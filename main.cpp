#include "dialog.h"
#include<QTranslator>
#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include<QtDebug>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTranslator t;
        //QTranslator guiTranslator;
        QStringList languages;
        languages << "French" << "English";
        QString lang =QInputDialog::getItem(NULL,"select language","language",languages);
        qDebug() << "select"<<lang ;

        if (lang == "English") {
               // Charger le fichier de traduction anglais
               if (t.load(":/english.qm")) {
                   a.installTranslator(&t);
                   //guiTranslator.load("C:/Qt/Qt5.9.9/5.9.9/mingw53_32/translations/english.qm");


               } else {
                   QMessageBox::warning(nullptr, "Translation Error", "Failed to load English translation file.");

               }
           }
    Dialog w;
    w.show();
    return a.exec();
}
