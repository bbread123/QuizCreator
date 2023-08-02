#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include<QtDebug>
#include "dialog.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Dialog form;
    form.show();
//    MainWindow w;
//    w.show();
//    w.setText();
//    w.on_skipButton_clicked();
    return a.exec();
}
