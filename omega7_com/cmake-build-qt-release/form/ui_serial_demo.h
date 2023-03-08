/********************************************************************************
** Form generated from reading UI file 'serial_demo.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIAL_DEMO_H
#define UI_SERIAL_DEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serial_demo
{
public:
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_input;
    QLineEdit *lineEdit_input0;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_fdb;
    QLineEdit *lineEdit_fdb0;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_availablePortNum;
    QPushButton *OpenSerialButton;
    QTextBrowser *textBrowser_serialRxData;

    void setupUi(QWidget *serial_demo)
    {
        if (serial_demo->objectName().isEmpty())
            serial_demo->setObjectName(QString::fromUtf8("serial_demo"));
        serial_demo->resize(405, 311);
        horizontalLayoutWidget_2 = new QWidget(serial_demo);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(50, 150, 141, 51));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_input = new QLabel(horizontalLayoutWidget_2);
        label_input->setObjectName(QString::fromUtf8("label_input"));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(9);
        label_input->setFont(font);

        horizontalLayout_2->addWidget(label_input);

        lineEdit_input0 = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit_input0->setObjectName(QString::fromUtf8("lineEdit_input0"));
        QFont font1;
        font1.setPointSize(9);
        lineEdit_input0->setFont(font1);

        horizontalLayout_2->addWidget(lineEdit_input0);

        horizontalLayoutWidget_3 = new QWidget(serial_demo);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(50, 200, 141, 61));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_fdb = new QLabel(horizontalLayoutWidget_3);
        label_fdb->setObjectName(QString::fromUtf8("label_fdb"));
        label_fdb->setFont(font);

        horizontalLayout_3->addWidget(label_fdb);

        lineEdit_fdb0 = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_fdb0->setObjectName(QString::fromUtf8("lineEdit_fdb0"));
        lineEdit_fdb0->setEnabled(true);
        lineEdit_fdb0->setFont(font1);

        horizontalLayout_3->addWidget(lineEdit_fdb0);

        verticalLayoutWidget = new QWidget(serial_demo);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(50, 40, 141, 61));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_availablePortNum = new QLabel(verticalLayoutWidget);
        label_availablePortNum->setObjectName(QString::fromUtf8("label_availablePortNum"));
        label_availablePortNum->setFont(font1);

        verticalLayout->addWidget(label_availablePortNum);

        OpenSerialButton = new QPushButton(verticalLayoutWidget);
        OpenSerialButton->setObjectName(QString::fromUtf8("OpenSerialButton"));
        OpenSerialButton->setEnabled(true);
        OpenSerialButton->setFont(font1);

        verticalLayout->addWidget(OpenSerialButton);

        textBrowser_serialRxData = new QTextBrowser(serial_demo);
        textBrowser_serialRxData->setObjectName(QString::fromUtf8("textBrowser_serialRxData"));
        textBrowser_serialRxData->setGeometry(QRect(220, 30, 151, 241));

        retranslateUi(serial_demo);

        QMetaObject::connectSlotsByName(serial_demo);
    } // setupUi

    void retranslateUi(QWidget *serial_demo)
    {
        serial_demo->setWindowTitle(QCoreApplication::translate("serial_demo", "serial_demo", nullptr));
        label_input->setText(QCoreApplication::translate("serial_demo", "input  ", nullptr));
        label_fdb->setText(QCoreApplication::translate("serial_demo", "fdb     ", nullptr));
        label_availablePortNum->setText(QCoreApplication::translate("serial_demo", "\345\217\257\347\224\250\344\270\262\345\217\243\346\225\260\357\274\232", nullptr));
        OpenSerialButton->setText(QCoreApplication::translate("serial_demo", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serial_demo: public Ui_serial_demo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIAL_DEMO_H
