#include "clientform.h"
#include "ui_clientform.h"
#include "QMessageBox"
#include "client.h"
#include <QIntValidator>
#include <QSqlQuery>
#include <QtDebug>
#include"auditeurform.h"
#include"materielleform.h"
#include"rapportform.h"
#include"normeform.h"
QSqlQueryModel *model;
Clientform::Clientform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clientform)
{
    client clientInstance;
    ui->setupUi(this);
    ui->lineEdit_ID->setValidator(new QIntValidator(0,9999999,this));
    //ui->tab_cl->setModel(c.Afficher());
    addDataToTableView(c.retrieveAllDataAsList("clients"));

    //stat
    loadChart("clientAdrs");

    //calander
    QString x=ui->calendarWidget->selectedDate().toString();
    ui->lineEdit_date->setText(x);

    QDate x1 = ui->calendarWidget->selectedDate();
    addDataToTableView2(clientInstance.retrieveAllCalanderDataAsList("clients", x1));
}

Clientform::~Clientform()
{
    delete ui;
}
//pour le menu
void Clientform::on_pushButton_2_clicked()
{
  Auditeurform a;
   this->hide();
  a.exec();

}

void Clientform::on_pushButton_3_clicked()
{
    Clientform cl;
     this->hide();
    cl.exec();

}

void Clientform::on_pushButton_4_clicked()
{
    Rapportform r;
     this->hide();
    r.exec();

}

void Clientform::on_pushButton_5_clicked()
{
    Materielleform m;
     this->hide();
    m.exec();

}

void Clientform::on_pushButton_6_clicked()
{
    Normeform n;
     this->hide();
    n.exec();

}

/////fin menu
void Clientform::on_pushButton_ajouter_clicked()
{

   QString ID_client=ui->lineEdit_ID->text();
   QString num_client=ui->lineEdit_num->text();
   QString nomcl=ui->lineEdit_nom->text();
   QString adressecl=ui->lineEdit_adresse->text();
   QString adresseEmail=ui->lineEdit_adresseE->text();
   QString dateEm=ui->lineEdit_dateEm->text();
   QString dateAud=ui->lineEdit_dateAud->text();
   client c(adresseEmail, adressecl, nomcl, dateEm, dateAud, ID_client, num_client);

    bool test=c.Ajouter();
if (test)
{
     //ui->tab_cl->setModel(c.Afficher());
    addDataToTableView(c.retrieveAllDataAsList("clients"));
    loadChart("clientAdrs");
    QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajout effectué\n" "click cancel to exit."),QMessageBox::Cancel);

    ui->lineEdit_ID->setText("");
    ui->lineEdit_num->setText("");
    ui->lineEdit_nom->setText("");
    ui->lineEdit_adresse->setText("");
    ui->lineEdit_adresseE->setText("");
    ui->lineEdit_dateEm->setDate(QDate::fromString("1/1/2000", "M/d/yyyy"));
    ui->lineEdit_dateAud->setDate(QDate::fromString("1/1/2000", "M/d/yyyy"));
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("ok"),QObject::tr("ajout non effectué\n" "click cancel to exit."),QMessageBox::Cancel);

        }
}

void Clientform::addDataToTableView(const QList<QMap<QString, QString>>& dataList)
{
    QStandardItemModel* model = new QStandardItemModel(this);

        // Define the desired column order
        QStringList columnOrder = {"id_client", "nom_client", "adresse_client", "num_client", "adresseemaill", "date_aud", "date_email"};

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

        ui->tab_cl->setModel(model);
}

void Clientform::on_pushButton_supprimer_clicked()
{
QString ID=ui->lineEdit_ID->text();
bool test=c.Supprimer(ID);
 if(test)
 {
    //ui->tab_cl->setModel(c.Afficher());
     addDataToTableView(c.retrieveAllDataAsList("clients"));
     loadChart("clientAdrs");
     QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("supression effectuée.\n" "click cancel to exit."),QMessageBox::Cancel);

     ui->lineEdit_ID->setText("");
     ui->lineEdit_num->setText("");
     ui->lineEdit_nom->setText("");
     ui->lineEdit_adresse->setText("");
     ui->lineEdit_adresseE->setText("");
     ui->lineEdit_dateEm->setDate(QDate::fromString("1/1/2000", "M/d/yyyy"));
     ui->lineEdit_dateAud->setDate(QDate::fromString("1/1/2000", "M/d/yyyy"));
  }
  else
  {
     QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("suppression non effectuée.\n" "clicked cancel to exit."),QMessageBox::Cancel);
  }
}

