#ifndef CLIENTFORM_H
#define CLIENTFORM_H
#include "client.h"

#include <QDialog>
#include <QStandardItemModel>

//pdf
#include<QPrinter>
#include <QPrinter>
#include <QTextDocument>
#include <QTextTable>
#include <QTextTableFormat>
#include <QTextCursor>
#include<QFileDialog>
#include<QDir>

//stat
#include <QtCharts>
#include <QChartView>
#include <QLayout>
#include <QFrame>
#include "mailing.h"

namespace Ui {
class Clientform;
}

class Clientform : public QDialog
{
    Q_OBJECT

public:
    explicit Clientform(QWidget *parent = nullptr);
    ~Clientform();
    void addDataToTableView(const QList<QMap<QString, QString>>& dataList);
    QString cleanString(const QString &inputString);
    void addDataToTableView1(const QList<QMap<QString, QString>>& dataList);

    bool exportDataToPDF(const QString& filePath);
    QString getSaveFilePath(QWidget *parent, QString file_type);

    //stat
    void createPieChartPost(QFrame *frame, const QString &title, QStringList postCategories, const QMap<QString, QList<int>> &data);
    void loadChart(QString chartType);

    //mail
    bool verifMail();

    //calander
    void addDataToTableView2(const QList<QMap<QString, QString>>& dataList);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_okButton_clicked();
    void on_pushButton_Rechercher_clicked();

    void on_pushButton_sort_clicked();

    void on_pushButton_exporter_clicked();
    void on_mail_send_btn_clicked();

    void on_calendarWidget_selectionChanged();

    void on_tab_cl_clicked(const QModelIndex &index);

    void on_pushButton_tri_clicked();

private:
    Ui::Clientform *ui;
    client c;
    client clientInstance;
    Mailing mailer;
};

#endif // CLIENTFORM_H
