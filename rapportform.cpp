#include "rapportform.h"
#include "ui_rapportform.h"
#include <QMessageBox>
#include "rapport.h"
#include <QIntValidator>
#include <QSqlQuery>
#include <QDebug>
#include<QFile>
#include<QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include<QPdfWriter>
#include<QPushButton>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include<QDesktopServices>
#include <QDir>

#include <QtCharts>
#include <QChartView>
#include <QLayout>
#include <QFrame>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLegend>
#include <QtCharts/QBarLegendMarker>
#include <QtCharts/QHorizontalBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QInputDialog>
#include <QMessageBox>
#include"auditeurform.h"
#include"clientform.h"
#include"materielleform.h"
#include"normeform.h"
Rapportform::Rapportform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rapportform)
{

    ui->setupUi(this);
    cnx.createconnection();
    rapport rapportInstance;
    ui->lineEdit_id->setValidator(new QIntValidator(100,999999,this));
    ui->tableView_afficher->setModel(rapportInstance.afficher());




    model = new QSqlQueryModel(this);
    connect(ui->pushButton_rechercher_2, SIGNAL(clicked()), this, SLOT (on_pushButton_rechercher_clicked()));
    connect(ui->pushButton_trier, &QPushButton::clicked, this, &Rapportform::on_pushButton_trier_clicked);
    connect(ui->pushButton_detect, &QPushButton::clicked, this, &Rapportform::generateSuiviPDF);
    addDataToTableView(rmp.retrieveAllDataAsList("rapport"));
    loadChart("rapport");
    COMPORT = new QSerialPort() ;



            COMPORT->setPortName("COM6");



            COMPORT->setBaudRate (QSerialPort::BaudRate::Baud9600);



            COMPORT->setParity (QSerialPort::Parity::NoParity);



            COMPORT->setDataBits (QSerialPort::DataBits::Data8);

            COMPORT->setStopBits (QSerialPort::StopBits::OneStop);



            COMPORT->setFlowControl (QSerialPort::FlowControl::NoFlowControl);



            COMPORT->open(QIODevice::ReadWrite);



            if(COMPORT->isOpen()){



            qDebug() << "Serial Port Is Connected." ;

                        qDebug() << COMPORT->error();

            }

            else{



            qDebug() << "Serial Port Is Not Connected.";



            qDebug() << COMPORT->error();

        }

            connect (COMPORT,SIGNAL(readyRead()),this,SLOT(Read_Data()));

            if(ardid!=0){

                qDebug()<<ardid;

            }
}

Rapportform::~Rapportform()
{
    delete ui;
}
//pour le menu
void Rapportform::on_pushButton_2_clicked()
{
  Auditeurform a;
   this->hide();
  a.exec();

}

void Rapportform::on_pushButton_3_clicked()
{
    Clientform cl;
    this->hide();
    cl.exec();

}

void Rapportform::on_pushButton_4_clicked()
{
    Rapportform r;
      this->hide();
    r.exec();

}

void Rapportform::on_pushButton_5_clicked()
{
    Materielleform m;
      this->hide();
    m.exec();

}

void Rapportform::on_pushButton_6_clicked()
{
    Normeform n;
     this->hide();
    n.exec();

}

/////fin menu
void Rapportform::on_pushButton_ajouter_2_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    QString titre=ui->lineEdit_titre->text();
    QDate datedecreation=QDate::fromString(ui->lineEdit_datecre->text(), "yyyy-MM-dd");
    QString typeequipement=ui->lineEdit_typeequi->text();
    QDate datemodification= QDate::fromString(ui->lineEdit_datemodi->text(), "yyyy-MM-dd");
    QString languetraduction=ui->lineEdit_languetrad->text();
    QString idmaterielaudite=ui->lineEdit_mataud->text();


    rapport r(id,titre,datedecreation,typeequipement,datemodification,languetraduction,idmaterielaudite);


     bool test = r.ajouter();
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "click ok to exist"), QMessageBox::Ok);
        addDataToTableView(rmp.retrieveAllDataAsList("rapport"));
         lograpportChange(id, "ajouter");
         // Après l'ajout, charger le graphique
             loadChart("rapport");

    }


    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non éffectué\n"
                                   "click Cancel to exit"), QMessageBox::Cancel);
    }


}


