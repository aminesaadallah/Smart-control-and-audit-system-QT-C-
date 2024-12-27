#include "materielleform.h"
#include "ui_materielleform.h"
#include "materiel_audite.h"
#include "QrCodeGenerator.h"

#include <QPainter>
#include <QImageWriter>
#include <QIntValidator>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QTableView>
#include <QStandardItem>
#include <QDesktopServices>
#include <QTextTableCell>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QSqlQueryModel>
#include<QModelIndexList>
#include <QByteArray>
#include<QScrollArea>
#include<QBuffer>

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMovie>
#include <QtGui>
#include <QtWidgets/QMainWindow>

#include<QtCharts>
#include <QPrinter>
#include <QChartView>
#include <QChart>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>
#include"auditeurform.h"
#include"clientform.h"
#include"rapportform.h"
#include"normeform.h"
Materielleform::Materielleform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Materielleform)
{
    ui->setupUi(this);
    ui->lineEdit_id_materiel_audite->setValidator(new QIntValidator(100, 9999, this));
    ui->tab_afficher_equipement->setModel(m.afficher());
    ui->tableView_chercher->setModel(m.afficher());
}

Materielleform::~Materielleform()
{
    delete ui;
}
//pour le menu
void Materielleform::on_pushButton_2_clicked()
{
  Auditeurform a;
   this->hide();
  a.exec();

}

void Materielleform::on_pushButton_3_clicked()
{
    Clientform cl;
    this->hide();
    cl.exec();

}

void Materielleform::on_pushButton_4_clicked()
{
    Rapportform r;
    this->hide();
    r.exec();

}

void Materielleform::on_pushButton_5_clicked()
{
    Materielleform m;
    this->hide();
    m.exec();

}

void Materielleform::on_pushButton_6_clicked()
{
    Normeform n;
    this->hide();
    n.exec();

}

/////fin menu

void Materielleform::setGallery(){

    /// Create a scroll area
    //not done yet
    QScrollArea *scrollArea = new QScrollArea(ui->centralwidget);
    scrollArea->setWidgetResizable(true);

    /// Create a widget to hold the buttons and labels
    //not done yet
    QWidget *scrollWidget = new QWidget(scrollArea);
    verticalLayout = new QVBoxLayout(scrollWidget);

    //get data from the data base
    EquipementData =  cnx.retrieveAllDataAsList("MATERIEL_AUDITE");

    for (const auto &map : EquipementData) {
            qDebug() << "Map:";
            for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
                qDebug() << "  Key:" << it.key().toLower() << "  Value:" << it.value();
            }
        }
    //creating cards
    for (const auto &map : EquipementData) {

         equipement_id = map["id_equipement"];
         equipement_name = map["nom_equipement"];
         date_achat = map["date_achat"];
         numero_serie = map["numero_serie"];
         emplacement = map["emplacement"];

         createButtonWithLabels(verticalLayout, map);


    }


    /// Set the layout of the scroll widget
    //note done yet
    scrollWidget->setLayout(verticalLayout);

    /// Set the widget for the scroll area
    //note done yet
    scrollArea->setWidget(scrollWidget);
    /// Set the layout of the central widget
    //note done yet

    QVBoxLayout *mainLayout = ui->EquipementFrame;//new QVBoxLayout(ui->centralWidget);

    //clear the old stuff before adding
    QLayoutItem *child;
    while ((child = mainLayout->takeAt(0)) != nullptr) {
        delete child->widget(); // This deletes the widget associated with the layout item
        delete child;           // This deletes the layout item itself
    }

    //adding
    mainLayout->addWidget(scrollArea);
}



