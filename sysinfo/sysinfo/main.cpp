#include "mainwindow.h"

#include <QApplication>

#include "sysinfo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SysInfo::instance().init();
    MainWindow w;
    w.show();
    return a.exec();
}
