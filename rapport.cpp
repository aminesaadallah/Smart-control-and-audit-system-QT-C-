#include "rapport.h"
#include<QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include<QMessageBox>
#include <QtCharts/QChartView>
#include <QtPrintSupport/QPrinter>
#include <QDateTime>
#include "ui_rapportform.h"
#include "connection.h"

rapport::rapport(int id,QString titre,QDate datedecreation,QString typeequipement,QDate datemodification,QString languetraduction,QString idmaterielaudite)


{
  this->id=id;
  this->titre=titre;
  this->datedecreation=datedecreation;
  this->typeequipement=typeequipement;
  this->datemodification=datemodification;
  this->languetraduction=languetraduction;
  this->idmaterielaudite=idmaterielaudite;

}

bool rapport::ajouter()
{
    QSqlQuery query;
   QString id_string =QString::number(id);
   QString datedecreation_string = datedecreation.toString("yyyy-MM-dd");
   QString datemodification_string = datemodification.toString("yyyy-MM-dd");


    query.prepare("INSERT INTO rapport(id, titre, datedecreation, typeequipement, datemodification, languetraduction,idmaterielaudite)"
                                "VALUES (:id, :titre, TO_DATE(:datedecreation, 'YYYY-MM-DD'), :typeequipement, TO_DATE(:datemodification, 'YYYY-MM-DD'), :languetraduction, :idmaterielaudite) ");
    query.bindValue(":id",id);
    query.bindValue(":titre",titre);
    query.bindValue(":datedecreation",datedecreation_string);
    query.bindValue(":typeequipement",typeequipement);
    query.bindValue(":datemodification",datemodification_string);
    query.bindValue(":languetraduction",languetraduction);
    query.bindValue(":idmaterielaudite",idmaterielaudite);


    // Execute the query
     if (query.exec()) {
         // Si l'ajout a réussi, enregistrez dans l'historique
              //  enregistrerEvenementHistorique("ajouté");
         // If the query executed successfully
         qDebug() << "Ajout effectué avec succès";
         return true;
     } else {
         // If there was an error, display the error message
         qDebug() << "Erreur lors de l'ajout :" << query.lastError().text();
         return false;
     }

}

QSqlQueryModel * rapport::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();


    model->setQuery("select * from rapport");

    model->setHeaderData (0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("titre"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("datedecreation"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("typeequipement"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("datemodification"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("languetraduction"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("idmaterielaudite"));



    return model;
 }


bool rapport::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM rapport WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Suppression effectuée avec succès";

        // Enregistrez l'événement de suppression dans l'historique
        //enregistrerEvenementHistorique(" supprimé");

        return true;
    } else {
        qDebug() << "Erreur lors de la suppression du rapport :" << query.lastError().text();
        return false;
    }

}


bool rapport::modifier()
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");

    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "Erreur : Connexion invalide ou non ouverte.";
        return false;
    }

    QSqlQuery query(db);

    //qDebug() << "data :" << id << titre << datedecreation << typeequipement << datemodification << languetraduction <<   idmaterielaudite ;

    query.prepare("UPDATE rapport SET titre = :titre, datedecreation = :datedecreation, typeequipement = :typeequipement, idmaterielaudite = :idmaterielaudite, "
                  "datemodification = :datemodification, languetraduction = :languetraduction "
                  "WHERE id = :id");

    query.bindValue(":id",id);
    query.bindValue(":titre", titre);
    query.bindValue(":datedecreation", datedecreation);
    query.bindValue(":typeequipement", typeequipement);
    query.bindValue(":datemodification",datemodification);
    query.bindValue(":languetraduction",languetraduction);
    query.bindValue(":idmaterielaudite",idmaterielaudite);



    if (query.exec()) {
        qDebug() << "Modification réussie pour l'id : " << id;
        return true;
    } else {
        qDebug() << "Erreur lors de la modification pour l'id " << id<< " : " << query.lastError().text();
        return false;
    }

}


bool rapport:: rechercher (int id, rapport &resultrapport)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM rapport WHERE ID = :ID");
    query.bindValue(":ID", id);

    if (query.exec() && query.first()) {
        // Populate 'resultrapport' with the data

        resultrapport.id= query.value("id").toInt();
        resultrapport.titre = query.value("titre").toString();
        resultrapport.datedecreation = QDate::fromString(query.value("datedecreation").toString(), "yyyy-MM-dd");
        resultrapport.typeequipement = query.value("typeequipement").toString();
        resultrapport.datemodification = QDate::fromString(query.value("datemodification").toString(), "yyyy-MM-dd");
        resultrapport.languetraduction= query.value("languetraduction").toString();
        resultrapport.idmaterielaudite= query.value("   idmaterielaudite").toString();


        return true; // Record found
    } else {
        qDebug() << "Erreur lors de la recherche du record :" << query.lastError().text();
         return false; // Record not found
    }
}

QSqlQueryModel *rapport::AfficherTriesParDate()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM rapport ORDER BY datedecreation");  // Assurez-vous de remplacer "datedecreation" par le nom réel de votre colonne de date

    // Assurez-vous d'ajuster les en-têtes en fonction de votre modèle de données
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("datedecreation"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("typeequipement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("datemodification"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("languetraduction"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("  idmaterielaudite"));



    return model;
}


QList<QMap<QString, QString>> rapport::retrieveAllDataAsList(const QString& tableName)
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

QMap<QString, QList<int>> rapport::retrieveRapportData(const QString &tableName) {
    QMap<QString, QList<int>> sourceData;

    QSqlQuery query;
    if (!query.exec("SELECT typeequipement, count(typeequipement) FROM " + tableName + " GROUP BY typeequipement")) {
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
// Fonction pour obtenir le nombre de rapports associés à un ID
/*int rapport::getReportCount()const
{
    // Effectuer votre requête SQL ici pour obtenir le nombre de rapports
    // Utilisez la variable 'id' pour filtrer les rapports associés à cet ID

    QSqlQuery query;
    QString queryString = QString("SELECT COUNT(*) FROM rapport WHERE idmaterielaudite = :targetId");
    query.prepare(queryString);
    query.bindValue(":targetId", id);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query";
        return -1; // Valeur de retour par défaut en cas d'erreur
    }

    // Fetch the result
    if (query.next())
    {
        int count = query.value(0).toInt();
        return count;
    }
    else
    {
        qDebug() << "Error: Unable to fetch result";
        return -1; // Valeur de retour par défaut en cas d'erreur
    }
}*/