void Materielleform::on_pushButton_ajouter_clicked()
{
    int id_materiel_audite=ui->lineEdit_id_materiel_audite->text().toInt();
    QString nom_materiel_audite=ui->lineEdit_nom_materiel_audite->text();
    QString date_achat=ui->lineEdit_date_achat->text();
    QString status=ui->lineEdit_status->text();
    QString numero_serie=ui->lineEdit_numero_serie->text();
    QString emplacement=ui->lineEdit_emplacement->text();
    QString responsable_equipement=ui->lineEdit_responsable_equipement->text();
    QString imageV=ui->lineEdit_photo->text();

    QFile imageFile(imageV);
    if (!imageFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Erreur: impossible d'ouvrir le fichier d'image";
        return;
    }
    // Lire les données de l'image à partir du fichier
    QByteArray imageData = imageFile.readAll();


    Materiel_audite  m( id_materiel_audite,nom_materiel_audite,date_achat,status,numero_serie,emplacement,responsable_equipement,imageData);

    bool test=m.ajouter();
    if(test)
    {
        ui->tab_afficher_equipement->setModel(m.afficher());
        ui->tableView_chercher->setModel(m.afficher());

        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                            QObject::tr("Ajout effectué\n"
                                                        "click cancel to exit."),QMessageBox::Cancel);

        QString chemin_image=ui->lineEdit_photo->text();

        QString repertoire="C:/"+m.get_status()+"_"+m.get_nom_materiel_audite();


        QDir dossier;

        if(!dossier.mkdir(repertoire))
            qWarning() << "Impossible de créer le dossier";

        QString destination=QString("%2/%3").arg(repertoire).arg(QFileInfo(chemin_image).fileName());

        if(!QFile::copy(chemin_image,destination))
        {
            qWarning() << "Impossible de copier l'image";
            return;
        }
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Image créée avec succès\n"
                                             "cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
}
else
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                            QObject::tr("Ajout non effectué.\n"
                                       "click Cancel to exit."),QMessageBox::Cancel);

}

