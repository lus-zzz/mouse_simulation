#include "mainwindow.h"

#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QMouseEvent>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextStream>
#include <thread>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  //  bool ret = GlobalMouseEvent::installMouseEvent();
  //  ui->textEdit->append(QString("<<<<<<<<<< 全局鼠标事件监听器安装%1
  //  >>>>>>>>>>")
  //                           .arg(ret ? "成功" : "失败"));
  ui->statusbar->addWidget(new QLabel("F9 开始/停止运行"));
  ui->statusbar->addWidget(new QLabel("F10 开始/停止录制"));
  connect(this, &MainWindow::stop_run, this, [&]() {
    this->showNormal();
    exit_flags = false;
    press_flags = true;
  });

  GlobalKeyEvent::installKeyEvent();
  connect(GlobalMouseEvent::getInstance(), &GlobalMouseEvent::mouseEvent, this,
          &MainWindow::on_mouseEvent);
  connect(GlobalMouseEvent::getInstance(), &GlobalMouseEvent::wheelEvent, this,
          &MainWindow::on_wheelEvent);
  connect(GlobalKeyEvent::getInstance(), &GlobalKeyEvent::keyEvent, this,
          &MainWindow::on_keyEvent);
  connect(this,&MainWindow::process_event,this,&MainWindow::keyMouseProcess,Qt::BlockingQueuedConnection);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_mouseEvent(QMouseEvent* event) {
  QDateTime now_time = QDateTime::currentDateTime();
  int duration = last_time.msecsTo(now_time);
  last_time = now_time;

  switch (event->type()) {
    case QMouseEvent::MouseMove: {
      QJsonDocument doc;
      QJsonObject obj;
      obj["type"] = 1;
      obj["x"] = event->x();
      obj["y"] = event->y();
      obj["duration"] = duration;
      doc.setObject(obj);

      QString str;
      QTextStream ts(&str);
      ts << doc.toJson(QJsonDocument::Compact);
      ui->textEdit->append(str);
    } break;
    case QEvent::MouseButtonDblClick:
    case QMouseEvent::MouseButtonPress: {
      QJsonDocument doc;
      QJsonObject obj;
      // 如果是鼠标左键按下
      if (event->button() == Qt::LeftButton) {
        obj["type"] = 2;

      }
      // 如果是鼠标右键按下
      else if (event->button() == Qt::RightButton) {
        obj["type"] = 3;
      }
      obj["event"] = 0;
      obj["x"] = event->x();
      obj["y"] = event->y();
      obj["duration"] = duration;
      doc.setObject(obj);
      QString str;
      QTextStream ts(&str);
      ts << doc.toJson(QJsonDocument::Compact);
      ui->textEdit->append(str);
    } break;
    case QMouseEvent::MouseButtonRelease: {
      QDateTime now_time = QDateTime::currentDateTime();
      QJsonDocument doc;
      QJsonObject obj;
      // 如果是鼠标左键释放
      if (event->button() == Qt::LeftButton) {
        obj["type"] = 2;

      }
      // 如果是鼠标右键释放
      else if (event->button() == Qt::RightButton) {
        obj["type"] = 3;
      }
      obj["event"] = 1;
      obj["x"] = event->x();
      obj["y"] = event->y();
      obj["duration"] = duration;
      doc.setObject(obj);
      QString str;
      QTextStream ts(&str);
      ts << doc.toJson(QJsonDocument::Compact);
      ui->textEdit->append(str);
    } break;
    default:
      break;
  }

  last_time = now_time;
}

