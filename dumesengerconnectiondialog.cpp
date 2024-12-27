#include "dumesengerconnectiondialog.h"
#include "ui_dumesengerconnectiondialog.h"
namespace DuarteCorporation {
dumesengerconnectiondialog::dumesengerconnectiondialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dumesengerconnectiondialog)
{
    ui->setupUi(this);
}

dumesengerconnectiondialog::~dumesengerconnectiondialog()
{
    delete ui;
}

void DuarteCorporation::dumesengerconnectiondialog::on_ok_clicked()
{
    mHostname = ui->hostname->text();
    mPort = ui->port->value();
    accept();
}

void DuarteCorporation::dumesengerconnectiondialog::on_cancel_clicked()
{
    reject();
}
}
