#include "mainwindow.h"
#include "userfile.h"
#include <QApplication>
#include <fstream>
#include <vector>
#include <cstdlib>

//--------------------------------------------------------

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();
}
