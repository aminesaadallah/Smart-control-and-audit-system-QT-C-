#ifndef MAILING_H
#define MAILING_H

#include <QCoreApplication>
#include <QProcess>
#include <qDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QStringList>
#include <QJsonArray>
#include <QResource>
#include <QByteArray>

class Mailing
{

private:
    QString folderPath, filePath, py_script_path;

    QMap<QString, QVariant> mailData;

public:
    Mailing();

    bool copyResourceToFile(const QString &fileName);
    QString executePythonScript(QString path);
    void createFolderIfNotExists(const QString &folderPath);
    void createJsonFile(const QString &filePath, const QMap<QString, QVariant> &dataMap);
    QMap<QString, QVariant> readJsonFile(const QString &filePath);
    void set_mail_atrb(QString atrb, QString txt);
    void set_mail_attachments(QVariant attachmentPaths);
    QString get_mail_atrb(QString atrb);
    QVariant get_mail_attachments();
    bool sendMailNormal(QString receiver, QString subject, QString message_body);
    bool sendMailWithAttachment(QString receiver, QString subject, QString message_body, QVariant attachmentPaths);
    bool sendMail(QString type);


};

#endif // MAILING_H
