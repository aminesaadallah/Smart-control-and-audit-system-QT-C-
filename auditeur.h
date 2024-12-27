#ifndef AUDITEUR_H
#define AUDITEUR_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include"connection.h"

#include <QSqlError>

#include <QSqlRecord>



class Auditeur
{
private:
    int id_auditeur;

    QString nom_auditeur,mail_auditeur,mdp_auditeur,tel_auditeur,genre_auditeur;

public:

    //constructeurs
    Auditeur();
    Auditeur(int,QString,QString,QString,QString,QString);

    //setters
    void setid_auditeur(int id_auditeur);
    void setnom_auditeur( QString nom_auditeur);
    void setmail_auditeur(QString mail_auditeur);
    void settel_auditeur(QString tel_auditeur);
    void setmdp_auditeur(QString mdp_auditeur);
    void setgenre_auditeur(QString genre_auditeur);
    bool checkIdEmailexist(const QString& generatedId);
   bool checkIdmdpexist(const QString& generatedId);


    //getters
    int get_id_auditeur();
    QString get_nom_auditeur();
    QString get_mail_auditeur();
    QString get_tel_auditeur();
    QString get_mdp_auditeur();
    QString get_genre_auditeur();

    //fonctionalite de base relative a l'entité
    bool ajouter();
    QSqlQueryModel * afficher ();
    bool supprimer (int);
    bool modifier(int id_auditeur);
    QSqlQueryModel* rechercher(int id_auditeur);
    QSqlQueryModel * tri();

    QList<QMap<QString, QString>> retrieveAllDataAsList(const QString& tableName);
    QList<QMap<QString, QString>> searchData(const QString& tableName, const QString& column, const QString& searchTerm);
    QMap<QString, QList<int>> retrieveAuditeurData(const QString &tableName);
    QList<QMap<QString, QString>> searchData1(const QString& tableName, const QString& column, const QString& searchTerm);


};

#endif // MATERIEL_AUDITE_H
