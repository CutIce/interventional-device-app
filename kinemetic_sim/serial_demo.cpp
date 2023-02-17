#include "serial_demo.h"
#include "ui_serial_demo.h"
#include "kinemetic_widget.h"

//#include "drdc.h"


#include <QLineEdit>

serial_demo::serial_demo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::serial_demo)
{
    ui->setupUi(this);

    //1ms定时器

    QObject::connect(&this->timer, &QTimer::timeout, this, &serial_demo::demoLoop, Qt::UniqueConnection);
    QObject::connect(&this->serial_system, SIGNAL(signal_DataUnpackCplt(Frame_Data_c2u_t, QString)),
            this, SLOT(printData()), Qt::UniqueConnection);

    this->timer.start(1);

    //drd parts
    //drdAutoInit();
    //drdStart();

    Kinemetic_Widget *w = new Kinemetic_Widget;

    w->resize(1000,500);
    w->move(300,150);
    w->setFocus();
    w->show();

    QObject::connect(w,SIGNAL(signal_qSmphi(float)),this,SLOT(Drotate(float)));
    QObject::connect(w,SIGNAL(signal_qSmx(float)),this,SLOT(Dcurve(float)));
    QObject::connect(w,SIGNAL(signal_qSmz(float)),this,SLOT(Dslide(float)));
    QObject::connect(w,SIGNAL(signal_qSnphi(float)),this,SLOT(rotate(float)));
    QObject::connect(w,SIGNAL(signal_qSnx(float)),this,SLOT(curve(float)));
    QObject::connect(w,SIGNAL(signal_qSnz(float)),this,SLOT(slide(float)));

}

serial_demo::~serial_demo()
{
    this->serial_system.tx_data_pack_u2c.upper_state = 0;
    this->serial_system.transmitPack2AllPort(this->serial_system.tx_data_pack_u2c);

    this->timer.deleteLater();
    this->serial_system.deleteLater();
    delete ui;
    //drdStop();
}

//主循环（1ms）
//离线检测，自动连接
//支持热插拔
//数据传输demo
void serial_demo::demoLoop()
{
    //扫描串口
    ui->label_availablePortNum->setText(tr("可用串口数：")+QString::number(serial_system.scanPort().size()));

    //printData();

    //发送数据包
    this->serial_system.tx_data_pack_u2c.upper_state = 2;
    this->serial_system.tx_data_pack_u2c.control_input[7] = 0;
    this->serial_system.tx_data_pack_u2c.control_input[8] = 0;

    this->serial_system.transmitPack2AllPort(this->serial_system.tx_data_pack_u2c);

    ui->lineEdit_fdb0->setText(QString::number(this->serial_system.rx_data_pack_c2u.control_fdb[0], 'f', 2));


}

//发送数据
void serial_demo::on_lineEdit_input0_editingFinished()
{
    this->serial_system.tx_data_pack_u2c.control_input[0] = ui->lineEdit_input0->text().toFloat();
}

//接收数据打印
void serial_demo::printData()
{
    ui->textBrowser_serialRxData->append(QString::number(this->serial_system.rx_data_pack_c2u.control_fdb [0], 'f', 2));
}

//打开串口：开启主循环，自动扫描连接串口
//关闭串口：关闭主循环
void serial_demo::on_OpenSerialButton_clicked()
{
    if(ui->OpenSerialButton->text() == tr("打开串口"))
    {
        QObject::connect(&this->timer, &QTimer::timeout, &this->serial_system, &Serial_System::openAllPort,
                         Qt::UniqueConnection);
        ui->OpenSerialButton->setText(tr("关闭串口"));
    }
    else
    {
        for(int i=0; i<20; i++)
        {
        this->serial_system.tx_data_pack_u2c.upper_state = 0;
        this->serial_system.transmitPack2AllPort(this->serial_system.tx_data_pack_u2c);
        }

        QObject::disconnect(&this->timer, &QTimer::timeout, &this->serial_system, &Serial_System::openAllPort);
        serial_system.closeAllPort();
        ui->OpenSerialButton->setText(tr("打开串口"));
    }
}

void serial_demo::Dcurve(float data)
{
    this->serial_system.tx_data_pack_u2c.control_input[6] =data;

}
void serial_demo::curve(float data)
{
    this->serial_system.tx_data_pack_u2c.control_input[3] =data;

}
void serial_demo::Dslide(float data)
{
    this->serial_system.tx_data_pack_u2c.control_input[5] =data;

}
void serial_demo::slide(float data)
{
    this->serial_system.tx_data_pack_u2c.control_input[2] =data;

}
void serial_demo::Drotate(float data)
{
    this->serial_system.tx_data_pack_u2c.control_input[4] =data;

}
void serial_demo::rotate(float data)
{
    this->serial_system.tx_data_pack_u2c.control_input[1] =data;

}
