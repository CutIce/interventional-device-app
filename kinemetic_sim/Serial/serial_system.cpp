#include "serial_system.h"

Serial_System::Serial_System(void)
{

}

/**
 * @brief	打开指定串口
 * @param 	port_name: 串口名
 * @retval 	true/false: 成功/失败
 */
bool Serial_System::openPort(const QString port_name)
{
    scanPort();
    if(this->port_list.contains(port_name))
    {
        return this->serial_list[this->port_list.indexOf(port_name)]->openPort();
    }
    return false;
}

/**
 * @brief	关闭指定串口
 * @param 	port_name: 串口名
 * @retval 	none
 */
void Serial_System::closePort(const QString port_name)
{
    this->scanPort();
    if(this->port_list.contains(port_name))
    {
        this->serial_list[this->port_list.indexOf(port_name)]->closePort();
    }
}

/**
 * @brief	打开全部可用串口
 * @param 	none
 * @retval 	true/false: 成功/失败
 */
bool Serial_System::openAllPort(void)
{
    bool flag = true;
    this->scanPort();
    foreach(Serial *serialx, this->serial_list)
    {
        if(!serialx->openPort())
        {
            flag = false;
        }
    }
    return flag;
}

/**
 * @brief	关闭全部可用串口
 * @param 	none
 * @retval 	none
 */
void Serial_System::closeAllPort(void)
{
    this->scanPort();
    foreach(Serial *serialx, this->serial_list)
    {
        serialx->closePort();
    }
}

/**
 * @brief	扫描可用串口，关闭并移除不可用串口
 * @param 	none
 * @retval 	可用串口列表
 */
QStringList Serial_System::scanPort(void)
{
    //扫描可用串口，更新串口名列表
    QSerialPort scan_port;
    QStringList new_port_list;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        scan_port.setPort(info);
        new_port_list.append(scan_port.portName());
        if(scan_port.open(QIODevice::NotOpen))
        {
            scan_port.close();
        }
    }
    scan_port.deleteLater();
    //原有串口处理
    //从新串口列表中移除已连接串口，关闭未连接串口
    this->port_list.clear();
    foreach(Serial *serialx, this->serial_list)
    {
        if(new_port_list.contains(serialx->portName()))
        {
            this->port_list.append(serialx->portName());
            new_port_list.removeAll(serialx->portName());
        }
        else
        {
            this->serial_handle_list[this->serial_list.indexOf(serialx)]->deleteLater();
            this->serial_handle_list.removeAt(this->serial_list.indexOf(serialx));
            serialx->closePort();
            serialx->deleteLater();
            this->serial_list.removeAll(serialx);
        }
    }
    //新串口处理
    //创捷新串口对象并配置串口名
    foreach(const QString &new_port_name, new_port_list)
    {
        Serial *new_serial = new Serial;
        Protocol *new_handle = new Protocol(new_port_name);

        new_serial->setPortName(new_port_name);
        this->port_list.append(new_serial->portName());
        this->serial_list.append(new_serial);
        this->serial_handle_list.append(new_handle);

        connect(new_serial, &Serial::signal_TxCplt, this, &Serial_System::txCpltCallback, Qt::UniqueConnection);
        connect(new_serial, &Serial::signal_RxCplt, this, &Serial_System::rxCpltCallback, Qt::UniqueConnection);

//        connect(new_handle, &Protocol::signal_DataPackCplt, new_serial, &Serial::transmitPack, Qt::UniqueConnection);
        connect(new_serial, &Serial::signal_RxCplt, new_handle, &Protocol::dataAppend2Buf, Qt::UniqueConnection);
        connect(new_handle, SIGNAL(signal_DataUnpackCplt(Frame_Data_U2C_t,QString)),
                this, SLOT(dataUnpackCpltCallback(Frame_Data_U2C_t,QString)),
                Qt::UniqueConnection);
        connect(new_handle, SIGNAL(signal_DataUnpackCplt(Frame_Data_C2U_t,QString)),
                this, SLOT(dataUnpackCpltCallback(Frame_Data_C2U_t,QString)),
                Qt::UniqueConnection);
        connect(new_handle, SIGNAL(signal_DataUnpackCplt(Frame_Data_U2I_t,QString)),
                this, SLOT(dataUnpackCpltCallback(Frame_Data_U2I_t,QString)),
                Qt::UniqueConnection);
        connect(new_handle, SIGNAL(signal_DataUnpackCplt(Frame_Data_I2U_t,QString)),
                this, SLOT(dataUnpackCpltCallback(Frame_Data_I2U_t,QString)),
                Qt::UniqueConnection);
        connect(new_handle, SIGNAL(signal_DataUnpackCplt(Frame_Data_C2I_t,QString)),
                this, SLOT(dataUnpackCpltCallback(Frame_Data_C2I_t,QString)),
                Qt::UniqueConnection);
        connect(new_handle, SIGNAL(signal_DataUnpackCplt(Frame_Data_I2C_t,QString)),
                this, SLOT(dataUnpackCpltCallback(Frame_Data_I2C_t,QString)),
                Qt::UniqueConnection);
    }
    return this->port_list;
}

