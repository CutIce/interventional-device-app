#ifndef SERIAL_H
#define SERIAL_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Serial : public QSerialPort
{
    Q_OBJECT

public:
    explicit Serial(void);

    bool openPort(const QString &port_name = "",
                  const qint32 baud_rate = QSerialPort::Baud115200,
                  const QSerialPort::DataBits data_bits = QSerialPort::Data8,
                  const QSerialPort::Parity parity = QSerialPort::NoParity,
                  const QSerialPort::StopBits stop_bits = QSerialPort::OneStop,
                  const QSerialPort::FlowControl flow_control = QSerialPort::NoFlowControl);
    void closePort(void);

    QStringList scanPort(void);
    bool isConnect(void);

    int64_t transmit(const QByteArray &data);
    int64_t transmit(const uint8_t *data);

private slots:
    void receive(void);

signals:
    void signal_PortOpen(QString port_name);
    void signal_PortClose(QString port_name);
    void signal_TxCplt(qint64 flag, QString port_name);
    void signal_RxCplt(QByteArray data, QString port_name);

private:
    QStringList port_list;
    QByteArray tx_buf;
    QByteArray rx_buf;
};

#endif // SERIAL_H
