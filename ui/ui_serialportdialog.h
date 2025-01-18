/********************************************************************************
** Form generated from reading UI file 'serialportdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALPORTDIALOG_H
#define UI_SERIALPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <xToolsBaudRateComboBox.h>
#include <xToolsDataBitsComboBox.h>
#include <xToolsFlowControlComboBox.h>
#include <xToolsParityComboBox.h>
#include <xToolsPortNameComboBox.h>
#include <xToolsStopBitsComboBox.h>

QT_BEGIN_NAMESPACE

class Ui_SerialPortDialog
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    xToolsStopBitsComboBox *comboBoxStopBits;
    xToolsPortNameComboBox *comboBoxPortNames;
    xToolsFlowControlComboBox *comboBoxFlowControl;
    QLabel *label_6;
    xToolsDataBitsComboBox *comboBoxDataBits;
    xToolsParityComboBox *comboBoxParity;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_2;
    xToolsBaudRateComboBox *comboBoxBaudRate;
    QLabel *label;
    QPushButton *pushButton_8;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SerialPortDialog)
    {
        if (SerialPortDialog->objectName().isEmpty())
            SerialPortDialog->setObjectName(QString::fromUtf8("SerialPortDialog"));
        SerialPortDialog->resize(242, 300);
        gridLayout = new QGridLayout(SerialPortDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new QFrame(SerialPortDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_3, 4, 0, 1, 1);

        comboBoxStopBits = new xToolsStopBitsComboBox(frame);
        comboBoxStopBits->setObjectName(QString::fromUtf8("comboBoxStopBits"));

        gridLayout_2->addWidget(comboBoxStopBits, 5, 1, 1, 1);

        comboBoxPortNames = new xToolsPortNameComboBox(frame);
        comboBoxPortNames->setObjectName(QString::fromUtf8("comboBoxPortNames"));
        comboBoxPortNames->setEditable(false);

        gridLayout_2->addWidget(comboBoxPortNames, 0, 1, 1, 1);

        comboBoxFlowControl = new xToolsFlowControlComboBox(frame);
        comboBoxFlowControl->setObjectName(QString::fromUtf8("comboBoxFlowControl"));

        gridLayout_2->addWidget(comboBoxFlowControl, 7, 1, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_6, 7, 0, 1, 1);

        comboBoxDataBits = new xToolsDataBitsComboBox(frame);
        comboBoxDataBits->setObjectName(QString::fromUtf8("comboBoxDataBits"));

        gridLayout_2->addWidget(comboBoxDataBits, 4, 1, 1, 1);

        comboBoxParity = new xToolsParityComboBox(frame);
        comboBoxParity->setObjectName(QString::fromUtf8("comboBoxParity"));

        gridLayout_2->addWidget(comboBoxParity, 6, 1, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_4, 5, 0, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_5, 6, 0, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        comboBoxBaudRate = new xToolsBaudRateComboBox(frame);
        comboBoxBaudRate->setObjectName(QString::fromUtf8("comboBoxBaudRate"));
        comboBoxBaudRate->setEditable(true);

        gridLayout_2->addWidget(comboBoxBaudRate, 2, 1, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label, 2, 0, 1, 1);

        pushButton_8 = new QPushButton(frame);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        gridLayout_2->addWidget(pushButton_8, 9, 0, 1, 2);


        gridLayout->addWidget(frame, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SerialPortDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(SerialPortDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SerialPortDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SerialPortDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SerialPortDialog);
    } // setupUi

    void retranslateUi(QDialog *SerialPortDialog)
    {
        SerialPortDialog->setWindowTitle(QCoreApplication::translate("SerialPortDialog", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("SerialPortDialog", "Data bits", nullptr));
        label_6->setText(QCoreApplication::translate("SerialPortDialog", "Flow control", nullptr));
        label_4->setText(QCoreApplication::translate("SerialPortDialog", "Stop bits", nullptr));
        label_5->setText(QCoreApplication::translate("SerialPortDialog", "Parity", nullptr));
        label_2->setText(QCoreApplication::translate("SerialPortDialog", "Port name", nullptr));
        label->setText(QCoreApplication::translate("SerialPortDialog", "Baud rate", nullptr));
        pushButton_8->setText(QCoreApplication::translate("SerialPortDialog", "\346\211\223\345\274\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SerialPortDialog: public Ui_SerialPortDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALPORTDIALOG_H