QString Clientform::cleanString(const QString &inputString) {
    // Remove leading and trailing spaces
    QString trimmedString = inputString.trimmed();

    // Replace multiple consecutive spaces with a single space
    trimmedString.replace(QRegularExpression("\\s+"), " ");

    return trimmedString;
}

void Clientform::addDataToTableView1(const QList<QMap<QString, QString>>& dataList)
{
    QStandardItemModel* model = new QStandardItemModel(this);

        // Define the desired column order
        QStringList columnOrder = {"id_client", "nom_client", "adresse_client", "num_client", "adresseemaill", "date_aud", "date_email"};

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

        ui->tab_cl->setModel(model);
}

void Clientform::on_pushButton_Rechercher_clicked()
{


        // Get the search ID from a QLineEdit or QSpinBox, assuming you have an input field named 'idLineEdit'
        QString to_search_str = cleanString(ui->lineEdit_ID->text());
        client c;

        if (to_search_str != ""){
            //qDebug() << to_search_str;

            //searchs data and puts it in the table
            addDataToTableView1(c.searchData("clients", "id_client", to_search_str));

        }
        else{

            //reload data to the table
            addDataToTableView1(c.retrieveAllDataAsList("clients"));
        }

        if (!c.checkIdExists(to_search_str)){
            QMessageBox::warning(this, "Search Result", "Record not found for ID is like : " + to_search_str);
        }


}

void Clientform::on_okButton_clicked()
{
    // Récupérez les valeurs modifiées depuis les champs d'interface utilisateur
    QString ID_client = ui->lineEdit_ID->text();
    QString num_client=ui->lineEdit_num->text();
    QString dateAud = ui->lineEdit_dateAud->text();
    QString dateEm = ui->lineEdit_dateEm->text();
    QString nomcl =ui->lineEdit_nom->text();
    QString adressecl =ui->lineEdit_adresse->text();
    QString adresseEmail=ui->lineEdit_adresseE->text();
    //qDebug() << "data 1 :" << id << titre << datedecreation << typeequipement << datemodification << languetraduction ;



    // Créez un objet client avec les nouvelles valeurs
   client c(adresseEmail, adressecl, nomcl, dateEm, dateAud, ID_client, num_client);

    // Utilisez la fonction Modifier pour mettre à jour les données dans la base de données
    if (c.Modifier()) {
        // Mise à jour réussie
        QMessageBox::information(nullptr, QObject::tr("Modification réussie"), QObject::tr("Le rapport a été modifié avec succès."), QMessageBox::Ok);
        // Mettez à jour le modèle si vous utilisez un QTableView
        // model->setQuery("SELECT * FROM client");
        //ui->tab_cl->setModel(c.Afficher());
        addDataToTableView(c.retrieveAllDataAsList("clients"));
        loadChart("clientAdrs");

        ui->lineEdit_ID->setText("");
        ui->lineEdit_num->setText("");
        ui->lineEdit_nom->setText("");
        ui->lineEdit_adresse->setText("");
        ui->lineEdit_adresseE->setText("");
        ui->lineEdit_dateEm->setDate(QDate::fromString("1/1/2000", "M/d/yyyy"));
        ui->lineEdit_dateAud->setDate(QDate::fromString("1/1/2000", "M/d/yyyy"));

    } else {
        // Gérez l'erreur si la mise à jour échoue
        QMessageBox::critical(nullptr, QObject::tr("Erreur de modification"), QObject::tr("Erreur lors de la modification du rapport."), QMessageBox::Ok);
    }
}

void Clientform::on_pushButton_sort_clicked()
{
    addDataToTableView(c.retrieveAllDataAsListSorted("clients", "id_client"));
}

bool Clientform::exportDataToPDF(const QString& filePath)
{
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->tab_cl->model());

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

QString Clientform::getSaveFilePath(QWidget *parent, QString file_type) {
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

void Clientform::on_pushButton_exporter_clicked()
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

              //open the file

              if (QDesktopServices::openUrl(folderUrl)) {
                  qDebug() << "Folder opened successfully.";
              } else {
                  qDebug() << "Failed to open folder.";
              }



              //qDebug() << "file exported";
          }
       }
}


