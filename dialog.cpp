#include "dialog.h"
#include "ui_dialog.h"
#include"auditeur.h"
#include<QMessageBox>
#include"auditeurform.h"
#include"connection.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Connection cn;
    cn.createconnection();
    COMPORT = new QSerialPort() ;

    COMPORT->setPortName("COM3");

    COMPORT->setBaudRate (QSerialPort::BaudRate::Baud9600);

    COMPORT->setParity (QSerialPort::Parity::NoParity);

    COMPORT->setDataBits (QSerialPort::DataBits::Data8);
    COMPORT->setStopBits (QSerialPort::StopBits::OneStop);

    COMPORT->setFlowControl (QSerialPort::FlowControl::NoFlowControl);

    COMPORT->open(QIODevice::ReadWrite);

    if(COMPORT->isOpen()){

    qDebug() << "Serial Port Is Connected." ;
                qDebug() << COMPORT->error();
    }
    else{

    qDebug() << "Serial Port Is Not Connected.";

    qDebug() << COMPORT->error();
}
    connect (COMPORT,SIGNAL(readyRead()),this,SLOT(Read_Data()));



}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{


        QString enteredEmail = ui->lineEdit->text();
        QString enteredmdp = ui->lineEdit_2->text();
        Auditeur a;
        if (a.checkIdEmailexist(enteredEmail))
        {
            QMessageBox::information(this, "Login Successful", "Login successful!");

                    if (a.checkIdmdpexist( enteredmdp)) {
                        QMessageBox::information(this, "Login Successful", "Login successful!");
                        Auditeurform app;
                        this->hide();
                        app.exec();


                    } else {
                        // Password is incorrect, show an error message
                        QMessageBox::critical(this, "Login Failed", "Incorrect password. Please try again.");
                        // Additional logic for failed login

                    }
                }
        else {
                    // Email does not exist, show an error message
                    QMessageBox::critical(this, "Login Failed", "Email does not exist. Please check your email.");
                    // Additional logic for failed login
                }
            }

void Dialog::Read_Data(){

    if (COMPORT->isOpen()) {

        while (COMPORT->bytesAvailable()) {
            Data_From_SerialPort += COMPORT->readAll();
            if (Data_From_SerialPort.at(Data_From_SerialPort.length() - 1) == char(10)) {
                Is_Data_Recevied = true;
            }
        }
        if (Is_Data_Recevied) {
             etatconn=Data_From_SerialPort.toInt();
           if(etatconn==1){ui->label_4->setText("etat : Start");}
           else if(etatconn==2){
               QMessageBox::information(this, "Login Successful", "Login successful!");
               Auditeurform app;
               this->hide();
               app.exec();
           }else ui->label_4->setText("etat : acces-denied try again");
            Data_From_SerialPort = "";
            Is_Data_Recevied = false;
        }
    }
}
