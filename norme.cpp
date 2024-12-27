#include "norme.h"

norme::norme()
{

}

norme::norme(QString titre,QString description,int etat)
{
    this->titre=titre;
    this->description=description;
    this->etat=etat;
}

QString norme::gettitre()
{
    return titre;
}

void norme::settitre(QString t)
{
    titre=t;
}

QString norme::getdescription()
{
    return description;
}

void norme::setdescription(QString d)
{
    description=d;
}

int norme::getetat()
{
    return etat;
}

void norme::setetat(int e)
{
    etat=e;
}

bool norme::ajouter()
{
    QString etat_str=QString::number(etat);
    QSqlQuery query;
    query.prepare("INSERT INTO NORME (TITRE,DESCRIPTION,ETAT)""VALUES(:titre,:description,:etat)");
    query.bindValue(":titre",titre);
    query.bindValue(":description",description);
    query.bindValue(":etat",etat_str);
    return query.exec();
}

QSqlQueryModel * norme::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM NORME");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMERO"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TITRE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETAT"));
    return model;
}

bool norme::supprimer(int numero)
{
    QSqlQuery query;
    QString numero_str=QString::number(numero);

    QMessageBox::StandardButton reply = QMessageBox::question(
                    nullptr,
                    "Confirmation de suppression",
                    "Êtes-vous sûr de vouloir supprimer cette norme ?",
                    QMessageBox::Yes | QMessageBox::No
                    );

        if (reply == QMessageBox::Yes)
        {
    query.prepare("DELETE FROM NORME WHERE NUMERO=:numero");
    query.bindValue(":numero",numero_str);
        }
    return query.exec();
}



bool norme::modifier(int numero)
{
    QSqlQuery query;

    QString numero_str=QString::number(numero);
    QString etat_str=QString::number(etat);

    if(titre!="")
    {
        query.prepare("UPDATE NORME SET TITRE=:titre WHERE numero=:num");
        query.bindValue(":num",numero_str);
        query.bindValue(":titre",titre);
        query.exec();
    }

    if(description!="")
    {
        query.prepare("UPDATE NORME SET DESCRIPTION=:des WHERE NUMERO=:num");
         query.bindValue(":num",numero_str);
         query.bindValue(":des",description);
        query.exec();
    }

    if(etat_str!="")
    {
       query.prepare("UPDATE NORME SET ETAT=:etat WHERE NUMERO=:num");
       query.bindValue(":num",numero_str);
       query.bindValue(":etat",etat_str);
       query.exec();
    }
    return query.exec();
}

QSqlQueryModel *norme::tri_croissant()
{
   QSqlQueryModel *model = new QSqlQueryModel();
   model->setQuery("SELECT * FROM NORME ORDER BY TITRE ");
   return model;
}

QSqlQueryModel *norme::tri_decroissant()
{
   QSqlQueryModel *model = new QSqlQueryModel();
   model->setQuery("SELECT * FROM NORME ORDER BY TITRE DESC ");
   return model;
}

QSqlQueryModel *norme::rechercher(int numero)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString numero_str=QString::number(numero);

        model->setQuery("SELECT * FROM NORME WHERE NUMERO LIKE '"+numero_str+"%'");
    return model;
}







