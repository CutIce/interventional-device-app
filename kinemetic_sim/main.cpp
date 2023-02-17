#include "serial_demo.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Kinemetic_Widget w;

//    w.resize(1000,500);
//    w.move(300,150);
//    w.setFocus();
//    w.show();

    serial_demo u;
    u.show();


    return a.exec();
}
