#ifndef DUMESENGERCONNECTIONDIALOG_H
#define DUMESENGERCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class dumesengerconnectiondialog;
}
namespace DuarteCorporation
{
class dumesengerconnectiondialog : public QDialog
{
    Q_OBJECT
public:
    explicit dumesengerconnectiondialog(QWidget *parent = nullptr);
    ~dumesengerconnectiondialog();
    QString hostname() const;
    quint16 port() const ;
private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::dumesengerconnectiondialog *ui;
    QString mHostname;
    quint16 mPort;

};
inline QString dumesengerconnectiondialog::hostname() const
{
    return mHostname;
}
inline quint16 dumesengerconnectiondialog::port() const
{
    return  mPort;
}
}
#endif // DUMESENGERCONNECTIONDIALOG_H
