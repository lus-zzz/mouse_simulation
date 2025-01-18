#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include "CH9329.h"
#include <QDialog>

namespace Ui {
class SerialPortDialog;
}

class SerialPortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialPortDialog(QWidget *parent = nullptr);
    ~SerialPortDialog();

    QSharedPointer<CH9329> ch9329() const;

public slots:
    void on_pushButton_8_clicked();

private:
    Ui::SerialPortDialog *ui;
    QSharedPointer<CH9329> ch9329_ptr;
};

#endif // SERIALPORTDIALOG_H
