#include <QApplication>
#include "../header/mainwindow.h"
#include <QDebug>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    qDebug() << "start ! \n";

    mainwindow w;
    w.resize(1000,500);
    w.move(300,150);
    w.setFocus();
    w.show();
    return a.exec();
}
