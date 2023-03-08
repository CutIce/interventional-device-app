//
// Created by hsh on 2023/3/8.
//

#include "../header/serial/protocol.h"

/**
 * @brief	构造函数，初始化解包阶段和SOF标志
 * @param 	port_name: 串口名
 * @retval 	none
 */
Protocol::Protocol(QString port_name)
{
    this->port_name = port_name;

    uint16_t SOF_val = SOF_VAL;
    this->SOF.resize(sizeof(uint16_t));
    memcpy(this->SOF.data(), &SOF_val, sizeof(uint16_t));

    this->unpack_step = Unpack_Step_e::idle;

    this->timer = new QTimer;

    QObject::connect(this->timer, &QTimer::timeout, this, &Protocol::dataUnpack, Qt::UniqueConnection);

    this->timer->start(1);
}

/**
 * @brief	帧头打包
 * @param 	pack_id: 数据包id（用于区分数据包格式）
 * @retval 	数据包帧头段
 */
QByteArray Protocol::headerPack(Pack_ID_e pack_id)
{
    uint8_t header_bytes[sizeof(Frame_Header_t)];

    memcpy(&this->tx_header.SOF, this->SOF.data(), sizeof(uint16_t));
    this->tx_header.pack_id = pack_id;
    switch(pack_id)
    {
        case Pack_ID_e::unknown:
        {
            this->tx_header.data_len = 0;
        }break;
        case Pack_ID_e::U2C:
        {
            this->tx_header.data_len = sizeof(Frame_Data_U2C_t);
        }break;
        case Pack_ID_e::C2U:
        {
            this->tx_header.data_len = sizeof(Frame_Data_C2U_t);
        }break;
        case Pack_ID_e::U2I:
        {
            this->tx_header.data_len = sizeof(Frame_Data_U2I_t);
        }break;
        case Pack_ID_e::I2U:
        {
            this->tx_header.data_len = sizeof(Frame_Data_I2U_t);
        }break;
        case Pack_ID_e::C2I:
        {
            this->tx_header.data_len = sizeof(Frame_Data_C2I_t);
        }break;
        case Pack_ID_e::I2C:
        {
            this->tx_header.data_len = sizeof(Frame_Data_I2C_t);
        }break;
    }
    memcpy(header_bytes, &this->tx_header, sizeof(Frame_Header_t));
    CRC.CRC8_Append(header_bytes, sizeof(Frame_Header_t));
    memcpy(&this->tx_header, header_bytes, sizeof(Frame_Header_t));

    QByteArray header_array;
    header_array.resize(sizeof(Frame_Header_t));
    memcpy(header_array.data(), header_bytes, sizeof(Frame_Header_t));

    return header_array;
}

/**
 * @brief	数据打包
 * @param 	port_id: 数据包id（用于区分数据包格式）
 * @param 	data: 数据段数据
 * @retval 	数据包整包
 */
QByteArray Protocol::dataPack(const Frame_Data_U2C_t &data)
{
    this->tx_buf.clear();

    //添加帧头
    this->tx_buf.append(this->headerPack(U2C));
    //添加数据
    QByteArray data_array;
    data_array.resize(sizeof(data));
    memcpy(data_array.data(), &data, sizeof(data));
    this->tx_buf.append(data_array);
    //添加帧尾
    uint8_t pack_bytes[sizeof(Frame_Header_t)+sizeof(data)+sizeof(Frame_Tail_t)];
    memcpy(pack_bytes, this->tx_buf.data(), this->tx_buf.size());
    CRC.CRC16_Append(pack_bytes, sizeof(pack_bytes));
    this->tx_buf.resize(sizeof(pack_bytes));
    memcpy(this->tx_buf.data(), pack_bytes, sizeof(pack_bytes));

    emit signal_DataPackCplt(this->port_name, this->tx_buf);

    return this->tx_buf;
}

