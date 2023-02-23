#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QComboBox>
#include <QTextCodec>
#include <QSerialPortInfo>
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serialPort = new QSerialPort;

    portNameList = getPortNameList();
    ui->portBox->addItems(portNameList);

    QStringList baudRateList;
    baudRateList << "1200" << "2400" << "4800" << "9600" << "19200" << "57600" << "115200";

    ui->baudBox->addItems(baudRateList);
    ui->baudBox->setCurrentIndex(6);

    ui->txData->setText(tr("串口调试助手"));
}

MainWindow::~MainWindow()
{
    serialPort->close();
    delete serialPort;
    delete ui;
}


QStringList MainWindow::getPortNameList() {
    QStringList serialPortNameList;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        serialPortNameList << info.portName();
        qDebug() << "all available port name: " << info.portName();
    }
    return serialPortNameList;
}

void MainWindow::on_openPortBtn_clicked() {
    if (ui->openPortBtn->text() == "打开串口") {
        if (serialPort->isOpen()) {
            serialPort->clear();
            serialPort->close();
        }

        serialPort->setPortName(portNameList[ui->portBox->currentIndex()]);

        if (! serialPort->open(QIODevice::ReadWrite)) {
            qDebug() << "串口" << portNameList[ui->portBox->currentIndex()] << "打开失败";
            return;
        } else {
            qDebug() << "串口" << portNameList[ui->portBox->currentIndex()] << "打开成功";
        }

        serialPort->setBaudRate(ui->baudBox->currentText().toInt(), QSerialPort::AllDirections);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);

        connect(serialPort, SIGNAL(readyRead()), this, SLOT(receiveData()));
        ui->openPortBtn->setText("关闭串口");
    } else {
        serialPort->close();
        ui->openPortBtn->setText("打开串口");
    }
}


void MainWindow::receiveData() {

    QByteArray data = serialPort->readAll();

    qDebug() << "Reveive Data" << data;

    QString strRxData = "";

    if (ui->hexshowbox->isChecked()) {
        QByteArray hexData = data.toHex();
        strRxData = hexData.toUpper();

        qDebug() << "Receive Data from uart" << strRxData;

        for (int i=0; i<strRxData.size(); ++i) {
            strRxData.insert(i, QLatin1String(" "));
        }
        strRxData.remove(0, 1);

        qDebug() << "data Afer dealing : " << strRxData;

        ui->rxData->append(strRxData);
    } else {
        strRxData = data;

        QTextCodec *textcodec = QTextCodec::codecForName("GBK");
        QString tmp_data = textcodec->toUnicode(data);

        ui->rxData->append(tmp_data);
    }
}

char convertChar2Hex(char c) {
    if ( (c >= '0') && (c <= '9')) {
        return c -0x30;
    } else if ((c >= 'A') && (c <= 'Z')) {
        return c - 'A' + 10;
    } else if ((c >= 'a') && (c <= 'z')) {
        return c - 'a' + 10;
    } else
        return (-1);
}


void convertString2Hex(const QString&str, QByteArray &arr) {
    int hexdata, lowhexdata;
    int hexdatalen = 0;
    int len = str.length();

    arr.resize(len/2);
    char lstr, hstr;

    for (int i = 0; i < len; ) {
        hstr = str[i].toLatin1();
        if (hstr == ' ') {
            i ++;
            continue;
        }
        i ++;
        if (i > len)
            break;
        lstr = str[i].toLatin1();
        hexdata = convertChar2Hex(hstr);
        lowhexdata = convertChar2Hex(lstr);

        if (hexdata == 16 || (lowhexdata == 16)) {
            break;
        } else
            hexdata = hexdata*16 + lowhexdata;
        i++;

        arr[hexdatalen] = (char) hexdata;
        hexdatalen++;
    }
    arr.resize(hexdatalen);
}


void MainWindow::on_sendBtn_clicked() {

    qDebug() << "sendBtn clicked";
    QString strSendData = ui->txData->text();

    if(ui->hexsendbox->isChecked())
    {
        if (strSendData.contains(" "))
        {
            strSendData.replace(QString(" "),QString(""));    //把空格去掉
        }

        QByteArray sendBuf;

        convertString2Hex(strSendData, sendBuf);             //把QString 转换 为 hex

        serialPort->write(sendBuf);
    }
    else
    {
        serialPort->write(strSendData.toLocal8Bit());
    }

}
