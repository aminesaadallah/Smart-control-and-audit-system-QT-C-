#ifndef RAPPORTFORM_H
#define RAPPORTFORM_H

#include <QDialog>
#include "rapport.h"
#include <QTableView>
#include <QStandardItemModel>
#include<connection.h>
#include <QTableView>
#include <QDebug>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QTextDocument>
#include <QTextTable>
#include <QTextTableFormat>
#include <QTextCursor>
#include<QFileDialog>
#include<QDir>
#include <QList>
#include <QMap>

//stat
#include <QtCharts>
#include <QChartView>
#include <QLayout>
#include <QFrame>

//stat chat
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLegend>
#include <QtCharts/QBarLegendMarker>
#include <QtCharts/QHorizontalBarSeries>
#include <QSerialPort>
namespace Ui {
class Rapportform;
}

class Rapportform : public QDialog
{
    Q_OBJECT

public:
    explicit Rapportform(QWidget *parent = nullptr);
    ~Rapportform();
    bool exportDataToPDF(const QString& filePath);
    QString getSaveFilePath(QWidget *parent, QString file_type);
    void addDataToTableView(const QList<QMap<QString, QString>>& dataList);
    void lograpportChange(int id, const QString& action);
    void generateSuiviPDF();
    void loadTypeEquipementChart(const QMap<QString, QList<int>> &data);
    void loadChart(const QString &tableName);

   void traduireEtAfficherRapport();


private slots:
   void on_pushButton_2_clicked();

   void on_pushButton_3_clicked();

   void on_pushButton_4_clicked();

   void on_pushButton_5_clicked();

   void on_pushButton_6_clicked();


    void on_pushButton_ajouter_2_clicked();
    void on_pushButton_supprimer_2_clicked();
    void on_pushButton_modifier_2_clicked();
    void on_pushButton_rechercher_clicked();
    void on_pushButton_trier_clicked();
    void on_pushButton_pdf_clicked();
    void on_countButton_clicked();
     void Read_Data();
    void recherche(const QString& id);

private:
    Ui::Rapportform *ui;
    rapport rmp;
    rapport rapportInstance;
    QSqlQueryModel *model;
    Connection cnx;

    QLineEdit *lineEdit_count;
            QPushButton *countButton;
            QLabel *id_count;

QSerialPort* COMPORT;
       QString Data_From_SerialPort;
       bool Is_Data_Recevied=false;
int ardid=0;

};

#endif // RAPPORTFORM_H
