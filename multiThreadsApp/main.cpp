#include <QApplication>
#include <QPushButton>
#include "./header/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow mw;
    mw.show();

//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();

    return QApplication::exec();
}
