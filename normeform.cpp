#include "normeform.h"
#include "ui_normeform.h"
#include"auditeurform.h"
#include"clientform.h"
#include"rapportform.h"
#include"materielleform.h"
Normeform::Normeform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Normeform)
{
    ui->setupUi(this);
    ui->tableView->setModel(N.afficher());
    ui->lineEdit_titre->setMaxLength(20);
    ui->lineEdit_titre->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+")));
}

Normeform::~Normeform()
{
    delete ui;
}
//pour le menu
void Normeform::on_pushButton_2_clicked()
{
  Auditeurform a;
   this->hide();
  a.exec();

}

void Normeform::on_pushButton_3_clicked()
{
    Clientform cl;
    this->hide();
    cl.exec();

}

void Normeform::on_pushButton_4_clicked()
{
    Rapportform r;
      this->hide();
    r.exec();

}

void Normeform::on_pushButton_5_clicked()
{
    Materielleform m;
      this->hide();
    m.exec();

}

void Normeform::on_pushButton_6_clicked()
{
    Normeform n;
     this->hide();
    n.exec();

}

/////fin menu
void Normeform::on_pushButton_ajouter_clicked()
{
    QString titre=ui->lineEdit_titre->text();
    QString description=ui->textEdit_description->toPlainText();
    int etat;

    if(ui->radioButton_confirme->isChecked())
        etat=1;
    else
        etat=0;
    qDebug()<<etat;

    norme N(titre,description,etat);
    bool test=N.ajouter();

    if(test)
    {
        ui->tableView->setModel(N.afficher());

        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                           QObject::tr("Ajout effectué\n"
                                                                       "click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                         QObject::tr("Ajout non effectué.\n"
                                                     "click Cancel to exit."),QMessageBox::Cancel);
}

void Normeform::on_pushButton_supprimer_clicked()
{
    int numero=ui->lineEdit_supprimer->text().toInt();
    bool test=N.supprimer(numero);

    if(test)
         {

             ui->tableView->setModel(N.afficher());
             QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                 QObject::tr("Suppression effectué\n"
                                                             "click cancel to exit."),QMessageBox::Cancel);
              }
          else
              QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                    QObject::tr("Suppression non effectué.\n"
                                            "click Cancel to exit."),QMessageBox::Cancel);

         ui->lineEdit_supprimer->clear();
}

void Normeform::on_tableView_activated(const QModelIndex &index)
{
    norme N;

           ui->tableView->setModel(N.afficher());
           QString val=ui->tableView->model()->data(index).toString();
           QSqlQuery qry;
           qry.prepare("SELECT * FROM NORME WHERE NUMERO='"+val+"'");
           if(qry.exec())
           {
            while(qry.next())
            {
               ui->lineEdit_numero->setText(qry.value(0).toString());
             ui->lineEdit_titre->setText(qry.value(1).toString());
             ui->textEdit_description->setText(qry.value(2).toString());
             if(qry.value(3)==1)
                 ui->radioButton_confirme->setChecked(true);
             else
                 ui->radioButton_refuse->setChecked(true);
            }
           }
           else
           {
            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
           }
}

void Normeform::on_pushButton_modifier_clicked()
{
    int numero=ui->lineEdit_numero->text().toInt();
    QString titre=ui->lineEdit_titre->text();
    QString description=ui->textEdit_description->toPlainText();
    int etat;

    if(ui->radioButton_confirme->isChecked())
        etat=1;
    else
        etat=0;

    norme N(titre,description,etat);
    bool test=N.modifier(numero);
    if(test)
    {
        ui->tableView->setModel(N.afficher());
        QMessageBox:: information(nullptr, QObject::tr("MODIF"),
                                                  QObject::tr("Modifier effectué\n"
                                                  "click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("MODIF"),
                                                       QObject::tr("modifier non effectué.\n"
                                                       "click Cancel to exit."),QMessageBox::Cancel);

}

void Normeform::on_pushButton_PDF_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount =ui->tableView->model()->columnCount();

    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("Normes")
            <<  "</head>\n"
            "<body bgcolor=#75a2f0 link=#5000A0>\n"

                "<h1>Liste des Normes</h1>"

                "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
        out << "<thead><tr bgcolor=#f0f0f0>";

        for (int column = 0; column < columnCount; column++)
            {
                out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
            }

        out << "</tr></thead>\n";

        // data table
           for (int row = 0; row < rowCount; row++)
           {
               out << "<tr>";

               for (int column = 0; column < columnCount; column++)
                   {
                           QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                           out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));

                   }
               out << "</tr>\n";
           }

           out <<  "</table>\n"
                   "</body>\n"
                   "</html>\n";

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("Liste des normes.pdf");
        document->print(&printer);
}