//stat
void Clientform::createPieChartPost(QFrame *frame, const QString &title, QStringList postCategories, const QMap<QString, QList<int>> &data) {
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

void Clientform::loadChart(QString chartType){
    client c;

    if (chartType == "clientAdrs") {
        QMap<QString, QList<int>> sourceData = c.retrieveAdrsData("clients");

        QStringList sourceCategories = c.retrieveAllClientsIds("clients");
        createPieChartPost(ui->chart_frame, "Distribution of Clients by Location", sourceCategories, sourceData);
    }
}


//mail
bool Clientform::verifMail(){
    QString to_verify = "";
    QString error_txt = "";
    QRegExp rxRule;

    ///verif the email
    to_verify = ui->email_inp->text();
    // Regular expression pattern to match alphabets only
    rxRule = QRegExp("^[A-Za-z0-9+_.-]+@[^@]+\\.[A-Za-z]{2,}$");

    // Check if the first name matches the pattern
    if (!rxRule.exactMatch(to_verify)) {
        error_txt = "Invalid email address. Please enter a valid email address.";
        ui->mail_error_lb->setText(error_txt);
        return false;
    }

    ///verif subject
    to_verify = ui->subject_inp->text();
    if (to_verify == ""){
        error_txt = "Invalid subject. Subject can't be empty.";
        ui->mail_error_lb->setText(error_txt);
        return false;
    }
    ///verif msg
    to_verify = ui->msg_inp->toPlainText();
    if (to_verify == ""){
        error_txt = "Invalid message. message can't be empty.";
        ui->mail_error_lb->setText(error_txt);
        return false;
    }

    ui->mail_error_lb->setText(error_txt);
    return true;
}

void Clientform::on_mail_send_btn_clicked()
{
    if (verifMail()){
        bool res = mailer.sendMailNormal(ui->email_inp->text(), ui->subject_inp->text(), ui->msg_inp->toPlainText());

        if (res){
            QMessageBox::information(nullptr, QObject::tr("mail sent successfully"),
                        QObject::tr("mail sent successfully.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else{
            QMessageBox::critical(nullptr, QObject::tr("error sending the mail"),
                        QObject::tr("error sending the mail.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
}


//calander
void Clientform::addDataToTableView2(const QList<QMap<QString, QString>>& dataList)
{
    QStandardItemModel* model = new QStandardItemModel(this);

        // Define the desired column order
        QStringList columnOrder = {"id_client", "nom_client", "adresse_client", "num_client", "adresseemaill", "date_aud", "date_email"};

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

        ui->cal_tabView->setModel(model);
}




void Clientform::on_calendarWidget_selectionChanged()
{
    client c;

    QString x=ui->calendarWidget->selectedDate().toString();

    ui->lineEdit_date->setText(x);

    QDate x1 = ui->calendarWidget->selectedDate();
    addDataToTableView2(c.retrieveAllCalanderDataAsList("clients", x1));
}

void Clientform::on_tab_cl_clicked(const QModelIndex &index)
{
    QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(ui->tab_cl->model());

    if (model && index.isValid()) {
        int row = index.row();
        int col = index.column(); // Get the clicked column index

        QMap<QString, QString> rowData; // Create a QMap to store the data
        int numColumns = model->columnCount();

        for (int col = 0; col < numColumns; ++col) {
            QStandardItem* item = model->item(row, col);
            if (item) {
                QString columnName = model->horizontalHeaderItem(col)->text().toLower();
                rowData[columnName] = item->text();
            }
        }

        //fill the data fields
        ui->lineEdit_ID->setText(rowData["id_client"]);
        ui->lineEdit_num->setText(rowData["num_client"]);
        ui->lineEdit_nom->setText(rowData["nom_client"]);
        ui->lineEdit_adresse->setText(rowData["adresse_client"]);
        ui->lineEdit_adresseE->setText(rowData["adresseemaill"]);
        ui->lineEdit_dateEm->setDate(QDate::fromString(rowData["date_email"], "M/d/yyyy"));
        ui->lineEdit_dateAud->setDate(QDate::fromString(rowData["date_aud"], "M/d/yyyy"));



    }

}

void Clientform::on_pushButton_tri_clicked()
{

    QString to_search_type_str = (ui->client_tri_par_type_inp->currentText()).replace(' ', '_');

    addDataToTableView(clientInstance.retrieveAllDataAsListSorted("clients", to_search_type_str));
}
