#include "materiel_audite.h"



#include<QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include <QPageSize>
#include <QPdfWriter>
#include <QPainter>
#include <QtCharts>

#include <QMessageBox>
#include <QFile>
#include <QSqlRecord>

Materiel_audite::Materiel_audite()
{
id_materiel_audite =0;
nom_materiel_audite ="";
date_achat ="";
status ="";
numero_serie ="";
emplacement ="";
responsable_equipement ="";
}

Materiel_audite::Materiel_audite(int id_materiel_audite,QString nom_materiel_audite,QString date_achat ,QString status ,QString numero_serie ,QString emplacement  ,QString responsable_equipement,QByteArray imageV )
{
    this->id_materiel_audite =id_materiel_audite ;
    this->nom_materiel_audite =nom_materiel_audite ;
    this->date_achat =date_achat ;
    this->status =status ;
    this->numero_serie =numero_serie ;
    this->emplacement =emplacement ;
    this->responsable_equipement =responsable_equipement ;
    this->imageV=imageV;

}

int Materiel_audite:: get_id_materiel_audite (){return id_materiel_audite;}
QString Materiel_audite:: get_nom_materiel_audite (){return nom_materiel_audite;}
QString Materiel_audite:: get_date_achat (){return date_achat;}
QString Materiel_audite:: get_status (){return status;}
QString Materiel_audite:: get_numero_serie (){return numero_serie;}
QString Materiel_audite:: get_emplacement (){return emplacement;}
QString Materiel_audite:: get_responsable_equipement  (){return responsable_equipement;}

void Materiel_audite::setid_materiel_audite(int id_materiel_audite){this->id_materiel_audite =id_materiel_audite ;}
void Materiel_audite::setnom_materiel_audite(QString nom_materiel_audite){this->nom_materiel_audite =nom_materiel_audite ;}
void Materiel_audite::setdate_achat(QString date_achat){this->date_achat =date_achat ;}
void Materiel_audite::setstatus(QString status ){this->status =status ;}
void Materiel_audite::setnumero_serie(QString numero_serie){this->numero_serie =numero_serie ;}
void Materiel_audite::setemplacement(QString emplacement){this->emplacement =emplacement ;}
void Materiel_audite::setresponsable_equipement(QString responsable_equipement){this->responsable_equipement =responsable_equipement ;}



bool Materiel_audite::ajouter()
{
    QSqlQuery query;
    QString id_string = QString::number(id_materiel_audite);

    // Prepare the SQL query
    query.prepare("INSERT INTO MATERIEL_AUDITE (id_materiel_audite, nom_materiel_audite, date_achat, status, numero_serie, emplacement, responsable_equipement,image_equipement) "
                  "VALUES (:id_materiel_audite, :nom_materiel_audite, :date_achat, :status, :numero_serie, :emplacement,  :responsable_equipement, :image_equipement)");

    // Bind values to the query parameters
    query.bindValue(":id_materiel_audite", id_string);
    query.bindValue(":nom_materiel_audite", nom_materiel_audite);
    query.bindValue(":date_achat", date_achat);
    query.bindValue(":status", status);
    query.bindValue(":numero_serie", numero_serie);
    query.bindValue(":emplacement", emplacement);
    query.bindValue(":responsable_equipement", responsable_equipement);
    query.bindValue(":image_equipement",imageV);

    return query.exec();


}


