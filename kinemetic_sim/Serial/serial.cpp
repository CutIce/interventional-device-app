#include "serial.h"
#include "QTime"
#include "QCoreApplication"

Serial::Serial(void)
{

}

/**
 * @brief	配置串口参数，打开串口
 * @param 	port_name: 串口名，默认可用串口列表第一个
 * @param 	baud_rate: 波特率，默认115200
 * @param 	data_bits: 数据位，默认8
 * @param 	parity: 校验位，默认无校验
 * @param 	stop_bits: 停止位，默认0
 * @param 	flow_control: 流控制，默认无控制
 * @retval 	true/false: 串口打开成功/失败
 */
bool Serial::openPort(const QString &port_name,
                      const qint32 baud_rate,
                      const QSerialPort::DataBits data_bits,
                      const QSerialPort::Parity parity,
                      const QSerialPort::StopBits stop_bits,
                      const QSerialPort::FlowControl flow_control)
{
    if(!port_name.isEmpty())
    {
        this->setPortName(port_name);
    }
    this->setBaudRate(baud_rate);
    this->setDataBits(data_bits);
    this->setParity(parity);
    this->setStopBits(stop_bits);
    this->setFlowControl(flow_control);

    if(this->isOpen())
    {
        return true;
    }
    if(this->open(QIODevice::ReadWrite))
    {
        connect(this, &Serial::readyRead, this, &Serial::receive, Qt::UniqueConnection);
        emit signal_PortOpen(this->portName());

        return true;
    }
    return false;
}

/**
 * @brief	关闭串口
 * @param 	none
 * @retval 	none
 */
void Serial::closePort()
{
    disconnect(this, &Serial::readyRead, this, &Serial::receive);
    if(this->isOpen())
    {
        this->clear();
        this->close();
    }
    emit signal_PortClose(this->portName());
}

/**
 * @brief	串口扫描，将所有可用串口记录到port_list中
 * @param 	none
 * @retval 	可用串口列表
 */
QStringList Serial::scanPort(void)
{
    port_list.clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        this->setPort(info);
        port_list.append(this->portName());
        //若当前串口已打开则只添加到列表不关闭
        if(this->open(QIODevice::NotOpen))
        {
            this->close();
        }
    }
    //若当前串口名为空则将列表首位配置为串口名
    if(this->portName().isEmpty() && !port_list.isEmpty())
    {
        this->setPortName(port_list[0]);
    }
    return port_list;
}

/**
 * @brief	检测串口连接状态
 * @param 	none
 * @retval 	true/false: 连接/离线
 */
bool Serial::isConnect(void)
{
    this->scanPort();
    return port_list.contains(this->portName());
}

/**
 * @brief	串口字符串发送
 * @param 	data
 * @retval 	-1/else: 发送失败/发送数据位数
 */
int64_t Serial::transmit(const QByteArray &data)
{
    if(!this->isOpen())
    {
        return -1;
    }

    int64_t flag;
    flag    = this->write(data);

    if(flag != -1)
    {
        emit signal_TxCplt(flag, this->portName());
    }
    return flag;
}

/**
 * @brief	串口1byte数据发送
 * @param 	data
 * @retval 	-1/else: 发送失败/发送数据位数
 */
qint64 Serial::transmit(const uint8_t *data)
{
    if(!this->isOpen())
    {
        return -1;
    }

    tx_buf.resize(sizeof(data));
    memcpy(tx_buf.data(), data, sizeof(tx_buf));

    qint64 flag = this->write(tx_buf);
    if(flag != -1)
    {
        emit signal_TxCplt(flag, this->portName());
    }
    return flag;
}

/**
 * @brief	串口数据接收函数，将数据存到缓冲区
 * @param 	none
 * @retval 	none
 */
void Serial::receive()
{
    rx_buf = this->readAll();
    emit signal_RxCplt(rx_buf, this->portName());
    rx_buf.clear();
}
