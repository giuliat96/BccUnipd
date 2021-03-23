#-------------------------------------------------
#
# Project created by QtCreator 2020-05-29T20:36:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = progetto_p2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        vista/mainwindow.cpp \
    modello/ospite.cpp \
     modello/persona.cpp \
     modello/operatore.cpp \
    controller/mainwindow_controller.cpp \
    vista/login_window.cpp \
     modello/soggetti.cpp \
     modello/dipendente.cpp \
     modello/cliente.cpp \
     modello/dipendente_cliente.cpp \
    vista/table_lists.cpp \
    vista/gestionepersone.cpp \
    modello/servizio.cpp \
    modello/prodotti.cpp \
    modello/cont_corr.cpp \
    modello/investimento.cpp

HEADERS += \
       vista/mainwindow.h \
     modello/ospite.h \
     modello/persona.h \
     modello/operatore.h \
    controller/mainwindow_controller.h \
    vista/login_window.h \
     modello/soggetti.h \
     modello/dipendente.h \
     modello/cliente.h \
     modello/dipendente_cliente.h \
    vista/table_lists.h \
    vista/gestionepersone.h \
    modello/servizio.h \
    modello/prodotti.h \
    modello/cont_corr.h \
    modello/investimento.h

FORMS += \
        mainwindow.ui \
    mainwindow.ui

RESOURCES += \
    resources.qrc
