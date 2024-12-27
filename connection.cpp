#include"connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

Connection::Connection() {}

bool Connection::createconnection()
{
    bool test= false;




    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("yasmine"); // Insert the username
    db.setPassword("1234"); // Insert the password




    if (db.open())
        test = true;

    return test;
}

void Connection::closeconnection()
{

    db.close();
}

QList<QMap<QString, QString>> Connection::retrieveAllDataAsList(const QString& MATERIEL_AUDITE)
{
    QList<QMap<QString, QString>> dataList;

    QSqlQuery query;
    if (!query.exec("SELECT * FROM " + MATERIEL_AUDITE)) {
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
