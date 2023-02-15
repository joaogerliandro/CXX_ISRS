#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    //window.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    window.show();
    return a.exec();
}