void Materielleform::on_pushButton_supprimer_clicked()
{
    Materiel_audite m;
    m.setid_materiel_audite(ui->lineEdit_chercher->text().toInt());
    bool test=m.supprimer(m.get_id_materiel_audite());
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                            QObject::tr("Suppression effectué\n"
                                                        "Click ok to exit ."), QMessageBox :: Ok);
        ui->tab_afficher_equipement->setModel(m.afficher());
        ui->tab_afficher_equipement->setModel(m.afficher());

    }
    else
        QMessageBox:: critical(nullptr, QObject::tr("Not OK"),
                                             QObject::tr("Suppression non effectué .\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);
    }

void Materielleform::on_pushButton_mod_clicked()
{
    int id_materiel_audite = ui->lineEdit_id_materiel_audite->text().toInt();
    QString nom_materiel_audite = ui->lineEdit_nom_materiel_audite->text();
    QString date_achat = ui->lineEdit_date_achat->text();
    QString status = ui->lineEdit_status->text();
    QString numero_serie = ui->lineEdit_numero_serie->text();
    QString emplacement = ui->lineEdit_emplacement->text();
    QString responsable_equipement = ui->lineEdit_responsable_equipement->text();
    QString imageV = ui->lineEdit_photo->text();

    QFile imageFile(imageV);
    if (!imageFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error: Unable to open the image file";
        return;
    }

    // Read the image data from the file
    QByteArray imageData = imageFile.readAll();

    Materiel_audite m(id_materiel_audite, nom_materiel_audite, date_achat, status, numero_serie, emplacement, responsable_equipement, imageData);

    bool test = m.modifier(id_materiel_audite);
    if (test)
    {
        ui->tab_afficher_equipement->setModel(m.afficher());
                  ui->tableView_chercher->setModel(m.afficher());
                  QMessageBox::information(nullptr, QObject::tr("ok"),
                              QObject::tr("modifier avec success.\n"
                                          "Click ok to exit."), QMessageBox::Ok);    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Modifier non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}


void Materielleform::on_pushButton_rech_clicked()
{
    Materiel_audite materiel_audite;
            int id_materiel_audite = ui->lineEdit_chercher->text().toInt();


            QSqlQueryModel *result = materiel_audite.rechercher(id_materiel_audite);

            ui->tab_afficher_equipement->setModel(result);
    }


void Materielleform::on_pushButton_tri_clicked()
{
    Materiel_audite m;
               QSqlQueryModel *model = m.tri();
               ui->tab_afficher_equipement->setModel(model);
}


void Materielleform::on_pushButton_pdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
        if (fileName.isEmpty()) {
            return;
        }

        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        QTextCursor cursor(&doc);

        // En-tête du document
        QTextCharFormat headerFormat;
        headerFormat.setFontPointSize(14);
        headerFormat.setFontWeight(QFont::Bold);
        cursor.setCharFormat(headerFormat);
        cursor.insertText("Liste des equipement\n\n");

        // Crée un tableau avec des colonnes pour chaque champ de la table
          QTextTableFormat tableFormat;
          tableFormat.setAlignment(Qt::AlignLeft);
          QTextTable *table = cursor.insertTable(1, 7, tableFormat);
          QTextCursor cellCursor;

          // Remplir les en-têtes de colonne
          cellCursor = table->cellAt(0, 0).firstCursorPosition();
          cellCursor.insertText("identifiant equipement");

          cellCursor = table->cellAt(0, 1).firstCursorPosition();
          cellCursor.insertText("nom equipement");

          cellCursor = table->cellAt(0, 2).firstCursorPosition();
          cellCursor.insertText("Date d'achat");

          cellCursor = table->cellAt(0, 3).firstCursorPosition();
          cellCursor.insertText("status equipement ");

          cellCursor = table->cellAt(0, 4).firstCursorPosition();
          cellCursor.insertText("numero de serie  ");

          cellCursor = table->cellAt(0, 5).firstCursorPosition();
          cellCursor.insertText("emplacement ");

          cellCursor = table->cellAt(0, 6).firstCursorPosition();
          cellCursor.insertText("responsable equipement ");



          // Obtain the client data from your table model
          QSqlQueryModel *model = static_cast<QSqlQueryModel*>(ui->tableView_chercher->model());

          // Fill the table data
          for (int row = 0; row < model->rowCount(); ++row) {
              table->appendRows(1);

              for (int col = 0; col < 7; ++col) {
                  cellCursor = table->cellAt(row + 1, col).firstCursorPosition();
                  cellCursor.insertText(model->data(model->index(row, col)).toString());
              }
          }

          doc.print(&printer);

          QMessageBox::information(this, "Succès", "Liste des commandes exportée sous forme de PDF.");



}

void Materielleform::on_pushButton_stat_clicked()
{
    // Assuming you have an instance of Materiel_audite as a member variable
        QString statistics = m.statistiqueparstatus();

        // Display the statistics in the debug output
        qDebug() << "Equipment Statistics:\n" << statistics;



}



void Materielleform::on_tab_afficher_equipement_clicked(const QModelIndex &index)
{
    if (index.isValid()) {

           QSqlQueryModel *model = qobject_cast<QSqlQueryModel *>(ui->tab_afficher_equipement->model());


           if (model) {

            //   QModelIndex firstColumnIndex = model->index(index.row(), 0);


               QStringList donneesLigne;
               for (int col = 0; col < model->columnCount(); ++col) {
                   QModelIndex cellIndex = model->index(index.row(), col);
                   donneesLigne << model->data(cellIndex).toString();
               }


               QString donnees = donneesLigne.join(" ");


               QrCodeGenerator generateurQR;
               QImage qrCodeImage = generateurQR.generateQr(donnees, 200);




               QMessageBox msgBox;
                           msgBox.setIconPixmap(QPixmap::fromImage(qrCodeImage));
                           msgBox.exec();        }
       }
}

QString Materielleform::selectImageFile() {
    QString imagePath = QFileDialog::getOpenFileName(nullptr, "Select Image", QDir::homePath(), "Images (*.png *.jpg *.jpeg *.bmp *.gif)");

    if (imagePath.isEmpty()) {
        qDebug() << "No image selected.";
    } else {
        qDebug() << "Selected image: " << imagePath;
    }

    return imagePath;
}

QByteArray Materielleform::loadImageData(const QString &filePath) {
    QImage image(filePath);

    if (image.isNull()) {
        qDebug() << "Error: Invalid image file";
        return QByteArray();
    }

    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);

    QString fileExtension = QFileInfo(filePath).suffix().toLower();

    if (fileExtension == "jpg" || fileExtension == "jpeg") {
        image.save(&buffer, "JPG");
    } else if (fileExtension == "png") {
        image.save(&buffer, "PNG");
    } else if (fileExtension == "bmp") {
        image.save(&buffer, "BMP");
    } else if (fileExtension == "gif") {
        image.save(&buffer, "GIF");
    } else {
        qDebug() << "Error: Unsupported image format";
        return QByteArray();
    }

    return imageData;
}


