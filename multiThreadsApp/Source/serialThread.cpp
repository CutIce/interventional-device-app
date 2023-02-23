//
// Created by hsh on 2023/2/22.
//

#include "../header/serialThread.h"


serialThread::serialThread() {
    Serial = new QSerialPort;
    timer  = new QTimer;
}


void serialThread::run() {
    QObject::connect(Serial, &QSerialPort::readyRead, this, &serialThread::data_receive);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
}

void serialThread::data_receive() {
    timer->start(1);
}