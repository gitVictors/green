#pragma once

#include <QMainWindow>
#include <functional>
#include "setting.h"
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotShowAction(int num, QString action_name, std::function<void()> action);
private slots:

    void on_pb_sett_1_clicked();

    void on_pb_sett_2_clicked();

    void on_pb_sett_3_clicked();

    void on_pb_sett_4_clicked();

private:
    Ui::MainWindow *ui;
    Setting* setting_ = new Setting();
    std::vector<QPushButton*> buttons_;
};