/**
 * @brief	串口字符串发送（全端口统一发送）
 * @param 	data: QByteArray数据
 * @retval 	-1/else: 发送失败/发送数据位数
 */
QList<int64_t> Serial_System::transmit2AllPort(const QByteArray &data)
{
    QList<int64_t> flag;
    foreach(Serial *serialx, this->serial_list)
    {
        flag.append(serialx->transmit(data));
    }
    return flag;
}

/**
 * @brief	串口1byte数据发送（全端口统一发送）
 * @param 	data: uint8数据
 * @retval 	-1/else: 发送失败/发送数据位数
 */
QList<int64_t> Serial_System::transmit2AllPort(const uint8_t *data)
{
    QList<int64_t> flag;
    foreach(Serial *serialx, this->serial_list)
    {
        flag.append(serialx->transmit(data));
    }
    return flag;
}

/**
 * @brief	串口数据包发送（全端口统一发送）
 * @param 	data: 数据包
 * @retval 	-1/else: 发送失败/发送数据位数
 */
QList<int64_t> Serial_System::transmitPack2AllPort(const Frame_Data_U2C_t &data)
{
    QList<int64_t> flag;
    foreach(Serial *serialx, this->serial_list)
    {
        flag.append(serialx->transmit(serial_handle_list[serial_list.indexOf(serialx)]->dataPack(data)));
    }
    return flag;
}

QList<int64_t> Serial_System::transmitPack2AllPort(const Frame_Data_C2U_t &data)
{
    QList<int64_t> flag;
    foreach(Serial *serialx, this->serial_list)
    {
        flag.append(serialx->transmit(serial_handle_list[serial_list.indexOf(serialx)]->dataPack(data)));
    }
    return flag;
}

QList<int64_t> Serial_System::transmitPack2AllPort(const Frame_Data_U2I_t &data)
{
    QList<int64_t> flag;
    foreach(Serial *serialx, this->serial_list)
    {
        flag.append(serialx->transmit(serial_handle_list[serial_list.indexOf(serialx)]->dataPack(data)));
    }
    return flag;
}

QList<int64_t> Serial_System::transmitPack2AllPort(const Frame_Data_I2U_t &data)
{
    QList<int64_t> flag;
    foreach(Serial *serialx, this->serial_list)
    {
        flag.append(serialx->transmit(serial_handle_list[serial_list.indexOf(serialx)]->dataPack(data)));
    }
    return flag;
}

QList<int64_t> Serial_System::transmitPack2AllPort(const Frame_Data_C2I_t &data)
{
    QList<int64_t> flag;
    foreach(Serial *serialx, this->serial_list)
    {
        flag.append(serialx->transmit(serial_handle_list[serial_list.indexOf(serialx)]->dataPack(data)));
    }
    return flag;
}

QList<int64_t> Serial_System::transmitPack2AllPort(const Frame_Data_I2C_t &data)
{
    QList<int64_t> flag;
    foreach(Serial *serialx, this->serial_list)
    {
        flag.append(serialx->transmit(serial_handle_list[serial_list.indexOf(serialx)]->dataPack(data)));
    }
    return flag;
}


/**
 * @brief	数据发送完成处理函数，用于封装所有串口的发送完成信号
 * @param 	port_name: 串口名
 * @param 	flag: 发送标志
 * @retval 	none
 */
void Serial_System::txCpltCallback(int64_t flag, QString port_name)
{
    emit this->signal_TxCplt(flag, port_name);
}

/**
 * @brief	数据接收完成处理函数，用于封装所有串口的接收完成信号
 * @param 	port_name: 串口名
 * @param 	data: 接收数据
 * @retval 	none
 */
void Serial_System::rxCpltCallback(QByteArray data, QString port_name)
{
    emit this->signal_RxCplt(data, port_name);


}

/**
 * @brief	数据解包完成处理函数，用于封装所有串口的解包完成信号
 * @param 	port_name: 串口名
 * @param 	data: 解析数据包
 * @retval 	none
 */
void Serial_System::dataUnpackCpltCallback(Frame_Data_U2C_t data, QString port_name)
{
    this->rx_data_pack_u2c = data;
    emit this->signal_DataUnpackCplt(data, port_name);
}

void Serial_System::dataUnpackCpltCallback(Frame_Data_C2U_t data, QString port_name)
{
    this->rx_data_pack_c2u = data;
    emit this->signal_DataUnpackCplt(data, port_name);
}

void Serial_System::dataUnpackCpltCallback(Frame_Data_U2I_t data, QString port_name)
{
    this->rx_data_pack_u2i = data;
    emit this->signal_DataUnpackCplt(data, port_name);
}

void Serial_System::dataUnpackCpltCallback(Frame_Data_I2U_t data, QString port_name)
{
    this->rx_data_pack_i2u = data;
    emit this->signal_DataUnpackCplt(data, port_name);
}

void Serial_System::dataUnpackCpltCallback(Frame_Data_C2I_t data, QString port_name)
{
    this->rx_data_pack_c2i = data;
    emit this->signal_DataUnpackCplt(data, port_name);
}

void Serial_System::dataUnpackCpltCallback(Frame_Data_I2C_t data, QString port_name)
{
    this->rx_data_pack_i2c = data;
    emit this->signal_DataUnpackCplt(data, port_name);
}

