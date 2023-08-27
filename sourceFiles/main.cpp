#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include<QtDebug>
#include "dialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    loading stylesheet
//    QFile styleSheetFile("C:/Users/username/Documents/QTproj/test/Darkeum.qss");
    QFile styleSheetFile("./Darkeum.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);

    Dialog form;
    form.show();
    return a.exec();
}

