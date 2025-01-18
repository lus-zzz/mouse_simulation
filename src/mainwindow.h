#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CH9329.h"
#include "Input_Lite.h"
#include <QDateTime>
#include <QLabel>
#include <QMap>
#include <QSharedPointer>
#include <globalmouseevent.h>
#include "globalkeyevent.h"
#include "serialportdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int keyMap(QKeyEvent *event);
    void keyMouseProcess(QString json_str);
signals:
    void stop_run();
    void process_event(QString json_str);

public slots:
    void on_mouseEvent(QMouseEvent *event);
    void on_keyEvent(QKeyEvent* event);
    void on_wheelEvent(QWheelEvent* event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

//    void on_pushButton_3_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    QDateTime last_time;
    std::atomic_bool exit_flags{false};
    bool install{false};
    bool press_flags{true};

    SerialPortDialog m_serial_port;


};
#endif // MAINWINDOW_H