void MainWindow::on_keyEvent(QKeyEvent* event) {
  if (event->type() == QKeyEvent::KeyRelease && event->key() == Qt::Key_F10) {
    this->showMinimized();
    last_time = QDateTime::currentDateTime();
    if (!install) {
      this->showMinimized();
      GlobalMouseEvent::installMouseEvent();
    } else {
      this->showNormal();
      GlobalMouseEvent::removeMouseEvent();
    }
    install = !install;
  } else if (event->type() == QKeyEvent::KeyRelease &&
             event->key() == Qt::Key_F9) {
    if (press_flags) {
      on_pushButton_2_clicked();
      on_pushButton_5_clicked();
    } else {
      exit_flags = true;
    }
  } else {
    if (install) {
      QDateTime now_time = QDateTime::currentDateTime();
      int duration = last_time.msecsTo(now_time);
      last_time = now_time;

      switch (event->type()) {
        case QEvent::KeyPress: {
          if (event->key() == Qt::Key_F10 || event->key() == Qt::Key_F9) return;

          QJsonObject obj;
          obj["type"] = 5;
          obj["event"] = 0;
          obj["code"] = keyMap(event);
          obj["duration"] = duration;
          QJsonDocument doc;
          doc.setObject(obj);
          QString str;
          QTextStream ts(&str);
          ts << doc.toJson(QJsonDocument::Compact);
          ui->textEdit->append(str);

        } break;
        case QEvent::KeyRelease: {
          if (event->key() == Qt::Key_F10 || event->key() == Qt::Key_F9) return;
          QJsonObject obj;
          obj["type"] = 5;
          obj["event"] = 1;
          obj["code"] = keyMap(event);
          obj["duration"] = duration;
          QJsonDocument doc;
          doc.setObject(obj);
          QString str;
          QTextStream ts(&str);
          ts << doc.toJson(QJsonDocument::Compact);
          ui->textEdit->append(str);
        } break;
        default:
          break;
      }
    }
  }
}

void MainWindow::on_wheelEvent(QWheelEvent* event) {
  QDateTime now_time = QDateTime::currentDateTime();
  int duration = last_time.msecsTo(now_time);
  last_time = now_time;
  QJsonObject obj;
  obj["type"] = 4;
  // 当滚轮远离使用者时向上
  if (event->delta() > 0) {
    obj["event"] = 2;
  } else {  //当滚轮向使用者方向旋转时向下
    obj["event"] = 3;
  }
  obj["duration"] = duration;
  QJsonDocument doc;
  doc.setObject(obj);
  QString str;
  QTextStream ts(&str);
  ts << doc.toJson(QJsonDocument::Compact);
  ui->textEdit->append(str);
}

void MainWindow::on_pushButton_clicked() {
  QString file_path = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                   tr("config (*.txt)"));
  QFile data(file_path);
  if (data.open(QFile::WriteOnly | QFile::Truncate)) {
    QTextStream out(&data);
    out << ui->textEdit->document()->toPlainText();
  }
  ui->textEdit->clear();
}

void MainWindow::on_pushButton_2_clicked() {
  press_flags = false;
  this->showMinimized();
  QVector<QPair<QString, int>> task;
  for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
    QTableWidgetItem* item0 = ui->tableWidget->item(row, 0);
    QTableWidgetItem* item1 = ui->tableWidget->item(row, 1);
    if (item0 && item1) {
      task.push_back({item0->text(), item1->text().toInt()});
    }
  }

  std::thread thread([&, task]() {
    for (auto it : task) {
      QFile file(it.first);
      if (file.open(QFile::ReadOnly)) {
        QStringList com_list;
        while (!file.atEnd()) {
          com_list.push_back(file.readLine());
        }
        file.close();
        for (int i = 0; i < it.second; i++) {
          for (auto line : com_list) {
            if (exit_flags) {
              emit stop_run();
              return;
            }
            emit process_event(line);
          }
        }
      }
    }
    if (task.size()) emit stop_run();
  });
  thread.detach();
}

