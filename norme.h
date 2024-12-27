#ifndef NORME_H
#define NORME_H
#include <QString>
#include <QSqlQuery>
#include<QtDebug>
#include <qmessagebox.h>
#include <QSqlQueryModel>
#include <QSqlError>

class norme
{
public:
    norme();
    norme(QString titre,QString description,int etat);
    QString gettitre();
    void settitre(QString t);
    QString getdescription();
    void setdescription(QString d);
    int getetat();
    void setetat(int e);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int numero);
    bool modifier(int numero);

    QSqlQueryModel *tri_croissant();
    QSqlQueryModel *tri_decroissant();
    QSqlQueryModel *rechercher(int numero);

private:
    QString titre,description;
    int etat;
};

#endif // NORME_H
