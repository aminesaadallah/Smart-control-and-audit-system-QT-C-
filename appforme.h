#ifndef APPFORME_H
#define APPFORME_H

#include <QMainWindow>

namespace Ui {
class appforme;
}

class appforme : public QMainWindow
{
    Q_OBJECT

public:
    explicit appforme(QWidget *parent = nullptr);
    ~appforme();

private:
    Ui::appforme *ui;
};

#endif // APPFORME_H
