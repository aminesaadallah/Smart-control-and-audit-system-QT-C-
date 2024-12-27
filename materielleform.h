#ifndef MATERIELLEFORM_H
#define MATERIELLEFORM_H

#include <QDialog>

#include <QMainWindow>
#include <QImageReader>
#include <QBuffer>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

#include "materiel_audite.h"

#include <QMainWindow>

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMovie>
#include <QtGui>
#include <QtWidgets/QMainWindow>
class QMediaplayer;
class QVideoWidget;class QMediaplayer;
class QVideoWidget;
namespace Ui {
class Materielleform;
}

class Materielleform : public QDialog
{
    Q_OBJECT

public:
    explicit Materielleform(QWidget *parent = nullptr);
    ~Materielleform();
    void setGallery();

    QString selectImageFile();
    QByteArray loadImageData(const QString &filePath);
    void loadImageFromDatabase(QString productId, QLabel *label);

    void createButtonWithLabels(QVBoxLayout *verticalLayout, QMap<QString, QString> map);



private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

  void on_pushButton_ajouter_clicked();

  void on_pushButton_supprimer_clicked();

  void on_pushButton_mod_clicked();

  void on_pushButton_rech_clicked();

  void on_pushButton_tri_clicked();

  void on_pushButton_pdf_clicked();

  void on_pushButton_stat_clicked();

  void on_tab_afficher_equipement_clicked(const QModelIndex &index);

 // void on_pushButton_ajout_image_clicked();

  void on_pushButton_mod_image_clicked();

  void on_boutton_verifier_image_vehicule_clicked();

  void on_boutton_choisir_image_vehicule_clicked();





  void on_tableView_chercher_activated(const QModelIndex &index);

private:
    Ui::Materielleform *ui;
    Materiel_audite m;
    QByteArray imageData;
    QVBoxLayout *verticalLayout;
    Connection cnx;
    QList<QMap<QString, QString>> EquipementData;
    QString equipement_id, equipement_name, date_achat, numero_serie, emplacement;


};

#endif // MATERIELLEFORM_H