void MainWindow::keyMouseProcess(QString json_str) {
  QJsonDocument doc = QJsonDocument::fromJson(json_str.toLatin1());
  QJsonObject message = doc.object();


  auto it = message.find("type");
  if (it == message.end()) return;
  auto type = message["type"].toInt();

  int x, y, event, code, duration;
  it = message.find("x");
  if (it != message.end()) x = message["x"].toInt();
  it = message.find("y");
  if (it != message.end()) y = message["y"].toInt();
  it = message.find("event");
  if (it != message.end()) event = message["event"].toInt();
  it = message.find("code");
  if (it != message.end()) code = message["code"].toInt();
  it = message.find("duration");
  if (it != message.end()) duration = message["duration"].toInt();

  std::this_thread::sleep_for(std::chrono::milliseconds(duration));

  switch (type) {
    case 1: {
          if(m_serial_port.ch9329())
                m_serial_port.ch9329()->mouseMove(x,y);
          else
             SL::Input_Lite::SendInput(
                 SL::Input_Lite::MousePositionAbsoluteEvent{x, y});
      break;
      case 2:
        if (event == 0) {  //鼠标左键按下
            if(m_serial_port.ch9329())
                m_serial_port.ch9329()->mousePress();
            else
                 SL::Input_Lite::SendInput(SL::Input_Lite::MouseButtonEvent{
                     true, SL::Input_Lite::MouseButtons::LEFT});

        } else if (event == 1) {  //鼠标左键松开
            if(m_serial_port.ch9329())
                m_serial_port.ch9329()->mouseRelease();
            else
                 SL::Input_Lite::SendInput(SL::Input_Lite::MouseButtonEvent{
                     false, SL::Input_Lite::MouseButtons::LEFT});
        }
        break;
      case 3:
        if (event == 0) {
            if(m_serial_port.ch9329())
                m_serial_port.ch9329()->mousePress(MOUSE_RIGHT_BUTTON);
            else
                SL::Input_Lite::SendInput(SL::Input_Lite::MouseButtonEvent{
                     true, SL::Input_Lite::MouseButtons::RIGHT});
        } else if (event == 1) {
            if(m_serial_port.ch9329())
                m_serial_port.ch9329()->mouseRelease();
            else
         SL::Input_Lite::SendInput(SL::Input_Lite::MouseButtonEvent{
             false, SL::Input_Lite::MouseButtons::RIGHT});
        }
        break;
      case 4:
        if (event == 0) {
            if(m_serial_port.ch9329())
                m_serial_port.ch9329()->mousePress(MOUSE_MIDDLE_BUTTON);
            else
             SL::Input_Lite::SendInput(SL::Input_Lite::MouseButtonEvent{
                 true, SL::Input_Lite::MouseButtons::MIDDLE});
        } else if (event == 1) {
            if(m_serial_port.ch9329())
                m_serial_port.ch9329()->mouseRelease();
            else
             SL::Input_Lite::SendInput(SL::Input_Lite::MouseButtonEvent{
                 false, SL::Input_Lite::MouseButtons::MIDDLE});
        } else if (event == 2) {
            if(m_serial_port.ch9329())
                m_serial_port.ch9329()->mouseWheel(0x01);
            else
                 SL::Input_Lite::SendInput(SL::Input_Lite::MouseScrollEvent{1});
        } else if (event == 3) {
            if(m_serial_port.ch9329())
                m_serial_port.ch9329()->mouseWheel(0x81);
            else
                SL::Input_Lite::SendInput(SL::Input_Lite::MouseScrollEvent{-1});
        }
        break;
      case 5:
        if (event == 0) {
            if(m_serial_port.ch9329())
                m_serial_port.ch9329()->press(SL::Input_Lite::ConvertToKeyCode(code));
            else
             SL::Input_Lite::SendInput(SL::Input_Lite::KeyEvent{
                 true, SL::Input_Lite::ConvertToKeyCode(code)});
        } else if (event == 1) {
            if(m_serial_port.ch9329())
                m_serial_port.ch9329()->releaseAll();
            else
             SL::Input_Lite::SendInput(SL::Input_Lite::KeyEvent{
                 false, SL::Input_Lite::ConvertToKeyCode(code)});
        }
        break;
      default:
        break;
    }
  }
}

void MainWindow::on_pushButton_3_clicked() {
  QStringList list = QFileDialog::getOpenFileNames(this, tr("add File"), "",
                                                   tr("config (*.txt)"));

  for (auto str : list) {
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    QFileInfo fileInfo(str);

    // 添加单元格内容
//    QTableWidgetItem* item1 = new QTableWidgetItem(fileInfo.baseName());
    QTableWidgetItem* item1 = new QTableWidgetItem(str);
    QTableWidgetItem* item2 = new QTableWidgetItem("1");
    ui->tableWidget->setItem(row, 0, item1);
    ui->tableWidget->setItem(row, 1, item2);
    ui->tableWidget->resizeColumnsToContents();
  }
}

void MainWindow::on_pushButton_4_clicked() {
  int currentRow = ui->tableWidget->currentRow();
  if (currentRow >= 0) {
    // 删除当前选定的行
    ui->tableWidget->removeRow(currentRow);
  }
}