void Rapportform::on_pushButton_supprimer_2_clicked()
{
    int id = ui->lineEdit_idRS_2->text().toInt();

    bool test = rmp.supprimer(id);

    if (test) {
        // Mettez à jour seulement le modèle de tableView_afficher après la suppression
     addDataToTableView(rmp.retrieveAllDataAsList("rapport"));


        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\nClick Cancel to exit."), QMessageBox::Cancel);

        lograpportChange(id, "supprimer");
        // Après la suppression, charger le graphique
          loadChart("rapport");
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
    }



}


void Rapportform::on_pushButton_modifier_2_clicked()
{
    // Récupérez les valeurs modifiées depuis les champs d'interface utilisateur
    int id = ui->lineEdit_id->text().toInt();
    QString titre=ui->lineEdit_titre->text();
    QDate datedecreation = QDate::fromString(ui->lineEdit_datecre->text(), "yyyy-MM-dd");
    QString typeequipement=ui->lineEdit_typeequi->text();
    QDate datemodification = QDate::fromString(ui->lineEdit_datemodi->text(), "yyyy-MM-dd");
    QString languetraduction =ui->lineEdit_languetrad->text();
    QString idmaterielaudite =ui->lineEdit_mataud->text();

    //qDebug() << "data 1 :" << id << titre << datedecreation << typeequipement << datemodification << languetraduction << idmaterielaudite ;



    // Créez un objet rapport avec les nouvelles valeurs
   rapport rapportModifie( id, titre, datedecreation, typeequipement, datemodification, languetraduction,idmaterielaudite);

    // Utilisez la fonction Modifier pour mettre à jour les données dans la base de données
    if (rapportModifie.modifier()) {
        // Mise à jour réussie
        QMessageBox::information(nullptr, QObject::tr("Modification réussie"), QObject::tr("Le rapport a été modifié avec succès."), QMessageBox::Ok);
        // Mettez à jour le modèle si vous utilisez un QTableView
        // model->setQuery("SELECT * FROM rapport");
        addDataToTableView(rmp.retrieveAllDataAsList("rapport"));
         lograpportChange(id, "modifier");
         // Après la suppression, charger le graphique
           loadChart("rapport");

    } else {
        // Gérez l'erreur si la mise à jour échoue
        QMessageBox::critical(nullptr, QObject::tr("Erreur de modification"), QObject::tr("Erreur lors de la modification du rapport."), QMessageBox::Ok);
    }



}


void Rapportform::on_pushButton_rechercher_clicked()
{
    // Get the search ID from a QLineEdit or QSpinBox, assuming you have an input field named 'lineEdit_idR'
    int searchid = ui->lineEdit_idRS_2->text().toInt();

    rapport resultrapport;

    if (rapportInstance.rechercher(searchid, resultrapport)) {
        // Record found - update QLineEdit widgets to display the data
        ui->lineEdit_id->setText(QString::number(resultrapport.getid()));
        ui->lineEdit_titre->setText(resultrapport.gettitre());
        ui->lineEdit_datecre->setText(resultrapport.getdatedecreation().toString("dd/MM/yyyy"));
        ui->lineEdit_typeequi->setText(resultrapport.gettypeequipement());
        ui->lineEdit_datemodi->setText(resultrapport.getdatemodification().toString("dd/MM/yyyy"));
        ui->lineEdit_languetrad->setText(resultrapport.getlanguetraduction());
        ui->lineEdit_mataud->setText(resultrapport.getidmaterielaudite());

        // Mettez à jour le modèle pour afficher le résultat dans le QTableView
        model->setQuery("SELECT * FROM rapport WHERE id = " + QString::number(searchid));
        ui->tableView_afficher->setModel(model);
    } else {
        // Handle the case when the record is not found
        QMessageBox::warning(this, "Search Result", "Record not found for ID: " + QString::number(searchid));
    }
}


void Rapportform::on_pushButton_trier_clicked()
{
    {
        // Par exemple, dans votre fonction associée au clic du bouton

            // Supprimez le modèle actuel s'il existe
            if (ui->tableView_afficher->model()) {
                delete ui->tableView_afficher->model();
            }

            // Affichez les rapports triés par prix
            ui->tableView_afficher->setModel(rmp.AfficherTriesParDate());
        }

}


