#ifndef RAPPORT_H
#define RAPPORT_H
#include<QString>
#include<QDate>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlError>
#include <QtDebug>
#include<QSqlError>
#include<QSqlRecord>
#include <QDateTime>
#include"connection.h"


class rapport
{
private:

    QString titre,typeequipement,languetraduction,idmaterielaudite;
    QDate datedecreation,datemodification;
    int id;

public:
     //constructeurs
     rapport(){}
     rapport(int,QString,QDate,QString ,QDate,QString,QString);


     //Setteurs
    void setid(int id);
    void settitre(QString n);
    void setdatedecreation(QDate d);
    void settypeequipement(QString n);
    void setdatemodification(QDate d);
    void setlanguetraduction(QString n);
    void setidmaterielaudite(QString n);



    //Getteurs
    int getid() {return id;}
    QString gettitre() {return titre;}
    QDate getdatedecreation(){return datedecreation;}
    QString gettypeequipement() {return typeequipement;}
    QDate getdatemodification(){return datemodification;}
    QString getlanguetraduction(){return languetraduction;}
    QString getidmaterielaudite(){return idmaterielaudite;}


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    bool rechercher(int id, rapport &resultrapport);
    QSqlQueryModel *AfficherTriesParDate();
    void exportToPDF(const QString &filename, const QStringList &rapportList);
    QList<QMap<QString, QString>> retrieveAllDataAsList(const QString& tableName);

    QMap<QString, QList<int>> retrieveRapportData(const QString &tableName);
 //int getReportCount()const;
};


#endif // RAPPORT_H


