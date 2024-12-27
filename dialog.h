#ifndef DIALOG_H
#define DIALOG_H
#include <QSerialPort>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void Read_Data();


private:
    Ui::Dialog *ui;
    QSerialPort* COMPORT;
      QString Data_From_SerialPort;
      bool Is_Data_Recevied=false;
      int etatconn=0;
};
#endif // DIALOG_H