QSqlQueryModel *Materiel_audite::afficher()const
{
    QSqlQueryModel *model =new QSqlQueryModel();

    model->setQuery("SELECT id_materiel_audite, nom_materiel_audite, date_achat, status, numero_serie, emplacement, responsable_equipement from MATERIEL_AUDITE");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("identifiant equipement"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom equipement"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("date d'achat"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("status"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("numero de serie"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("emplacement"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("responsable equipement"));


    return model;

}


bool Materiel_audite::supprimer(int id_materiel_audite)
{
    QSqlQuery query;
    QString res = QString::number(id_materiel_audite);

    query.prepare("DELETE FROM MATERIEL_AUDITE WHERE id_materiel_audite = :id_materiel_audite");
    query.bindValue(":id_materiel_audite", res);

    qDebug() << "Query: " << query.lastQuery();
    qDebug() << "Bound Values: " << query.boundValues();

    if (query.exec()) {
        // If the query executed successfully
        qDebug() << "Suppression effectuée avec succès";
        return true;
    } else {
        // If there was an error, display the error message
        qDebug() << "Erreur lors de la suppression :" << query.lastError().text();
        return false;
    }
}


bool Materiel_audite::modifier(int id_materiel_audite)
{
    QSqlQuery query;

    // Prepare the SQL query
    query.prepare("UPDATE MATERIEL_AUDITE SET nom_materiel_audite = :nom_materiel_audite, "
                  "date_achat = :date_achat, status = :status, "
                  "numero_serie = :numero_serie, emplacement = :emplacement, "
                  "responsable_equipement = :responsable_equipement, image_equipement = :image_equipement "
                  "WHERE id_materiel_audite = :id_materiel_audite");

    // Bind values to the query parameters
    query.bindValue(":id_materiel_audite", id_materiel_audite);
    query.bindValue(":nom_materiel_audite", nom_materiel_audite);
    query.bindValue(":date_achat", date_achat);
    query.bindValue(":status", status);
    query.bindValue(":numero_serie", numero_serie);
    query.bindValue(":emplacement", emplacement);
    query.bindValue(":responsable_equipement", responsable_equipement);
    query.bindValue(":image_equipement", imageV);

    // Check for errors
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQueryModel *Materiel_audite::rechercher(int id_materiel_audite)
{
    QSqlQuery query;
    QString id = QString::number(id_materiel_audite);

    QString queryStr = "SELECT * FROM   MATERIEL_AUDITE WHERE 1=1";

        if (id_materiel_audite > 0) {
            queryStr += " AND id_materiel_audite = :id_materiel_audite";
        }

        query.prepare(queryStr);

        if (id_materiel_audite > 0) {
            query.bindValue(":id_materiel_audite", id);
        }


        query.exec();

        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);

        return model;

}

QSqlQueryModel *Materiel_audite::tri()
         {
             QSqlQuery *m = new QSqlQuery();
             QSqlQueryModel *model = new QSqlQueryModel();
             m->prepare("SELECT * FROM MATERIEL_AUDITE ORDER BY ID_MATERIEL_AUDITE");
             m->exec();
             model->setQuery(*m);

             return model;

}

void Materiel_audite::exporterPDF(const QString &nomFichier) const
{
    QFile file(nomFichier);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QPdfWriter pdfWriter(&file);
            pdfWriter.setPageSize(QPageSize(QPageSize::A4));
            QPainter painter(&pdfWriter);

            painter.drawText(100, 100, "Liste des equipements");
            painter.drawText(100, 150, "identifiant equipement");
            painter.drawText(200, 150, "nom equipement");
            painter.drawText(300, 150, "Date d'achat");
            painter.drawText(400, 150, "Status");
            painter.drawText(500, 150, "numero de serie");
            painter.drawText(600, 150, "emplacement");
            painter.drawText(700, 150, "responsable equipement");

            QSqlQueryModel *model = afficher();
            for (int row = 0; row < model->rowCount(); ++row)
                 {
                     for (int col = 0; col < model->columnCount(); ++col)
                     {
                         QString data = model->data(model->index(row, col)).toString();
                         painter.drawText(100 + col * 100, 200 + row * 50, data);
                     }
                 }

                 file.close();
             }
             else {
                 qDebug() << "Erreur lors de l'ouverture du fichier : " << file.errorString();
             }
         }



    QString Materiel_audite::statistiqueparstatus()
    {
        int equipementEnMaintenance = getNombreEquipmentParStatus("en maintenance");
        int equipementDisponible = getNombreEquipmentParStatus("disponible");
        int equipementHorsService = getNombreEquipmentParStatus("hors service");
        int totalEquipements = equipementEnMaintenance + equipementDisponible + equipementHorsService;

        QtCharts::QPieSeries *pieSeries = new QtCharts::QPieSeries();

        QtCharts::QPieSlice *maintenanceSlice = new QtCharts::QPieSlice();
        QtCharts::QPieSlice *disponibleSlice = new QtCharts::QPieSlice();
        QtCharts::QPieSlice *horsServiceSlice = new QtCharts::QPieSlice();

        maintenanceSlice->setBrush(QColor(Qt::darkCyan));
        disponibleSlice->setBrush(QColor(Qt::cyan));
        horsServiceSlice->setBrush(QColor(Qt::darkGray));

        if (totalEquipements > 0) {
            maintenanceSlice->setValue(static_cast<double>(equipementEnMaintenance));
            disponibleSlice->setValue(static_cast<double>(equipementDisponible));
            horsServiceSlice->setValue(static_cast<double>(equipementHorsService));
        }

        pieSeries->append(maintenanceSlice);
        pieSeries->append(disponibleSlice);
        pieSeries->append(horsServiceSlice);

        maintenanceSlice->setLabel(QObject::tr("En maintenance") + ": " + QString::number(maintenanceSlice->percentage() * 100, 'f', 1) + "%");
        disponibleSlice->setLabel(QObject::tr("Disponible") + ": " + QString::number(disponibleSlice->percentage() * 100, 'f', 1) + "%");
        horsServiceSlice->setLabel(QObject::tr("Hors service") + ": " + QString::number(horsServiceSlice->percentage() * 100, 'f', 1) + "%");

        QtCharts::QChart *chart = new QtCharts::QChart();
        chart->addSeries(pieSeries);
        chart->setTitle("Statistiques des équipements");

        QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartView->show();

        QString statistiques = "Statistiques des équipements :\n";
        statistiques += QObject::tr("En maintenance") + " : " + QString::number(maintenanceSlice->percentage() * 100, 'f', 1) + "%\n";
        statistiques += QObject::tr("Disponible") + " : " + QString::number(disponibleSlice->percentage() * 100, 'f', 1) + "%\n";
        statistiques += QObject::tr("Hors service") + " : " + QString::number(horsServiceSlice->percentage() * 100, 'f', 1) + "%";

        return statistiques;
    }

    int Materiel_audite::getNombreEquipmentParStatus(const QString &status)
    {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM MATERIEL_AUDITE WHERE status = :status");
        query.bindValue(":status", status);

        if (query.exec() && query.next()) {
            return query.value(0).toInt();
        }

        return -1; // A negative value indicates an error
    }


    bool Materiel_audite::chercher_materiel_audite(QString id_materiel_audite)
    {
        QSqlQuery query;

        query.prepare("SELECT * FROM MATERIEL_AUDITE WHERE id_materiel_audite=:id_materiel_audite");
        query.bindValue(":id_materiel_audite",id_materiel_audite);

        if(query.exec() && query.next())
            return true;
        else
            return false;
    }

    QByteArray Materiel_audite::loadImageDataFromDatabase(QString id_materiel_audite, QString tablename) {
        QByteArray imageData;

        QSqlQuery query;

        // Prepare the SQL query to retrieve image data based on product ID
        query.prepare("SELECT image_equipement FROM " + tablename +" WHERE id_materiel_audite = :id_materiel_audite");
        query.bindValue(":id_materiel_audite", id_materiel_audite);

        // Execute the query
        if (query.exec()) {
            // Check if any results were returned
            if (query.next()) {
                // Retrieve image data from the query result
                imageData = query.value(0).toByteArray();
            } else {
                qDebug() << "Error: No image data found for id_materiel_audite" << id_materiel_audite;
            }
        } else {
            qDebug() << "Error executing SQL query:" << query.lastError().text();
        }

        return imageData;
    }

    QString Materiel_audite::encrypt(QString ID_MATERIEL_AUDITE)
    {
        QString result;
        int shift = ID_MATERIEL_AUDITE.right(1).toInt(); // use the last digit as the shift amount
        for(int i=0; i<ID_MATERIEL_AUDITE.length()-1; i++) {
            // shift each digit by 'shift' amount and add it to the result
            result += QString::number((ID_MATERIEL_AUDITE.at(i).digitValue() + shift) % 10);
        }
        // append the last digit to the end of the result
        result += ID_MATERIEL_AUDITE.right(1);
        return result;
    }
