#include "mailing.h"

Mailing::Mailing()
{
    folderPath = "";
    filePath = "";
    py_script_path = "";

    // Populate the QMap with email data
    mailData["type"] = "mail";
    mailData["user"] = "Marzouki.yosr@esprit.tn";
    mailData["pass"] = "yhvy kcxn xoha onxj";
    mailData["receiver"] = "";
    mailData["subject"] = "";
    mailData["message_body"] = "";

    // Create a QStringList to store attachment file paths
    QStringList attachmentPaths;

    // Add the QStringList of attachment paths to the QMap
    mailData["files"] = QVariant(attachmentPaths);

}

bool Mailing::copyResourceToFile(const QString &fileName) {

    // Path to the Python script in the resources
    QString scriptResourcePath = ":/scripts/" + fileName;

    QString scriptCopyPath = "./" + fileName;

    if (QFile::exists(scriptCopyPath)){
        qDebug() << "File already exists in the current directory.";
        return true;
    }

    // Copy the Python script from resources to the temporary directory
    QFile scriptCopy(scriptCopyPath);
        if (scriptCopy.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            QFile scriptResource(scriptResourcePath);
            if (scriptResource.open(QIODevice::ReadOnly)) {
                scriptCopy.write(scriptResource.readAll());
                scriptResource.close();
            }
            scriptCopy.close();

            qDebug() << "File copied to the current directory.";
            return true;
        } else {
            qDebug() << "Failed to copy the Python script.";
            return false;
        }

}

QString Mailing::executePythonScript(QString path)
{
    // Create a QProcess object
    QProcess pythonProcess;

    // Set the Python interpreter executable (e.g., "python" or "python3")
    pythonProcess.setProgram("python");

    // Define the arguments, including the path to your Python script
    QStringList arguments;
    arguments << path; // Replace with your script's path

    // Set the arguments for the Python script
    pythonProcess.setArguments(arguments);

    // Start the Python process
    pythonProcess.start();

    // Wait for the process to finish
    pythonProcess.waitForFinished();

    // Read the output of the Python script
    QByteArray output = pythonProcess.readAllStandardOutput();
    QString outputStr(output);

    // Read the standard error
    QByteArray errorOutput = pythonProcess.readAllStandardError();
    QString errorStr(errorOutput);

    // Check for any errors
    if (!errorStr.isEmpty()) {
        qDebug() << "Python script error:\n" << errorStr;
        return errorStr;
    }

    // Handle the output as needed
    //qDebug() << "Python script output:\n" << (outputStr == "Email sent successfully!\r\n");

    bool res = (outputStr == "Email sent successfully!\r\n");
    if (res){
        return "ok";
    }
    else {
        return outputStr;
    }
}

void Mailing::createFolderIfNotExists(const QString &folderPath) {
    QDir dir(folderPath);

    // Check if the directory already exists
    if (!dir.exists()) {
        // Attempt to create the directory
        if (dir.mkpath(".")) {
            //qDebug() << "Directory created successfully: " << folderPath;
        } else {
            //qWarning() << "Failed to create directory: " << folderPath;
        }
    } else {
        //qDebug() << "Directory already exists: " << folderPath;
    }
}

void Mailing::createJsonFile(const QString &filePath, const QMap<QString, QVariant> &dataMap) {
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonObject jsonObject;

        // Convert the QMap to a QJsonObject
        QMapIterator<QString, QVariant> iter(dataMap);
        while (iter.hasNext()) {
            iter.next();

            // Check if the value is a QStringList
            if (iter.value().canConvert<QStringList>()) {
                QStringList stringList = iter.value().toStringList();
                QJsonArray jsonArray;
                for (const QString &str : stringList) {
                    jsonArray.append(str);
                }
                jsonObject[iter.key()] = jsonArray;
            } else {
                jsonObject[iter.key()] = QJsonValue::fromVariant(iter.value());
            }
        }

        QJsonDocument jsonDoc(jsonObject);
        QByteArray jsonData = jsonDoc.toJson();

        file.write(jsonData);
        file.close();

        //qDebug() << "JSON file created successfully: " << filePath;
    } else {
        //qWarning() << "Failed to create JSON file: " << filePath;
    }
}

