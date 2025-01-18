#include "serialportdialog.h"
#include "ui_serialportdialog.h"

SerialPortDialog::SerialPortDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SerialPortDialog)
{
    ui->setupUi(this);
}

SerialPortDialog::~SerialPortDialog()
{
    delete ui;
}

void SerialPortDialog::on_pushButton_8_clicked()
{
    ch9329_ptr = QSharedPointer<CH9329>::create(ui->comboBoxPortNames->currentText());
}

QSharedPointer<CH9329> SerialPortDialog::ch9329() const
{
    return ch9329_ptr;
}
