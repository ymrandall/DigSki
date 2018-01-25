#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    //Forms
    MyDialog first;
    MainWindow second;

    QObject::connect(&first, SIGNAL(newTextEntered(const QString&)),
                         &second, SLOT(onNewTextEntered(const QString&)));

    second.show();
    first.show();


    return a.exec();
}
