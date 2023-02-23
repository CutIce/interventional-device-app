#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStringList getPortNameList();

private slots:
    void on_openPortBtn_clicked();
    void on_sendBtn_clicked();
    void receiveData();

private:
    Ui::MainWindow *ui;
    QSerialPort* serialPort;
    QStringList portNameList;
};
#endif // MAINWINDOW_H