bool Rapportform::exportDataToPDF(const QString& filePath)
{
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tableView_afficher->model());

    if (!model) {
        qDebug() << "No model found.";
        return false;
    }

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QTextDocument doc;
    QTextCursor cursor(&doc);

    QTextTableFormat tableFormat;
    tableFormat.setBorder(1); // Set the border width for the table
    QTextTable* table = cursor.insertTable(model->rowCount() + 1, model->columnCount(), tableFormat);

    // Fill in table headers
    for (int col = 0; col < model->columnCount(); ++col) {
        QModelIndex index = model->index(0, col);
        QTextTableCell headerCell = table->cellAt(0, col);
        headerCell.firstCursorPosition().insertText(model->headerData(col, Qt::Horizontal).toString());
    }

    // Fill in table data
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QModelIndex index = model->index(row, col);
            QTextTableCell dataCell = table->cellAt(row + 1, col);
            dataCell.firstCursorPosition().insertText(model->data(index).toString());
        }
    }

    doc.setPageSize(printer.pageRect().size());
    doc.print(&printer);

    qDebug() << "Data exported to PDF successfully!";

    return true;
}


QString Rapportform::getSaveFilePath(QWidget *parent, QString file_type) {
    QString all_files_filter = "All Files (*)";
    QString selected_filter = file_type + ";;" + all_files_filter;

    QString filePath = QFileDialog::getSaveFileName(
        parent, "Save File", QDir::homePath(), selected_filter
    );

    if (!filePath.isEmpty()) {
        // The user selected a file path.
        // You can use 'filePath' to save your file.
        return filePath;
    } else {
        // The user canceled the save operation.
        return QString(); // Return an empty string to indicate no file was selected.
    }
}


void Rapportform::on_pushButton_pdf_clicked()
{
    ///create the output folder
       // Get the current working directory
           //QString currentDir = QDir::currentPath();
       QString outputFileName = getSaveFilePath(this, "PDF Files (*.pdf)");

       if (!outputFileName.isEmpty()) {
           qDebug() << outputFileName;

          if (exportDataToPDF(outputFileName)){

              QString folderPath = outputFileName;
              QUrl folderUrl = QUrl::fromLocalFile(folderPath);

              //open the folder

              if (QDesktopServices::openUrl(folderUrl)) {
                  qDebug() << "Folder opened successfully.";
              } else {
                  qDebug() << "Failed to open folder.";
              }

              QFileInfo fileInfo(outputFileName);
              folderPath = fileInfo.absolutePath();
              folderUrl = QUrl::fromLocalFile(folderPath);

              //open the folder

              if (QDesktopServices::openUrl(folderUrl)) {
                  qDebug() << "Folder opened successfully.";
              } else {
                  qDebug() << "Failed to open folder.";
              }



              //qDebug() << "file exported";
          }
       }
}

void Rapportform::addDataToTableView(const QList<QMap<QString, QString>>& dataList)
{
    QStandardItemModel* model = new QStandardItemModel(this);

        // Define the desired column order
        QStringList columnOrder = {"id", "titre", "datedecreation", "typeequipement", "datemodification", "languetraduction","idmaterielaudite"};

        // Set the column headers based on the defined order
        QStringList headers;
        for (const QString& columnName : columnOrder) {
            headers << columnName;
        }
        model->setHorizontalHeaderLabels(headers);

        for (const auto& rowData : dataList) {
            QList<QStandardItem*> rowItems;

            // Populate the row in the specified order
            for (const QString& columnName : columnOrder) {
                QStandardItem* item = new QStandardItem(rowData.value(columnName));
                rowItems.append(item);
            }
            model->appendRow(rowItems);
        }

        ui->tableView_afficher->setModel(model);
}