void Materielleform::loadImageFromDatabase(QString id_materiel_audite, QLabel *label) {

    int maxWidth, maxHeight;
    maxWidth = 200;
    maxHeight = 200;

    // Retrieve image data from the database based on product ID
    QByteArray imageData = m.loadImageDataFromDatabase(id_materiel_audite, "MATERIEL_AUDITE");


    // Check if the image data is valid
    if (imageData.isEmpty()) {
        qDebug() << "Error: Unable to retrieve image data from the database";
        //return;
    }

    // Convert the image data to a QImage
    QImage image;
    if (!imageData.isEmpty()){
        image.loadFromData(imageData);
    }
    else{
        image.load(":/images/not_found_img.png");
    }

    // Check if the image is valid
    if (image.isNull()) {
        qDebug() << "Error: Invalid image data";
        return;
    }

    // Scale the image to the specified maximum width and height
    image = image.scaled(maxWidth, maxHeight, Qt::KeepAspectRatio);


    // Display the image in the provided QLabel or another widget
    label->setPixmap(QPixmap::fromImage(image));
    label->setScaledContents(true);
}


void Materielleform::createButtonWithLabels(QVBoxLayout *verticalLayout, QMap<QString, QString> map)
{
    QLabel *label0 = new QLabel("id_materiel_audite : "+map["id_equipement"], this);
    QLabel *label1 = new QLabel("nom_materiel_audite : "+map["nom_equipement,"], this);
    QLabel *label2 = new QLabel("date_achat : "+map["date_achat"], this);
    QLabel *label3 = new QLabel("numero_serie : "+map["numero_serie"], this);
    QLabel *label4 = new QLabel("emplacement : "+map["emplacement"], this);
    QLabel *labelSpacing = new QLabel(this);

    QLabel *labelImg = new QLabel(this);
    loadImageFromDatabase(map["id_equipement"], labelImg);

    // Set accessibleName for button and labels
    label0->setAccessibleName("idLabel");
    label1->setAccessibleName("nameLabel");
    label2->setAccessibleName("date_achatLabel");
    label3->setAccessibleName("numero_serieLabel");
    label4->setAccessibleName("emplacement_Label");
    labelSpacing->setAccessibleName("spacingLabel");
    labelImg->setAccessibleName("imgLabel");


    // Create a horizontal layout to hold the button and labels
    QVBoxLayout *dataLayout = new QVBoxLayout;

    QHBoxLayout *dataRow0Layout = new QHBoxLayout;
    dataRow0Layout->addWidget(label0, 0);
    dataLayout->addLayout(dataRow0Layout);

    QVBoxLayout *dataRow1Layout = new QVBoxLayout;
    dataRow1Layout->addWidget(labelImg, 0);
    dataLayout->addLayout(dataRow1Layout);

    QHBoxLayout *dataRow2Layout = new QHBoxLayout;
    dataRow2Layout->addWidget(label1, 0);
    dataRow2Layout->addWidget(label2, 0);
    dataLayout->addLayout(dataRow2Layout);

    QHBoxLayout *dataRow3Layout = new QHBoxLayout;
    dataRow3Layout->addWidget(label3, 0);
    dataRow3Layout->addWidget(label4, 0);
    dataLayout->addLayout(dataRow3Layout);

    QHBoxLayout *dataRow4Layout = new QHBoxLayout;
    dataRow4Layout->addWidget(labelSpacing, 0);
    dataLayout->addLayout(dataRow4Layout);



    // Add the horizontal layout to the vertical layout
    verticalLayout->addLayout(dataLayout);

}



