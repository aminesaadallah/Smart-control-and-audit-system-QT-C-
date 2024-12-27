#include "auditeurform.h"
#include "ui_auditeurform.h"
#include"clientform.h"
#include"rapportform.h"
#include"materielleform.h"
#include"normeform.h"
#include"generateurpdf.h"

Auditeurform::Auditeurform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Auditeurform)
{
    ui->setupUi(this);
    ui->tab_auditeur->setModel(a.afficher());
    //stat
    QMap<QString, QList<int>> sourceData = a.retrieveAuditeurData("auditeurs");

    QStringList sourceCategories = {"male", "femelle"};
    createPieChartPost(ui->chart_frame, "auditeurs gender Distribution", sourceCategories, sourceData);
    //arduino
    int ret=arduino.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< arduino.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<arduino.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";}
}

Auditeurform::~Auditeurform()
{
    delete ui;
}
//pour le menu
void Auditeurform::on_pushButton_2_clicked()
{
  Auditeurform a;
  this->hide();
  a.exec();

}

void Auditeurform::on_pushButton_3_clicked()
{
    Clientform cl;
    this->hide();
    cl.exec();

}

void Auditeurform::on_pushButton_4_clicked()
{
    Rapportform r;
    this->hide();
    r.exec();

}

void Auditeurform::on_pushButton_5_clicked()
{
    Materielleform m;
    this->hide();
    m.exec();

}

void Auditeurform::on_pushButton_6_clicked()
{
    Normeform n;
     this->hide();
    n.exec();

}

/////fin menu
QString Auditeurform::cleanString(const QString &inputString) {
    // Remove leading and trailing spaces
    QString trimmedString = inputString.trimmed();

    // Replace multiple consecutive spaces with a single space
    trimmedString.replace(QRegularExpression("\\s+"), " ");

    return trimmedString;
}
void Auditeurform::on_pb_ajouter_clicked()
{

    int id_auditeur = ui->le_id->text().toInt();
    QString nom_auditeur = ui->le_nom->text();
    QString mail_auditeur = ui->le_mail->text();
    QString tel_auditeur = ui->le_tel->text();
    QString mdp_auditeur = ui->le_mdp->text();
    QString genre_auditeur = ui->le_genre->currentText();

    qDebug()<< id_auditeur << nom_auditeur << mail_auditeur << tel_auditeur << mdp_auditeur ;

    Auditeur  a( id_auditeur,nom_auditeur,mail_auditeur,tel_auditeur,mdp_auditeur, genre_auditeur);

    bool test = a.ajouter();
    if (test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué\n"
                            "Click ok to exit ."), QMessageBox :: Ok);
        ui->tab_auditeur->setModel(a.afficher());

        //stat
        loadChart("genre");
    }
    else
        QMessageBox:: critical(nullptr, QObject::tr("Not OK"),
                               QObject::tr("Ajout non effectué .\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
}

void Auditeurform::on_pb_supprimer_clicked()
{
    Auditeur a;
    a.setid_auditeur(ui->le_id->text().toInt());
    bool test=a.supprimer(a.get_id_auditeur());
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                            QObject::tr("Suppression effectué\n"
                                                        "Click ok to exit ."), QMessageBox :: Ok);
        ui->tab_auditeur->setModel(a.afficher());

        //stat
        loadChart("genre");
    }
    else
        QMessageBox:: critical(nullptr, QObject::tr("Not OK"),
                                             QObject::tr("Suppression non effectué .\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);
}

void Auditeurform::on_pb_recherche_clicked()
{
    QString to_search_str = cleanString(ui->le_id->text());
    QString to_search_type_str = "id_auditeur";

    qDebug() << to_search_str;

    if (to_search_str != ""){
        //qDebug() << to_search_str;

        //searchs data and puts it in the table
        //addDataToTableView1(a.searchData("Auditeurs", to_search_type_str, to_search_str));

    }
    else{

        //reload data to the table
       // addDataToTableView1(a.retrieveAllDataAsList("Auditeurs"));
    }

    /*
    int id_materiel_audite = ui->pb_recherche->text().toInt();
    QSqlQueryModel* searchResults = a.rechercher(id_materiel_audite);
    ui->tableView_rech->setModel(searchResults);
    */
}

void Auditeurform::on_pb_modifier_clicked()
{
    qDebug() << "mod";
       int id_auditeur=ui->le_id->text().toInt();
       QString nom_auditeur=ui->le_nom->text();
       QString mail_auditeur=ui->le_mail->text();
       QString tel_auditeur=ui->le_tel->text();
       QString mdp_auditeur=ui->le_mdp->text();
       QString genre_auditeur = ui->le_genre->currentText();

       qDebug()<< id_auditeur << nom_auditeur << mail_auditeur << tel_auditeur << mdp_auditeur ;

       Auditeur a(id_auditeur,nom_auditeur,mail_auditeur,tel_auditeur,mdp_auditeur, genre_auditeur);

       bool test=a.modifier(id_auditeur);
       if (test){

           QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("modifier avec success.\n"
                                   "Click ok to exit."), QMessageBox::Ok);
          // addDataToTableView(a.retrieveAllDataAsList("auditeurs"));
           ui->tab_auditeur->setModel(a.afficher());

           //stat
           loadChart("genre");
       }
       else
           QMessageBox::critical(nullptr, QObject::tr("not ok"),
                       QObject::tr(" modifier non effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}

void Auditeurform::on_pb_pdf_clicked()
{
    QString nomFichierPDF = QFileDialog::getSaveFileName(this, "Enregistrer PDF", "", "Fichiers PDF (*.pdf)");

            if (!nomFichierPDF.isEmpty()) {
                QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tab_auditeur->model());

                if (model) {
                    GenerateurPDF::genererPDF(model, nomFichierPDF);
                } else {
                    QMessageBox::warning(this, "Erreur", "Le modèle n'est pas de type QSqlQueryModel.");
                }
            }
}

void Auditeurform::on_pushButton_clicked()
{
    Auditeur a;
                   QSqlQueryModel *model = a.tri();
                   ui->tab_auditeur->setModel(model);
}

//pdf
bool Auditeurform::exportDataToPDF(const QString& filePath)
{
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tab_auditeur->model());

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

    //qDebug() << "Data exported to PDF successfully!";

    return true;
}

QString Auditeurform::getSaveFilePath(QWidget *parent, QString file_type) {
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

//stat
void Auditeurform::createPieChartPost(QFrame *frame, const QString &title, QStringList postCategories, const QMap<QString, QList<int>> &data) {
    QPieSeries *series = new QPieSeries();

    // Iterate through the post categories in the desired order
    for (const QString &postCategory : postCategories) {
        if (data.contains(postCategory)) {
            const QList<int> &categoryData = data[postCategory];
            int categorySum = 0;

            for (int value : categoryData) {
                categorySum += value;
            }

            // Create a label with the category name and the number of data points
            QString sliceLabel = QString("%1 (%2)").arg(postCategory).arg(categorySum);
            QPieSlice *slice = new QPieSlice(sliceLabel, categorySum);
            series->append(slice);
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Clear the existing contents of the frame
    QLayout *layout = frame->layout();
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0))) {
            delete item->widget();
            delete item;
        }
    }

    frame->layout()->addWidget(chartView);
}

void Auditeurform::loadChart(QString chartType){

    if (chartType == "genre") {
        QMap<QString, QList<int>> sourceData = a.retrieveAuditeurData("auditeurs");

        QStringList sourceCategories = {"male", "femelle"};
        createPieChartPost(ui->chart_frame, "auditeurs gender Distribution", sourceCategories, sourceData);
    }
}