QByteArray Protocol::dataPack(const Frame_Data_C2U_t &data)
{
    this->tx_buf.clear();

    //添加帧头
    this->tx_buf.append(this->headerPack(C2U));
    //添加数据
    QByteArray data_array;
    data_array.resize(sizeof(data));
    memcpy(data_array.data(), &data, sizeof(data));
    this->tx_buf.append(data_array);
    //添加帧尾
    uint8_t pack_bytes[sizeof(Frame_Header_t)+sizeof(data)+sizeof(Frame_Tail_t)];
    memcpy(pack_bytes, this->tx_buf.data(), this->tx_buf.size());
    CRC.CRC16_Append(pack_bytes, sizeof(pack_bytes));
    this->tx_buf.resize(sizeof(pack_bytes));
    memcpy(this->tx_buf.data(), pack_bytes, sizeof(pack_bytes));

    return this->tx_buf;
}

QByteArray Protocol::dataPack(const Frame_Data_U2I_t &data)
{
    this->tx_buf.clear();

    //添加帧头
    this->tx_buf.append(this->headerPack(U2I));
    //添加数据
    QByteArray data_array;
    data_array.resize(sizeof(data));
    memcpy(data_array.data(), &data, sizeof(data));
    this->tx_buf.append(data_array);
    //添加帧尾
    uint8_t pack_bytes[sizeof(Frame_Header_t)+sizeof(data)+sizeof(Frame_Tail_t)];
    memcpy(pack_bytes, this->tx_buf.data(), this->tx_buf.size());
    CRC.CRC16_Append(pack_bytes, sizeof(pack_bytes));
    this->tx_buf.resize(sizeof(pack_bytes));
    memcpy(this->tx_buf.data(), pack_bytes, sizeof(pack_bytes));

    return this->tx_buf;
}

QByteArray Protocol::dataPack(const Frame_Data_I2U_t &data)
{
    this->tx_buf.clear();

    //添加帧头
    this->tx_buf.append(this->headerPack(I2U));
    //添加数据
    QByteArray data_array;
    data_array.resize(sizeof(data));
    memcpy(data_array.data(), &data, sizeof(data));
    this->tx_buf.append(data_array);
    //添加帧尾
    uint8_t pack_bytes[sizeof(Frame_Header_t)+sizeof(data)+sizeof(Frame_Tail_t)];
    memcpy(pack_bytes, this->tx_buf.data(), this->tx_buf.size());
    CRC.CRC16_Append(pack_bytes, sizeof(pack_bytes));
    this->tx_buf.resize(sizeof(pack_bytes));
    memcpy(this->tx_buf.data(), pack_bytes, sizeof(pack_bytes));

    return this->tx_buf;
}

QByteArray Protocol::dataPack(const Frame_Data_C2I_t &data)
{
    this->tx_buf.clear();

    //添加帧头
    this->tx_buf.append(this->headerPack(C2I));
    //添加数据
    QByteArray data_array;
    data_array.resize(sizeof(data));
    memcpy(data_array.data(), &data, sizeof(data));
    this->tx_buf.append(data_array);
    //添加帧尾
    uint8_t pack_bytes[sizeof(Frame_Header_t)+sizeof(data)+sizeof(Frame_Tail_t)];
    memcpy(pack_bytes, this->tx_buf.data(), this->tx_buf.size());
    CRC.CRC16_Append(pack_bytes, sizeof(pack_bytes));
    this->tx_buf.resize(sizeof(pack_bytes));
    memcpy(this->tx_buf.data(), pack_bytes, sizeof(pack_bytes));

    return this->tx_buf;
}

QByteArray Protocol::dataPack(const Frame_Data_I2C_t &data)
{
    this->tx_buf.clear();

    //添加帧头
    this->tx_buf.append(this->headerPack(I2C));
    //添加数据
    QByteArray data_array;
    data_array.resize(sizeof(data));
    memcpy(data_array.data(), &data, sizeof(data));
    this->tx_buf.append(data_array);
    //添加帧尾
    uint8_t pack_bytes[sizeof(Frame_Header_t)+sizeof(data)+sizeof(Frame_Tail_t)];
    memcpy(pack_bytes, this->tx_buf.data(), this->tx_buf.size());
    CRC.CRC16_Append(pack_bytes, sizeof(pack_bytes));
    this->tx_buf.resize(sizeof(pack_bytes));
    memcpy(this->tx_buf.data(), pack_bytes, sizeof(pack_bytes));

    return this->tx_buf;
}

