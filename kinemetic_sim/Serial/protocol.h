/**
 * 通信协议说明
 *
 * 1. 串口配置
 *    波特率115200，8位数据位，1位停止位，无硬件流控，无校验位
 * 2. 通信方式
 *    软件总线形式，广播发送，监听接收
 * 3. 数据帧格式
 *    header(5-byte)+data(n-byte)+end(2-byte)
 *    header: SOF(1-byte, 0x22)+pack_id(1-byte)+data_len(2-byte)+CRC8(1-byte)
 *    data: data package(n-byte, n=data_len)
 *    end: CRC16(2-byte)
 *
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QTimer>

#include <QThread>

#include "crc8_crc16.h"

#define RX_BUF_MAX_LEN          128

#define SOF_VAL                 ((uint16_t)0x2022)

#define CONTROL_SIGNAL_NUM      9
#define IMPLEMENT_SIGNAL_NUM    9

//解包阶段
typedef enum unpack_step : uint8_t
{
    idle = 0,
    header = 1,
    data = 2,
    tail = 3,
    finish = 4,
}Unpack_Step_e;

//数据包ID
typedef enum pack_id : uint8_t
{
    unknown = 0x00,
    U2C = 0x01,
    C2U = 0x02,
    U2I = 0x03,
    I2U = 0x04,
    C2I = 0x05,
    I2C = 0x06,
}Pack_ID_e;

//结构体按1-byte对齐
#pragma pack(1)

//数据帧帧头
typedef struct frame_header
{
    uint16_t SOF;
    Pack_ID_e pack_id;
    uint16_t data_len;
    uint8_t CRC8;
}Frame_Header_t;

//数据帧数据-上位机->控制端
typedef struct frame_data_upper_2_control
{
    uint8_t upper_state;
    float control_input[CONTROL_SIGNAL_NUM];
}Frame_Data_U2C_t;

//数据帧数据-控制端->上位机
typedef struct frame_data_control_2_upper
{
    uint8_t control_state;
    float control_fdb[CONTROL_SIGNAL_NUM];
}Frame_Data_C2U_t;

//数据帧数据-上位机->执行端
typedef struct frame_data_upper_2_implement
{
    uint8_t upper_state;
    float implement_input[IMPLEMENT_SIGNAL_NUM];
}Frame_Data_U2I_t;

//数据帧数据-执行端->上位机
typedef struct frame_data_implement_2_upper
{
    uint8_t implement_state;
    float implement_fdb[IMPLEMENT_SIGNAL_NUM];
}Frame_Data_I2U_t;

//数据帧数据-控制端->执行端
typedef struct frame_data_control_2_implement
{
    uint8_t upper_state;
    float implement_input[IMPLEMENT_SIGNAL_NUM];
    float control_fdb[CONTROL_SIGNAL_NUM];
}Frame_Data_C2I_t;

//数据帧数据-执行端->控制端
typedef struct frame_data_implement_2_control
{
    uint8_t implement_state;
    float control_input[CONTROL_SIGNAL_NUM];
    float implement_fdb[IMPLEMENT_SIGNAL_NUM];
}Frame_Data_I2C_t;

//数据帧帧尾
typedef struct frame_tail
{
    uint16_t CRC16;
}Frame_Tail_t;

#pragma pack()

class Protocol : public QObject
{
    Q_OBJECT

public:
    explicit Protocol(QString port_name);

private:
    QByteArray headerPack(Pack_ID_e pack_id);

public:
    QByteArray dataPack(const Frame_Data_U2C_t &data);
    QByteArray dataPack(const Frame_Data_C2U_t &data);
    QByteArray dataPack(const Frame_Data_U2I_t &data);
    QByteArray dataPack(const Frame_Data_I2U_t &data);
    QByteArray dataPack(const Frame_Data_C2I_t &data);
    QByteArray dataPack(const Frame_Data_I2C_t &data);

public slots:
    void dataAppend2Buf(QByteArray data, QString port_name);
    void dataUnpack(void);

private slots:
    void dataUnpackFailCallback(Unpack_Step_e fail_step);

signals:
    void signal_DataPackCplt(QString port_name, QByteArray tx_pack);

    void signal_DataUnpackCplt(Frame_Data_U2C_t data, QString port_name);
    void signal_DataUnpackCplt(Frame_Data_C2U_t data, QString port_name);
    void signal_DataUnpackCplt(Frame_Data_U2I_t data, QString port_name);
    void signal_DataUnpackCplt(Frame_Data_I2U_t data, QString port_name);
    void signal_DataUnpackCplt(Frame_Data_C2I_t data, QString port_name);
    void signal_DataUnpackCplt(Frame_Data_I2C_t data, QString port_name);

    void signal_DataUnpackFail(Unpack_Step_e fail_step);

private:
    QString port_name;

    QByteArray tx_buf;
    QByteArray rx_buf;

    Unpack_Step_e unpack_step;

    QByteArray SOF;
    Frame_Header_t tx_header;
    Frame_Header_t rx_header;
    Frame_Data_U2C_t rx_data_pack_u2c;
    Frame_Data_C2U_t rx_data_pack_c2u;
    Frame_Data_U2I_t rx_data_pack_u2i;
    Frame_Data_I2U_t rx_data_pack_i2u;
    Frame_Data_C2I_t rx_data_pack_c2i;
    Frame_Data_I2C_t rx_data_pack_i2c;
    Frame_Tail_t rx_tail;
    CRC8_CRC16 CRC;

    QTimer *timer;
};

#endif // PROTOCOL_H
