#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
    QSqlDatabase db;

public:
    Connection();
    bool createconnection();
    void closeconnection();
    QList<QMap<QString, QString>> retrieveAllDataAsList(const QString& MATERIEL_AUDITE);

};

#endif // CONNECTION_H
