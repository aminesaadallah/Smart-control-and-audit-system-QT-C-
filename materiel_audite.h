#ifndef MATERIEL_AUDITE_H
#define MATERIEL_AUDITE_H

#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QVBoxLayout>
#include <QLabel>

#include "connection.h"
#include <QString>
#include <QSqlQuery>
#include<QtDebug>
#include <qmessagebox.h>
#include <QSqlQueryModel>
class Materiel_audite
{
private:
    int id_materiel_audite;

    QString nom_materiel_audite, date_achat, status,  numero_serie, emplacement, responsable_equipement;
    QByteArray imageV;

public:

    //constructeurs
    Materiel_audite();
    Materiel_audite(int,QString,QString,QString,QString,QString,QString,QByteArray);

    //setters
    void setid_materiel_audite(int id_materiel_audite);
    void setnom_materiel_audite( QString nom_materiel_audite);
    void setdate_achat(QString date_achat);
    void setstatus(QString status);
    void setnumero_serie(QString numero_serie);
    void setemplacement(QString emplacement);
    void setresponsable_equipement(QString responsable_equipement);

    //getters
    int get_id_materiel_audite();
    QString get_nom_materiel_audite();
    QString get_date_achat();
    QString get_status();
    QString get_numero_serie();
    QString get_emplacement();
    QString get_responsable_equipement();

    //fonctionalite de base relative a l'entité
    bool ajouter();
    QSqlQueryModel * afficher ()const;
    bool supprimer (int);
    bool modifier(int id_materiel_audite );
    QSqlQueryModel* rechercher(int id_materiel_audite);
    QSqlQueryModel * tri();
    void exporterPDF(const QString &nomFichier)const;
    QString statistiqueparstatus();
    int getNombreEquipmentParStatus(const QString &status);

    QByteArray loadImageDataFromDatabase(QString id_materiel_audite, QString tablename);

    bool chercher_materiel_audite(QString id_materiel_audite);

    QString encrypt(QString cin);


};

#endif // MATERIEL_AUDITE_H
