#ifndef SERIAL_DEMO_H
#define SERIAL_DEMO_H

#include <QWidget>
#include <QTimer>
#include "Serial/serial.h"
#include "Serial/serial_system.h"


#include "dhdc.h"
#include "drdc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class serial_demo; }
QT_END_NAMESPACE

class serial_demo : public QWidget
{
    Q_OBJECT

public:
    serial_demo(QWidget *parent = nullptr);
    ~serial_demo();

public slots:
    void rotate(float data);
    void slide(float data);
    void curve(float data);
    void Drotate(float data);
    void Dslide(float data);
    void Dcurve(float data);

    void demoLoop();

    void printData();
//    void printOutput();

    void on_OpenSerialButton_clicked();
    void on_lineEdit_input0_editingFinished();

public:
    Ui::serial_demo *ui;
    QTimer timer;

    Serial_System serial_system;

};
#endif // SERIAL_DEMO_H