int MainWindow::keyMap(QKeyEvent* event) {
  int ret = 0;
  switch (event->key()) {
    case Qt::Key_Backspace:
      ret = 8;
      break;
    case Qt::Key_Backtab:
    case Qt::Key_Tab:
      ret = 9;
      break;
    case Qt::Key_Clear:
      ret = 12;
      break;
    case Qt::Key_Enter:
      ret = 13;
      break;
    case Qt::Key_Shift:
      ret = 16;
      break;
    case Qt::Key_Control:
      ret = 17;
      break;
    case Qt::Key_Alt:
      ret = 18;
      break;
    case Qt::Key_CapsLock:
      ret = 20;
      break;
    case Qt::Key_Escape:
      ret = 27;
      break;
    case Qt::Key_Space:
      ret = 32;
      break;
    case Qt::Key_PageUp:
      ret = 33;
      break;
    case Qt::Key_PageDown:
      ret = 34;
      break;
    case Qt::Key_End:
      ret = 35;
      break;
    case Qt::Key_Home:
      ret = 36;
      break;
    case Qt::Key_Left:
      ret = 37;
      break;
    case Qt::Key_Up:
      ret = 38;
      break;
    case Qt::Key_Right:
      ret = 39;
      break;
    case Qt::Key_Down:
      ret = 40;
      break;
    case Qt::Key_Insert:
      ret = 45;
      break;
    case Qt::Key_Delete:
      ret = 46;
      break;
    case Qt::Key_NumLock:
      ret = 14;
      break;
    case Qt::Key_Asterisk:
      ret = 106;
    case Qt::Key_Plus:
      ret = 107;
      break;
    case Qt::Key_Return:
      ret = 108;
      break;
    case Qt::Key_Minus:
      ret = 109;
      break;
    case Qt::Key_Period:
      ret = 110;
      break;
    case Qt::Key_Slash:
      ret = 111;
      break;
    case Qt::Key_F1:
      ret = 112;
      break;
    case Qt::Key_F2:
      ret = 113;
      break;
    case Qt::Key_F3:
      ret = 114;
      break;
    case Qt::Key_F4:
      ret = 115;
      break;
    case Qt::Key_F5:
      ret = 116;
      break;
    case Qt::Key_F6:
      ret = 117;
      break;
    case Qt::Key_F7:
      ret = 118;
      break;
    case Qt::Key_F8:
      ret = 119;
      break;
    case Qt::Key_F9:
      ret = 120;
      break;
    case Qt::Key_F10:
      ret = 121;
      break;
    case Qt::Key_F11:
      ret = 122;
      break;
    case Qt::Key_F12:
      ret = 123;
      break;
    case Qt::Key_BraceLeft:
    case Qt::Key_BracketLeft:
      ret = 219;
      break;
    case Qt::Key_Bar:
    case Qt::Key_Backslash:
      ret = 220;
      break;
    case Qt::Key_BraceRight:
    case Qt::Key_BracketRight:
      ret = 221;
      break;
    case Qt::Key_QuoteDbl:
    case Qt::Key_Apostrophe:
      ret = 222;
      break;
    case Qt::Key_AsciiTilde:
    case Qt::Key_QuoteLeft:
      ret = 192;
      break;
    case Qt::Key_Colon:
    case Qt::Key_Semicolon:
      ret = 186;
      break;
    case Qt::Key_Equal:
      ret = 187;
      break;
    case Qt::Key_Less:
    case Qt::Key_Comma:
      ret = 188;
      break;
    case Qt::Key_Underscore: {
      ret = 189;
    } break;
    case Qt::Key_Greater:
    case Qt::Key_PreviousCandidate:
      ret = 190;
      break;
    case Qt::Key_Question:
      ret = 191;
      break;
    default:
      ret = event->key();
      break;
  }
  return ret;
}

void MainWindow::on_pushButton_5_clicked() {
  press_flags = false;
  this->showMinimized();
  QVector<QString> task;
  QTextDocument* doc = ui->textEdit->document();
  for (int i = 0; i < doc->lineCount(); ++i) {
    QTextBlock block = doc->findBlockByLineNumber(i);
    QString line = block.text();
    task.push_back(line);
  }
  std::thread thread([&, task]() {
    for (auto it : task) {
      if (exit_flags) {
        emit stop_run();
        return;
      }
      emit process_event(it);
    }
    if (task.size()) emit stop_run();
  });
  thread.detach();
}




void MainWindow::on_pushButton_6_clicked()
{
    m_serial_port.exec();
}

