//
// Created by hsh on 2023/2/22.
//

#ifndef MULTITHREADSAPP_SERIALTHREAD_H
#define MULTITHREADSAPP_SERIALTHREAD_H

#include <QThread>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QTimer>

class serialThread : public  QThread {
    Q_OBJECT
public:
    serialThread();

public:
    QSerialPort *Serial;
    void SetPortName(const QString &portname);
    void SetPortBaudRate(qint32 baudrate);
    void SetPortDataBits(QSerialPort::DataBits dataBits);
    void SetPortParity(QSerialPort::Parity parity);
    void SetPortStopBits(QSerialPort::StopBits stopbits);
    void SetFlowControl(QSerialPort::FlowControl flowControl);
    bool OpenPort();
    void ClosePort();

public:
    QByteArray buffer;

signals:
    void datasend(QByteArray);
    void timeout();

private slots:
    void timeUpdate();
    void data_receive();
    void run();

private:
    QTimer *timer;
};

#endif //MULTITHREADSAPP_SERIALTHREAD_H
