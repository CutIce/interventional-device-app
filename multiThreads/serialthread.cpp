#include "serialthread.h"
#include <QDebug>

serialThread::serialThread()
{
    port = new QSerialPort();
}

serialThread::~serialThread() {
    port->close();
    port->deleteLater();
}

void serialThread::InitPort(const QString name, const qint32 baudrate, const QSerialPort::DataBits databits, const QSerialPort::Parity parity, const QSerialPort::StopBits stopbit, const QSerialPort::FlowControl flowcontrol) {
    port->setPortName(name);
    port->setBaudRate(baudrate);
    port->setDataBits(databits);
    port->setStopBits(stopbit);
    port->setParity(parity);
    port->setFlowControl(flowcontrol);
}


bool serialThread::OpenPort()
{
    if( port->open(QIODevice::ReadWrite)) {
        qDebug() << "Succeed to open port";
        return true;
    } else {
        qDebug() << "Fail to open port";
        return false;
    }

    connect(port, SIGNAL(readyRead()), this, SLOT(handleData()), Qt::QueuedConnection);
}

void serialThread::ClosePort()
{
    port->close();
}


void serialThread::handleData() {
    QByteArray data = port->readAll();
    qDebug() << QStringLiteral("RxData: ") << data;
    qDebug() << "handling thread ID is " << QThread::currentThreadId();
    emit rxData(data);
}


void serialThread::txData(QByteArray data) {
    qDebug() << "transmit thread ID is " << QThread::currentThreadId();
    port->write(data);
}