/**
 * @brief	数据解包
 * @param 	port_name: 数据来源串口名
 * @param 	data: 数据包
 * @retval 	none
 */
void Protocol::dataAppend2Buf(QByteArray data, QString port_name)
{
    if(port_name != this->port_name)
    {
        return;
    }
    this->rx_buf.append(data);
    if(this->rx_buf.size() > RX_BUF_MAX_LEN)
    {
        this->rx_buf.remove(0, rx_buf.size() - RX_BUF_MAX_LEN);
    }
}

/**
 * @brief	数据解包
 * @param 	port_name: 数据来源串口名
 * @param 	data: 数据包
 * @retval 	none
 */
void Protocol::dataUnpack(void)
{
    //解包阶段
    switch(this->unpack_step)
    {
        case Unpack_Step_e::idle:
        {
            //检测到SOF标志，清除缓冲区中无效数据，进入start阶段
            if(this->rx_buf.contains(this->SOF))
            {
                this->rx_buf.remove(0, this->rx_buf.indexOf(this->SOF));
                this->unpack_step = Unpack_Step_e::header;
            }
            else
            {
                this->rx_buf.clear();
                break;
            }
        }
        case Unpack_Step_e::header:
        {
            //缓冲区长度>=帧头段长度，读取帧头
            if((uint64_t)this->rx_buf.size() >= sizeof(Frame_Header_t))
            {
                //获取帧头
                memcpy(&this->rx_header, this->rx_buf.data(), sizeof(Frame_Header_t));
                //帧头CRC8校验
                uint8_t header_bytes[sizeof(Frame_Header_t)];
                memcpy(header_bytes, &this->rx_header, sizeof(header_bytes));
//                if(this->CRC.CRC8_Verify(header_bytes, sizeof(header_bytes)))
                {
                    this->rx_buf.remove(0, sizeof(Frame_Header_t));
                    this->unpack_step = Unpack_Step_e::data;
                }
//                else
//                {
//                    this->rx_buf.remove(0, sizeof(this->SOF));
// 暂且去掉crc校验                   this->unpack_step = Unpack_Step_e::idle;
//                    emit this->signal_DataUnpackFail(this->unpack_step);
//                    break;
//                }
            }
            else
            {
                break;
            }
        }
        case Unpack_Step_e::data:
        {
            //缓冲区长度>=数据段长度，读取数据
            if((uint64_t)this->rx_buf.size() >= this->rx_header.data_len)
            {
                //获取数据
                switch(this->rx_header.pack_id)
                {
                    case Pack_ID_e::U2C:
                    {
                        memcpy(&this->rx_data_pack_u2c, this->rx_buf.data(), this->rx_header.data_len);
                        this->unpack_step = Unpack_Step_e::tail;
                    }break;
                    case Pack_ID_e::C2U:
                    {
                        memcpy(&this->rx_data_pack_c2u, this->rx_buf.data(), this->rx_header.data_len);
                        this->unpack_step = Unpack_Step_e::tail;
                    }break;
                    case Pack_ID_e::U2I:
                    {
                        memcpy(&this->rx_data_pack_u2i, this->rx_buf.data(), this->rx_header.data_len);
                        this->unpack_step = Unpack_Step_e::tail;
                    }break;
                    case Pack_ID_e::I2U:
                    {
                        memcpy(&this->rx_data_pack_i2u, this->rx_buf.data(), this->rx_header.data_len);
                        this->unpack_step = Unpack_Step_e::tail;
                    }break;
                    case Pack_ID_e::C2I:
                    {
                        memcpy(&this->rx_data_pack_c2i, this->rx_buf.data(), this->rx_header.data_len);
                        this->unpack_step = Unpack_Step_e::tail;
                    }break;
                    case Pack_ID_e::I2C:
                    {
                        memcpy(&this->rx_data_pack_i2c, this->rx_buf.data(), this->rx_header.data_len);
                        this->unpack_step = Unpack_Step_e::tail;
                    }break;
                    default:
                    {
                        this->unpack_step = Unpack_Step_e::idle;
                    }break;
                }
                this->rx_buf.remove(0, this->rx_header.data_len);
            }
            else
            {
                break;
            }
        }
        case Unpack_Step_e::tail:
        {
            //缓冲区长度>=帧尾段长度，读取帧尾
            if((uint64_t)this->rx_buf.size() >= sizeof(Frame_Tail_t))
            {
                memcpy(&this->rx_tail, this->rx_buf.data(), sizeof(Frame_Tail_t));
                //整包CRC16校验
                uint8_t pack_bytes[sizeof(Frame_Header_t)+this->rx_header.data_len+sizeof(Frame_Tail_t)];
                memcpy(pack_bytes, &this->rx_header, sizeof(Frame_Header_t));
                switch(this->rx_header.pack_id)
                {
                    case Pack_ID_e::U2C:
                    {
                        memcpy(pack_bytes+sizeof(Frame_Header_t), &this->rx_data_pack_u2c, this->rx_header.data_len);
                    }break;
                    case Pack_ID_e::C2U:
                    {
                        memcpy(pack_bytes+sizeof(Frame_Header_t), &this->rx_data_pack_c2u, this->rx_header.data_len);
                    }break;
                    case Pack_ID_e::U2I:
                    {
                        memcpy(pack_bytes+sizeof(Frame_Header_t), &this->rx_data_pack_u2i, this->rx_header.data_len);
                    }break;
                    case Pack_ID_e::I2U:
                    {
                        memcpy(pack_bytes+sizeof(Frame_Header_t), &this->rx_data_pack_i2u, this->rx_header.data_len);
                    }break;
                    case Pack_ID_e::C2I:
                    {
                        memcpy(pack_bytes+sizeof(Frame_Header_t), &this->rx_data_pack_c2i, this->rx_header.data_len);
                    }break;
                    case Pack_ID_e::I2C:
                    {
                        memcpy(pack_bytes+sizeof(Frame_Header_t), &this->rx_data_pack_i2c, this->rx_header.data_len);
                    }break;
                    default: break;
                }
                memcpy(pack_bytes+sizeof(Frame_Header_t)+this->rx_header.data_len, (uint8_t *)&this->rx_tail,
                       sizeof(Frame_Tail_t));
                if(this->CRC.CRC16_Verify(pack_bytes, sizeof(pack_bytes)))
                {
                    this->unpack_step = Unpack_Step_e::finish;
                }
                else
                {
                    this->unpack_step = Unpack_Step_e::idle;
                    emit this->signal_DataUnpackFail(this->unpack_step);
                    break;
                }
                this->rx_buf.remove(0, sizeof(Frame_Tail_t));
            }
            else
            {
                break;
            }
        }
        case Unpack_Step_e::finish:
        {
            //数据解包完成，发出信号，解包状态重置为空闲
            switch(this->rx_header.pack_id)
            {
                case Pack_ID_e::U2C:
                {
                    emit signal_DataUnpackCplt(this->rx_data_pack_u2c, this->port_name);
                }break;
                case Pack_ID_e::C2U:
                {
                    emit signal_DataUnpackCplt(this->rx_data_pack_c2u, this->port_name);
                }break;
                case Pack_ID_e::U2I:
                {
                    emit signal_DataUnpackCplt(this->rx_data_pack_u2i, this->port_name);
                }break;
                case Pack_ID_e::I2U:
                {
                    emit signal_DataUnpackCplt(this->rx_data_pack_i2u, this->port_name);
                }break;
                case Pack_ID_e::C2I:
                {
                    emit signal_DataUnpackCplt(this->rx_data_pack_c2i, this->port_name);
                }break;
                case Pack_ID_e::I2C:
                {
                    emit signal_DataUnpackCplt(this->rx_data_pack_i2c, this->port_name);
                }break;
                default: break;
            }
            this->unpack_step = Unpack_Step_e::idle;
            break;
        }
    }
}

/**
 * @brief	数据解包失败回调函数
 * @param 	fail_step: 解包失败阶段
 * @retval 	none
 */
void Protocol::dataUnpackFailCallback(Unpack_Step_e fail_step)
{
    Q_UNUSED(fail_step);
}