void Normeform::on_radioButton_croissant_clicked()
{
    ui->tableView->setModel(N.tri_croissant());

}

void Normeform::on_radioButton_decroissant_clicked()
{
    ui->tableView->setModel(N.tri_decroissant());
}

void Normeform::on_pushButton_rechercher_clicked()
{
    int numero=ui->lineEdit_supprimer->text().toInt();

    ui->tableView->setModel(N.rechercher(numero));
}

void Normeform::on_pushButton_statistique_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    int confirme,nonconfirme;
    float pourcentage_nonconfirme,pourcentage_confirme,total;

    model->setQuery("SELECT * FROM NORME WHERE ETAT='1'");
    confirme=model->rowCount();

    model->setQuery("SELECT * FROM NORME WHERE ETAT='0'");
    nonconfirme=model->rowCount();

    total=confirme+nonconfirme;

    pourcentage_confirme=(confirme*100)/total;
    pourcentage_nonconfirme=(nonconfirme*100)/total;


    QString a=QString::number(pourcentage_confirme,'f',2);
    QString b=QString::number(pourcentage_nonconfirme,'f',2);

    a="Confirme: "+a+"%";
    b="NonConfirme: "+b+"%";


    QtCharts::QPieSeries  *series=new QtCharts::QPieSeries();

    series->append(a,confirme);
    series->append(b,nonconfirme);


    if(confirme!=0)
    {
        QtCharts::QPieSlice *slice= series->slices().at(0);
        slice->setLabelVisible();
        slice->setExploded(true);
    }

    if(nonconfirme!=0)
    {
     QtCharts::QPieSlice *slice1= series->slices().at(1);
     slice1->setLabelVisible();
    }
    QtCharts::QChart * chart=new QtCharts::QChart();

    chart->addSeries(series);

    chart->setTitle("Pourcentage Par Type Etat :Nombre Des Normes "+ QString::number(total));

    QtCharts::QChartView * chartview=new QtCharts::QChartView(chart);

    // Set some chart options
    chartview->chart()->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chartview->chart()->legend()->setAlignment(Qt::AlignRight);
    chartview->chart()->legend()->setFont(QFont("Arial", 15));
    // Set the size and position of the chart view
    QPropertyAnimation *animation = new QPropertyAnimation(series, "opacity");

    // Set the target object and property to animate
    animation->setTargetObject(series);
    animation->setPropertyName("opacity");

    // Set the duration and easing curve
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
     chartview->setRenderHint(QPainter::Antialiasing);
     chartview->resize(1000,500);
    chartview->show();
}


void Normeform::on_pushButton_chatbox_clicked()
{
    DuarteCorporation::widget w;
    w.exec();
}

void Normeform::on_pushButton_video_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this,tr("Select Video File"),"",tr("MP4 File (*.MP4)"));
    QMediaPlayer *player = new QMediaPlayer();
    QVideoWidget *video = new QVideoWidget();
    video->setGeometry(20,20,640,400);
    player->setVideoOutput(video);
    player->setMedia(QUrl(FileName));
    video->show();
    player->play();
}

void Normeform::on_pushButton_todolist_clicked()
{
    t = new todolist();
    t->show();

}
