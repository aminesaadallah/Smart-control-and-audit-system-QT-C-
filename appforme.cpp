#include "appforme.h"
#include "ui_appforme.h"

appforme::appforme(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::appforme)
{
    ui->setupUi(this);
}

appforme::~appforme()
{
    delete ui;
}
