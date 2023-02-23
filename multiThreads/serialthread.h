#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include<QThread>
#include<QDebug>
#include<QSerialPort>
#include<QSerialPortInfo>
#include<QString>
#include<QTimer>


class serialThread : public QObject
{
    Q_OBJECT
public:
    serialThread();
    ~serialThread();

public:
    void InitPort(const QString name,
                  const qint32 baudrate,
                  const QSerialPort::DataBits databits,
                  const QSerialPort::Parity parity,
                  const QSerialPort::StopBits stopbit,
                  const QSerialPort::FlowControl flowcontrol);  // 初始化串口信息
    bool OpenPort();                                            // 打开串口
    void ClosePort();                                           // 关闭串口

    //    void InitPortName(const QString &portName);                 //初始化串口名
    //    void InitPortBaudRate(qint32 baudRate);                     //...波特率
    //    void InitPortDataBits(QSerialPort::DataBits dataBits);      //...数据位
    //    void InitPortParity(QSerialPort::Parity parity);            //...奇偶校验
    //    void InitPortStopBits(QSerialPort::StopBits stopbits);      //...停止位
    //    void InitFlowControl(QSerialPort::FlowControl flowcontrol); //...控制流


public slots:
    void handleData();
    void txData(QByteArray data);

signals:
    void rxData(QByteArray data);

private:
    QSerialPort *port;
};

#endif // SERIALTHREAD_H
