#ifndef AUDITEURFORM_H
#define AUDITEURFORM_H

#include <QDialog>

#include "auditeur.h"
#include <QStandardItemModel>

#include <QPrinter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QTextDocument>
#include <QTextTable>
#include <QTextTableFormat>
#include <QTextCursor>
#include <QFileDialog>

//stat
#include <QtCharts>
#include <QChartView>
#include <QLayout>
#include <QFrame>
#include<arduino.h>
namespace Ui {
class Auditeurform;
}

class Auditeurform : public QDialog
{
    Q_OBJECT

public:
    explicit Auditeurform(QWidget *parent = nullptr);
    ~Auditeurform();
    QString cleanString(const QString &inputString);



    //pdf
    QString getSaveFilePath(QWidget *parent, QString file_type);
    bool exportDataToPDF(const QString& filePath);

    //stat
    void createPieChartPost(QFrame *frame, const QString &title, QStringList postCategories, const QMap<QString, QList<int>> &data);
    void loadChart(QString chartType);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_recherche_clicked();

    void on_pb_modifier_clicked();

    void on_pb_pdf_clicked();

    void on_pushButton_clicked();




private:
    Ui::Auditeurform *ui;
    Auditeur a;
    Arduino arduino;
    QByteArray arduinoData;
};

#endif // AUDITEURFORM_H
