#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QtSql>
#include <QDate>
client::client()
{
    ID_client="";
    num_client="";
    nomcl="";
    adressecl="";
    adresseEmail="";
    dateAud = "";
    dateEm  = "";
}
    void client::setID_client(QString n){ID_client=n;}
    void client::setnum_client(QString n){num_client=n;}
    void client::setnomcl(QString n){nomcl=n;}
    void client ::setadressecl(QString  n){adressecl=n;}
    void client::setadresseEmail(QString n){adresseEmail=n;}
    void client::setdateAud(QString n){dateAud=n;}
    void client::setdateEm(QString n){dateEm=n;}


    QString client::getID_client(){return ID_client;}
    QString client::getnum_client(){return num_client;}
    QString client::getnomcl(){return nomcl;}
    QString client::getadressecl(){return adressecl;}
    QString client ::getadresseEmail(){return adresseEmail; }
    QString client ::getdateAud(){return dateAud;}
    QString  client ::getdateEm(){return dateEm;}


client::client(QString adresseEmail,QString adressecl,QString nomcl,QString dateEm,QString dateAud,QString ID_client,QString num_client)
{
    this->ID_client=ID_client;
    this->num_client=num_client;
    this->nomcl=nomcl;
    this->adressecl=adressecl;
    this->adresseEmail=adresseEmail;
    this->dateAud=dateAud;
    this->dateEm=dateEm;
 }




bool client ::Ajouter()
{

        QSqlQuery query;
        QString ID_string=ID_client;
        QString num_string=num_client;
        QString datedeAUDstring = dateAud;
        QString dateEm_string = dateEm;

        // Utilize placeholders in the prepare statement and bind values accordingly
        /*query.prepare("INSERT INTO CLIENTS (ID_CLIENT, NOM_CLIENT, ADRESSE_CLIENT,NUM_CLIENT,ADRESSEEMAIL,DATE_AUD,DATE_EMAIL) "
                      "VALUES (:ID_CLIENT, :NOM_CLIENT :ADRESSE_CLIENT, :NUM_CLIENT, :ADRESSEEMAIL,  TO_DATE(:DATE_AUD, 'YYYY-MM-DD'):,  TO_DATE(:DATE_EMAIL, 'YYYY-MM-DD'))");*/
        query.prepare("INSERT INTO CLIENTS (ID_CLIENT, NOM_CLIENT, ADRESSE_CLIENT,NUM_CLIENT,ADRESSEEMAILL,DATE_AUD,DATE_EMAIL) "
                              "VALUES (:ID_CLIENT, :NOM_CLIENT, :ADRESSE_CLIENT, :NUM_CLIENT, :ADRESSEEMAILL, :DATE_AUD, :DATE_EMAIL)");

        qDebug() << "data :" << ID_client << num_client <<nomcl<< adressecl << adresseEmail << dateAud<< dateEm ;

        // Bind values to the placeholders in the appropriate order
        query.bindValue(":ID_CLIENT",ID_string);
        query.bindValue(":NOM_CLIENT",nomcl);
        query.bindValue(":ADRESSE_CLIENT",adressecl);
        query.bindValue(":NUM_CLIENT",num_client);
        query.bindValue(":ADRESSEEMAILL",adresseEmail);
        query.bindValue(":DATE_AUD",dateAud);
        query.bindValue(":DATE_EMAIL",dateEm);




        if (query.exec()) {
            qDebug() << "Record ajouté avec succès";

            return true;
        } else {
            qDebug() << "Erreur lors de l'ajout du record :" << query.lastError().text();

            return false;
        }

}