/*
void MainWindow::on_pushButton_ajout_image_clicked()
{
    QString imagePath = selectImageFile();
        imageData = loadImageData(imagePath);
        QFileInfo fileInfo(imagePath);
        QString fileName = fileInfo.fileName();

        ui->lineEdit_ajout_image->setText(fileName);

}
*/
void Materielleform::on_pushButton_mod_image_clicked()
{
    QString file = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image",QDir::homePath(), "Images (*.png *.xpm *.jpg *.jpeg)");
    ui->lineEdit_photo->setText(file);

}
//test image
void Materielleform::on_boutton_verifier_image_vehicule_clicked()
{
    Materiel_audite m;
    QString id_materiel_audite=ui->lineEdit_chercher->text();
    QString chemin_dossier;
    QSqlQuery query;

    if(id_materiel_audite!="" && m.chercher_materiel_audite(id_materiel_audite))
    {
        query.prepare("SELECT * FROM MATERIEL_AUDITE WHERE id_materiel_audite=:id_materiel_audite");
        query.bindValue(":id_materiel_audite",id_materiel_audite);
        query.exec();

        QString ID_MATERIEL_AUDITE=query.value(0).toString().simplified();
        QString NOM_MATERIEL_AUDITE=query.value(1).toString().simplified();
        QString DATE_ACHAT=query.value(2).toString().simplified();
        QString STATUS=query.value(3).toString().simplified();
        QString NUMERO_SERIE=query.value(4).toString().simplified();
        QString EMPLACEMENT=query.value(5).toString().simplified();
        QString RESPONSABLE_EQUIPEMENT=query.value(6).toString().simplified();


    QDir dir("C:/");
        QStringList dirs = dir.entryList();
        for (const auto& d : dirs)
        {
            if (d.startsWith(id_materiel_audite))
            {
                chemin_dossier=d;
            }
        }
        chemin_dossier="C:/"+chemin_dossier;
          QDir dossier(chemin_dossier);

          QStringList filters;
              filters << "*.jpg" << "*.jpeg" << "*.png" << "*.gif";
              qDebug()<<filters[0];
               dossier.setNameFilters(filters);

                QFileInfoList files = dossier.entryInfoList();
               QString chemin_complet=chemin_dossier+"/"+files[0].fileName();
               QPixmap pixmap(chemin_complet);
               QChart *chart = new QChart();

               QChartView *chartView = new QChartView(chart);

               QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
               QGraphicsScene *scene = new QGraphicsScene(chartView);
               scene->addItem(item);

               // Ajouter la scène au QGraphicsView
               chartView->setScene(scene);
               chartView->show();


    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Matricule est invalide.\n"
                                      "click Cancel to exit."),QMessageBox::Cancel);


    qDebug()<<m.encrypt("01234");
}

void Materielleform::on_boutton_choisir_image_vehicule_clicked()
{
    QString file = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image",QDir::homePath(), "Images (*.png *.xpm *.jpg *.jpeg)");
    ui->lineEdit_photo->setText(file);
}

#include <qDebug>


//image

void Materielleform::on_tableView_chercher_activated(const QModelIndex &index)
{
    Materiel_audite m;
    ui->tableView_chercher->setModel(m.afficher());
       QString val=ui->tableView_chercher->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("select * from MATERIEL_AUDITE where id_materiel_audite=:val");
        query.bindValue(":val",val);
        query.exec() ;
        qDebug()<<"nn";
        if (query.next() )
        {   qDebug()<<"oui";
            QByteArray imagedata=query.value(7).toByteArray();
            QPixmap image;
            image.loadFromData(imagedata);
            ui->imagedata->setPixmap(image);
        }
}
