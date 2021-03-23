#include "controller/mainwindow_controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowController w;

    return a.exec();

}
