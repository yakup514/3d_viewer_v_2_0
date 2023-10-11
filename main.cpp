#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    setenv("LC_NUMERIC", "C", 1);
     QApplication::setOrganizationName("21_school_team1");
     QApplication::setApplicationName("s21_3dViewer_1.0");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
