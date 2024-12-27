#ifndef NORMEFORM_H
#define NORMEFORM_H

#include <QDialog>
#include "norme.h"
#include <QMainWindow>
#include <QDebug>
#include "norme.h"
#include <error.h>
#include <QPrinter>
#include <QtGui>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QMediaPlayer>
#include <QtMultimediaWidgets>
#include <QVideoWidget>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include "widget.h"
#include "todolist.h"
namespace Ui {
class Normeform;
}

class Normeform : public QDialog
{
    Q_OBJECT

public:
    explicit Normeform(QWidget *parent = nullptr);
    ~Normeform();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_modifier_clicked();

    void on_pushButton_PDF_clicked();

    void on_radioButton_croissant_clicked();

    void on_radioButton_decroissant_clicked();

    void on_pushButton_rechercher_clicked();

    void on_pushButton_statistique_clicked();

    void on_pushButton_chatbox_clicked();

    void on_pushButton_video_clicked();

    void on_pushButton_todolist_clicked();

private:
    Ui::Normeform *ui;
    norme N;
    todolist *t;
   // Norme N;
};

#endif // NORMEFORM_H
