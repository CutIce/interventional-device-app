#include <QApplication>
#include "../header/mainwindow.h"
#include <QDebug>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    qDebug() << "start ! \n";

    mainwindow w;
    w.show();
    return a.exec();
}