QSqlQueryModel * client::Afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();


    model->setQuery("select * from CLIENTS");

    model->setHeaderData (0,Qt::Horizontal,QObject::tr("id_client"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("num client"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("nom client"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("adresse client"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse email client"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("date audit"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("date email"));


    return model;
 }

QList<QMap<QString, QString>> client::retrieveAllDataAsList(const QString& tableName)
{
    QList<QMap<QString, QString>> dataList;

        QSqlQuery query;
        if (!query.exec("SELECT * FROM " + tableName)) {
            qDebug() << "Error executing query:" << query.lastError().text();
            return dataList;
        }

        while (query.next()) {
            QMap<QString, QString> rowData;
            QSqlRecord record = query.record();

            for (int i = 0; i < record.count(); ++i) {
                rowData[record.fieldName(i).toLower()] = query.value(i).toString();
            }

            dataList.append(rowData);
        }

        qDebug() << "Data retrieved successfully!";
        return dataList;
}

bool client::Supprimer(QString ID_client )
{
    QSqlQuery query;
    QString res=ID_client;
    qDebug() << res;
    query.prepare("delete from clients where id_client= :ID ");
    query.bindValue(":ID",res);
    return query.exec();

}

bool client::Modifier()
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");  // Obtenez la connexion à la base de données

    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "Erreur : Connexion invalide ou non ouverte.";
        // Gérez l'erreur de connexion à la base de données ici si nécessaire.
        return false;
    }

    // Vous devez construire la requête SQL pour la mise à jour des données.
    QSqlQuery query(db);
    query.prepare("UPDATE clients  SET nom_client = :NOM_CLIENT, adresse_client = :ADRESSE_CLIENT, num_client = :NUM_CLIENT, adresseemaill = :ADRESSEEMAILL, date_aud = :DATE_AUD, date_email = :DATE_EMAIL "

                  "WHERE id_client = :ID");


    query.bindValue(":ID", ID_client);
    query.bindValue(":NOM_CLIENT",nomcl);
    query.bindValue(":ADRESSE_CLIENT",adressecl);
    query.bindValue(":NUM_CLIENT",num_client);
    query.bindValue(":ADRESSEEMAILL",adresseEmail);
    query.bindValue(":DATE_AUD",dateAud);
    query.bindValue(":DATE_EMAIL",dateEm);
    if (query.exec()) {
        qDebug() << "Modification réussie pour ID : " << ID_client;
        return true;  // La mise à jour a réussi.
    } else {
        qDebug() << "Erreur lors de la modification pour l ID " << ID_client << " : " << query.lastError().text();
        // Gérez l'erreur de mise à jour ici si nécessaire.
        return false;
    }
}

QList<QMap<QString, QString>> client::retrieveAllDataAsListSorted(const QString& tableName, const QString& orderByColumn)
{
    QList<QMap<QString, QString>> dataList;

    QSqlQuery query;
    QString queryString = "SELECT * FROM " + tableName + " ORDER BY " + orderByColumn;

    if (!query.exec(queryString)) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return dataList;
    }

    while (query.next()) {
        QMap<QString, QString> rowData;
        QSqlRecord record = query.record();

        for (int i = 0; i < record.count(); ++i) {
            rowData[record.fieldName(i).toLower()] = query.value(i).toString();
        }

        dataList.append(rowData);
    }

    qDebug() << "Data retrieved successfully!";
    return dataList;
}

QList<QMap<QString, QString>> client::searchData(const QString& tableName, const QString& column, const QString& searchTerm)
{
    QList<QMap<QString, QString>> searchResults;

    QSqlQuery query;
    QString queryString = "SELECT * FROM " + tableName + " WHERE " + column + " LIKE ?";
    query.prepare(queryString);
    query.addBindValue("%" + searchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return searchResults;
    }

    while (query.next()) {
        QMap<QString, QString> rowData;
        QSqlRecord record = query.record();

        for (int i = 0; i < record.count(); ++i) {
            rowData[record.fieldName(i).toLower()] = query.value(i).toString();
        }

        searchResults.append(rowData);
    }

    qDebug() << "Search results retrieved successfully!";
    return searchResults;
}

bool client::checkIdExists(const QString& generatedId) {
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM clients WHERE 	id_client LIKE ?");
    checkQuery.addBindValue("%" + generatedId + "%");

    if (checkQuery.exec() && checkQuery.next()) {
        int count = checkQuery.value(0).toInt();
        return count > 0;
    } else {
        qDebug() << "Query error:" << checkQuery.lastError().text();
        return false; // Handle the error condition
    }
}


bool client::Rechercher (int ID_client,client &resultclient)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM client WHERE ID_client = :ID_client");
    query.bindValue(":ID",ID_client);
    qDebug()<<ID_client;
    if (query.exec() && query.first()) {
        // Populate 'resultLivreur' with the data
        resultclient.ID_client = query.value("ID").toString();
        resultclient.num_client = query.value("num client").toString();
        resultclient.nomcl= query.value("Nom").toString();
        resultclient.adressecl=query.value("adresse client").toString();
        resultclient.adresseEmail=query.value("adresse email client").toString();
        resultclient.dateEm = query.value("date email").toString();
        resultclient.dateAud = query.value("date audit").toString();

        return true; // Record found
    } else {
        return false; // Record not found
    }
}


//stat
QMap<QString, QList<int>> client::retrieveAdrsData(const QString &tableName) {
    QMap<QString, QList<int>> sourceData;

    QSqlQuery query;
    if (!query.exec("SELECT adresse_client, count(adresse_client) FROM " + tableName + " GROUP BY adresse_client")) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return sourceData;
    }

    while (query.next()) {
        QString source = query.value(0).toString();
        int quantity = query.value(1).toInt();

        if (!sourceData.contains(source)) {
            sourceData[source] = QList<int>();
        }

        sourceData[source].append(quantity);
    }

    qDebug() << "Source data retrieved successfully!";
    return sourceData;
}

QStringList client::retrieveAllClientsIds(const QString &tableName) {
    QStringList employerIds;

    QSqlQuery query;
    QString queryString = "SELECT DISTINCT adresse_client FROM " + tableName;

    if (query.exec(queryString)) {
        while (query.next()) {
            QString employerId = query.value("adresse_client").toString();
            employerIds.append(employerId);
        }
    } else {
        qDebug() << "Error executing query: " << query.lastError().text();
    }

    return employerIds;
}


//calander
QList<QMap<QString, QString>> client::retrieveAllCalanderDataAsList(const QString& tableName, const QDate& x)
{
    QList<QMap<QString, QString>> dataList;

    QString xString = x.toString("d/M/yyyy");  // Convert QDate to string in the expected format

    //qDebug() << "date :" << xString;

    QSqlQuery query;
    if (!query.exec("SELECT * FROM " + tableName + " WHERE date_aud = '" + xString + "'")) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return dataList;
    }

    while (query.next()) {
        QMap<QString, QString> rowData;
        QSqlRecord record = query.record();

        for (int i = 0; i < record.count(); ++i) {
            rowData[record.fieldName(i).toLower()] = query.value(i).toString();
        }

        dataList.append(rowData);
    }

    qDebug() << "Data retrieved successfully!";
    return dataList;
}
