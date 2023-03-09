#ifndef SERIAL_SYSTEM_H
#define SERIAL_SYSTEM_H

#include <QList>
#include "serial.h"
#include "protocol.h"
#include <QDebug>
#include <QThread>


class Serial_System : public QObject
{
    Q_OBJECT

public:
    explicit Serial_System(void);

    bool openPort(const QString port_name);
    void closePort(const QString port_name);
    bool openAllPort(void);
    void closeAllPort(void);

    QStringList scanPort(void);

    QList<int64_t> transmit2AllPort(const QByteArray &data);
    QList<int64_t> transmit2AllPort(const uint8_t *data);

    QList<int64_t> transmitPack2AllPort(const Frame_Data_U2C_t &data);
    QList<int64_t> transmitPack2AllPort(const Frame_Data_C2U_t &data);
    QList<int64_t> transmitPack2AllPort(const Frame_Data_U2I_t &data);
    QList<int64_t> transmitPack2AllPort(const Frame_Data_I2U_t &data);
    QList<int64_t> transmitPack2AllPort(const Frame_Data_C2I_t &data);
    QList<int64_t> transmitPack2AllPort(const Frame_Data_I2C_t &data);

public:
    Frame_Data_U2C_t tx_data_pack_u2c;
    Frame_Data_C2U_t tx_data_pack_c2u;
    Frame_Data_U2I_t tx_data_pack_u2i;
    Frame_Data_I2U_t tx_data_pack_i2u;
    Frame_Data_C2I_t tx_data_pack_c2i;
    Frame_Data_I2C_t tx_data_pack_i2c;

    Frame_Data_U2C_t rx_data_pack_u2c;
    Frame_Data_C2U_t rx_data_pack_c2u;
    Frame_Data_U2I_t rx_data_pack_u2i;
    Frame_Data_I2U_t rx_data_pack_i2u;
    Frame_Data_C2I_t rx_data_pack_c2i;
    Frame_Data_I2C_t rx_data_pack_i2c;

public slots:
    void startThreadSlot();
    void txCpltCallback(int64_t flag, QString port_name);
    void rxCpltCallback(QByteArray data, QString port_name);

    //用于各串口数据解包完成信号封装
    void dataUnpackCpltCallback(Frame_Data_U2C_t data, QString port_name);
    void dataUnpackCpltCallback(Frame_Data_C2U_t data, QString port_name);
    void dataUnpackCpltCallback(Frame_Data_U2I_t data, QString port_name);
    void dataUnpackCpltCallback(Frame_Data_I2U_t data, QString port_name);
    void dataUnpackCpltCallback(Frame_Data_C2I_t data, QString port_name);
    void dataUnpackCpltCallback(Frame_Data_I2C_t data, QString port_name);

signals:
    void signal_TxCplt(int64_t flag, QString port_name);
    void signal_RxCplt(QByteArray data, QString port_name);

    //用于各串口数据解包完成信号封装
    void signal_DataUnpackCplt(const Frame_Data_U2C_t &data, QString port_name);
    void signal_DataUnpackCplt(const Frame_Data_C2U_t &data, QString port_name);
    void signal_DataUnpackCplt(const Frame_Data_U2I_t &data, QString port_name);
    void signal_DataUnpackCplt(const Frame_Data_I2U_t &data, QString port_name);
    void signal_DataUnpackCplt(const Frame_Data_C2I_t &data, QString port_name);
    void signal_DataUnpackCplt(const Frame_Data_I2C_t &data, QString port_name);

private:
    QStringList port_list;
    QList<Serial*> serial_list;
    QList<Protocol*> serial_handle_list;
};

#endif // SERIAL_SYSTEM_H