QMap<QString, QVariant> Mailing::readJsonFile(const QString &filePath) {
    QMap<QString, QVariant> resultMap;

    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray jsonData = file.readAll();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

        if (jsonDoc.isObject()) {
            QJsonObject jsonObject = jsonDoc.object();

            // Iterate through all keys and values in the JSON object
            QStringList keys = jsonObject.keys();
            for (const QString &key : keys) {
                QJsonValue jsonValue = jsonObject.value(key);

                if (jsonValue.isString()) {
                    resultMap[key] = jsonValue.toString();
                } else if (jsonValue.isArray()) {
                    QStringList stringList;
                    QJsonArray jsonArray = jsonValue.toArray();
                    for (const QJsonValue &arrayValue : jsonArray) {
                        if (arrayValue.isString()) {
                            stringList.append(arrayValue.toString());
                        }
                    }
                    resultMap[key] = stringList;
                } else {
                    // Handle other data types as needed
                }
            }
        } else {
            qWarning() << "JSON data is not an object in file: " << filePath;
        }

        file.close();
    } else {
        qWarning() << "Failed to open JSON file for reading: " << filePath;
    }

    return resultMap;
}

void Mailing::set_mail_atrb(QString atrb, QString txt){
    if (atrb == "receiver"){
        mailData["receiver"] = txt;
    }
    else if (atrb == "subject"){
        mailData["subject"] = txt;
    }
    else if (atrb == "message_body"){
        mailData["message_body"] = txt;
    }
}

void Mailing::set_mail_attachments(QVariant attachmentPaths){
    mailData["files"] = QVariant(attachmentPaths);
}

QString Mailing::get_mail_atrb(QString atrb){
    if (atrb == "user"){
        return mailData["user"].toString();
    }
    if (atrb == "receiver"){
        return mailData["receiver"].toString();
    }
    else if (atrb == "subject"){
        return mailData["subject"].toString();
    }
    else if (atrb == "message_body"){
        return mailData["message_body"].toString();
    }
    else{
        return "";
    }
}

QVariant Mailing::get_mail_attachments(){
    return mailData["files"];
}

bool Mailing::sendMailNormal(QString receiver, QString subject, QString message_body){

    bool file_exsits = copyResourceToFile("mail_for_qt.py");

    if (file_exsits){

        set_mail_atrb("receiver", receiver);
        set_mail_atrb("subject", subject);
        set_mail_atrb("message_body", message_body);

        //QString folderPath = "D:/esprit study/2eme/QT/projects/try2";
        QString folderPath = ".";

        createFolderIfNotExists(folderPath);

        QString filePath = folderPath + "/jsonfile.json";

        // Call createJsonFile with the QMap
        createJsonFile(filePath, mailData);

        // Execute the Python script
        //QString py_script_path = "D:/esprit study/2eme/QT/projects/try2/mail_for_qt.py";
        QString py_script_path = "./mail_for_qt.py";
        QString res = executePythonScript(py_script_path);
        //qDebug() << res;

        return res == "ok";
    }
    return "";

}

bool Mailing::sendMailWithAttachment(QString receiver, QString subject, QString message_body, QVariant attachmentPaths){

    bool file_exsits = copyResourceToFile("mail_for_qt.py");

    if (file_exsits){

        copyResourceToFile("mail_for_qt.py");

        set_mail_atrb("receiver", receiver);
        set_mail_atrb("subject", subject);
        set_mail_atrb("message_body", message_body);
        set_mail_attachments(attachmentPaths);

        //QString folderPath = "D:/esprit study/2eme/QT/projects/try2";
        QString folderPath = ".";

        createFolderIfNotExists(folderPath);

        QString filePath = folderPath + "/jsonfile.json";

        // Call createJsonFile with the QMap
        createJsonFile(filePath, mailData);

        // Execute the Python script
        //QString py_script_path = "D:/esprit study/2eme/QT/projects/try2/mail_for_qt.py";
        QString py_script_path = "./mail_for_qt.py";
        QString res = executePythonScript(py_script_path);
        //qDebug() << res;

        return res == "ok";

    }

    return "";
}

bool Mailing::sendMail(QString type){
    bool res = false;

    if (type == "normal"){

        res = sendMailNormal(mailData["receiver"].toString(), mailData["subject"].toString(), mailData["message_body"].toString());
    }
    else if (type == "files"){
        res = sendMailWithAttachment(mailData["receiver"].toString(), mailData["subject"].toString(), mailData["message_body"].toString(), mailData["files"]);
    }

    return res;
}
