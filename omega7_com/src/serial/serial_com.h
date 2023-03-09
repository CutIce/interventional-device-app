//
// Created by hsh on 2023/3/8.
//

#ifndef OMEGA7_COM_SERIAL_COM_H
#define OMEGA7_COM_SERIAL_COM_H

#include "../header/serial/serial.h"
#include "../header/serial/protocol.h"
#include <QList>


class Serial_Communicator : public QObject {
    Q_OBJECT

private:
    Pack_ID_e serial_type;

public:
    explicit Serial_Communicator();
    ~Serial_Communicator();


    Serial serial;
    Protocol serial_handle;

signals:
    void signal_RxCplt(QByteArray &data);

public slots:
    void enableSerialPort(QString &port_name);
    void transmitData();

    //用于各串口数据解包完成信号封装
    void dataUnpackCpltCallback(Frame_Data_U2C_t data);
    void dataUnpackCpltCallback(Frame_Data_C2U_t data);
    void dataUnpackCpltCallback(Frame_Data_U2I_t data);
    void dataUnpackCpltCallback(Frame_Data_I2U_t data);
    void dataUnpackCpltCallback(Frame_Data_C2I_t data);
    void dataUnpackCpltCallback(Frame_Data_I2C_t data);



};

#endif //OMEGA7_COM_SERIAL_COM_H