void Rapportform::lograpportChange(int id, const QString& action)
{
    QSqlQuery query;
    query.prepare("INSERT INTO HISTORIQUE (ID_RAPPORT, ACTION, DATETIME) VALUES (:idrapport, :action, :datetime)");
    query.bindValue(":idrapport", id); // Convert int to QString
    query.bindValue(":action", action);
    query.bindValue(":datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

    if (!query.exec()) {
        qDebug() << "Error logging rapport change:" << query.lastError().text();
    }
}


void Rapportform::generateSuiviPDF()
{
    // Create a QTextDocument
    QTextDocument doc;

    // Set the document title
    doc.setHtml("<h1 style='text-align:center;'>Modification pour la gestion des rapports :</h1>");

    // Create an HTML-like string for the table
    QString tableHtml = "<table border='1' cellspacing='0' cellpadding='10' style='width:100%; margin:auto; border-collapse:collapse;  align: center; '>";
    tableHtml += "<tr><th style='border:1px solid #ddd; padding:20px; background-color:#f2f2f2;'>ID rapport</th><th style='border:1px solid #ddd; padding:20px; background-color:#f2f2f2;'>Action</th><th style='border:1px solid #ddd; padding:20px; background-color:#f2f2f2;'>Date Time</th></tr>";

    // Fetch suivi data and populate the table
    QSqlQuery query("SELECT * FROM historique");
    while (query.next()) {
        tableHtml += "<tr>";
        tableHtml += "<td style='border:1px solid #ddd; padding:20px;'>" + query.value(0).toString() + "</td>";
        tableHtml += "<td style='border:1px solid #ddd; padding:20px;'>" + query.value(1).toString() + "</td>";
        tableHtml += "<td style='border:1px solid #ddd; padding:20px;'>" + query.value(2).toString() + "</td>";
        tableHtml += "</tr>";
    }

    tableHtml += "</table>";

    // Insert the table HTML into the document
    QTextCursor cursor(&doc);
    cursor.movePosition(QTextCursor::End);
    cursor.insertHtml(tableHtml);

    // Get the user's download directory path
    QString downloadPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

    // Prompt the user for the save location
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", QDir(downloadPath).filePath("suivi_rapport.pdf"), "PDF Files (*.pdf)");

    // Check if the user canceled the save operation
    if (filePath.isEmpty()) {
        return;
    }

    // Create a QPrinter
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    // Print the document to the PDF file
    doc.print(&printer);
}
void Rapportform::loadTypeEquipementChart(const QMap<QString, QList<int>> &data)
{
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    QtCharts::QChart *chart = new QtCharts::QChart();
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);

    int totalCount = 0; // Variable pour stocker le total de tous les types d'équipement

    // Parcours de toutes les sources (types d'équipement) pour calculer le total
    for (const QString &source : data.keys()) {
        for (const int& value : data[source]) {
            totalCount += value;
        }
    }

    // Parcours de toutes les sources (types d'équipement) pour créer les séries
    for (const QString &source : data.keys()) {
        QtCharts::QBarSet *set = new QtCharts::QBarSet(source);

        // Parcours de toutes les valeurs associées à une source pour calculer les pourcentages
        for (const int& value : data[source]) {
            double percentage = 0.0;
            if (totalCount > 0) {
                percentage = static_cast<double>(value) / totalCount * 100.0;
            }
            *set << percentage;
        }

        series->append(set);
    }

    // Ajouter la série au graphique
    chart->addSeries(series);

    // Créer et configurer l'axe des valeurs (X)
    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis();
    axisX->setTitleText("Equipements Medicaux");
    chart->setAxisX(axisX, series);

    // Désactiver l'affichage des étiquettes de l'axe X
    axisX->setLabelsVisible(false);

    // Créer et configurer l'axe des valeurs (Y)
    QtCharts::QValueAxis *valueAxisY = new QtCharts::QValueAxis();
    valueAxisY->setTitleText("Pourcentage");
    valueAxisY->setLabelFormat("%.0f%%"); // Définir le format des étiquettes
    chart->setAxisY(valueAxisY, series);

    // Configurer le titre et le légende
    chart->setTitle("Statistiques des types d'équipement (en %)");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Supprimer tous les anciens widgets du layout
    QLayoutItem *child;
    while ((child = ui->verticalLayout_chart_2->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }

    // Ajouter le nouveau graphique au layout
    ui->verticalLayout_chart_2->addWidget(chartView);

    // Affiche des messages de débogage pour vérifier le graphique
    qDebug() << "Chart created successfully!";
}
void Rapportform::loadChart(const QString &tableName)
{
    QMap<QString, QList<int>> data = rmp.retrieveRapportData(tableName);

    // Affiche les données récupérées dans la console
    for (const QString &source : data.keys()) {
        qDebug() << source << ": " << data[source];
    }

    loadTypeEquipementChart(data);
}
void Rapportform::on_countButton_clicked()
{
    QString idmaterielaudite = ui->lineEdit_count->text();
    qDebug() << "on_countButton_clicked - idmaterielaudite : " << idmaterielaudite;

    QSqlQuery query;
    QString queryString = QString("SELECT COUNT(*) FROM rapport WHERE idmaterielaudite = :targetId");
    query.prepare(queryString);
    query.bindValue(":targetId", idmaterielaudite);

    if (!query.exec()) {
        qDebug() << "Erreur : impossible d'exécuter la requête";
        qDebug() << "Requête : " << queryString;
        qDebug() << "Valeur liée : " << idmaterielaudite;
        return;
    }

    // Récupérer le résultat
    if (query.next()) {
        int count = query.value(0).toInt();
        qDebug() << "on_countButton_clicked - Résultat de la requête : " << count;
        ui->id_count->setText(QString::number(count));
    } else {
        qDebug() << "Erreur : impossible de récupérer le résultat de la requête";
    }
}

void Rapportform::recherche(const QString& id)
{
    QSqlQuery query;
    QString queryString = QString("SELECT COUNT(*) FROM rapport WHERE idmaterielaudite = :targetId");
    query.prepare(queryString);
    query.bindValue(":targetId", id);

    if (!query.exec()) {
        qDebug() << "recherche - Erreur : impossible d'exécuter la requête";
        qDebug() << "Requête : " << queryString;
        qDebug() << "Valeur liée : " << id;
        return;
    }

    // Récupérer le résultat
    if (query.next()) {
        int count = query.value(0).toInt();
        qDebug() << "recherche - Résultat de la requête : " << count;

        // Vérifier si le pointeur ui->id_count est valide
        if (ui->id_count) {
            // Utiliser QMetaObject::invokeMethod pour mettre à jour l'interface utilisateur depuis un autre thread
            QMetaObject::invokeMethod(ui->id_count, "setText", Qt::QueuedConnection, Q_ARG(QString, QString::number(count)));

            // Afficher le texte que vous essayez de définir
            qDebug() << "recherche - Texte à afficher sur l'écran LCD : " << QString::number(count);
        } else {
            qDebug() << "recherche - Erreur : ui->id_count est NULL";
        }

        QString to_show =  "show:" + QString::number(count).toUtf8();

        qDebug() << "aaaaa : " << to_show.toUtf8();

        COMPORT->write(to_show.toUtf8());
        COMPORT->flush();
    } else {
        qDebug() << "recherche - Erreur : impossible de récupérer le résultat de la requête";
    }
}


void Rapportform::Read_Data()
{
    if (COMPORT->isOpen()) {
        while (COMPORT->bytesAvailable()) {
            Data_From_SerialPort += COMPORT->readAll();
            if (Data_From_SerialPort.contains('\n')) {
                qDebug() << "Read_Data - Données reçues depuis le port série : " << Data_From_SerialPort;
                Is_Data_Recevied = true;
            }
        }

        if (Is_Data_Recevied) {
            ui->textBrowser->append(Data_From_SerialPort);

            // Extraire l'ID de la chaîne
            QRegularExpression regex("ID:(\\d+)");
            QRegularExpressionMatch match = regex.match(Data_From_SerialPort);

            if (match.hasMatch()) {
                QString idString = match.captured(1);
                ardid = idString.toInt();
                qDebug() << "Read_Data - ID reçu : " << ardid;

                recherche(QString::number(ardid)); // Convertir ardid en QString
            } else {
                qDebug() << "Read_Data - Erreur : Impossible d'extraire l'ID de la chaîne.";
            }

            qDebug() << "Read_Data - Données depuis le port série : " << Data_From_SerialPort;

            Data_From_SerialPort = "";
            Is_Data_Recevied = false;
        }
    }
}
