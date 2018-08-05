#include "mainwindow.h"
#include "CoreApp/coreapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CoreApp w;
    w.show();

    return a.exec();
}
