QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql printsupport charts serialport sql network multimedia multimediawidgets charts printsupport widgets axcontainer
QT += sql
QT += printsupport
QT += charts
QT += network
QT += multimedia
QT +=multimediawidgets
QT +=serialport svg
CONFIG += c++11
INCLUDEPATH += $$PWD/Qt-QrCodeGenerator-main/src
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    $$PWD/Qt-QrCodeGenerator-main/src/QrCodeGenerator.h \
    $$PWD/Qt-QrCodeGenerator-main/src/qrcodegen/qrcodegen.h \
    materielleform.h \
    normeform.h \
    qrcodedialog.h \
    ihmgraphique.h\
    generateurpdf.h
SOURCES += \
    $$PWD/Qt-QrCodeGenerator-main/src/QrCodeGenerator.cpp \
    $$PWD/Qt-QrCodeGenerator-main/src/qrcodegen/qrcodegen.cpp \
    materielleform.cpp \
    normeform.cpp \
    qrcodedialog.cpp\
    ihmgraphique.cpp\
    generateurpdf.cpp



SOURCES += \
    appforme.cpp \
    arduino.cpp \
    auditeur.cpp \
    auditeurform.cpp \
    client.cpp \
    clientform.cpp \
    connection.cpp \
    mailing.cpp \
    main.cpp \
    dialog.cpp \
    materiel_audite.cpp \
    rapport.cpp \
    rapportform.cpp\
    dumesengerconnectiondialog.cpp \
    todolist.cpp \
    widget.cpp\
    norme.cpp \


HEADERS += \
    appforme.h \
    arduino.h \
    auditeur.h \
    auditeurform.h \
    client.h \
    clientform.h \
    connection.h \
    dialog.h \
    mailing.h \
    materiel_audite.h \
    rapport.h \
    rapportform.h\
    dumesengerconnectiondialog.h \
    todolist.h \
    widget.h\
    norme.h \

FORMS += \
    appforme.ui \
    auditeurform.ui \
    clientform.ui \
    dialog.ui \
    materielleform.ui \
    normeform.ui \
    rapportform.ui\
    dumesengerconnectiondialog.ui \
    todolist.ui \
    widget.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    res.qrc \
    translation.qrc
