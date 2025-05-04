#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    buttons_ = {ui->pb_button_1, ui->pb_button_2, ui->pb_button_3, ui->pb_button_4};

    connect(setting_, &Setting::signalSetAction, this, &MainWindow::slotShowAction);
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotShowAction(int num, QString action_name, std::function<void()> action) {
    // Сохраните действие, которое будет делать кнопка с номером num.
    // Действие находится в функциональном объекте action.
    // Поменяйте надпись на кнопке: установите текст action_name.

    // Устанавливаем текст на кнопке
    buttons_[num]->setText(action_name);

    // Устанавливаем новое действие для кнопки
    if (action) {
        connect(buttons_[num], &QPushButton::clicked, this, [action]() {
            action();
        });
    }

}

void MainWindow::on_pb_sett_1_clicked()
{
    setting_->show();
    setting_->SetButtonForSetting(0);
}

void MainWindow::on_pb_sett_2_clicked()
{
    setting_->show();
    setting_->SetButtonForSetting(1);
}

void MainWindow::on_pb_sett_3_clicked()
{
    setting_->show();
    setting_->SetButtonForSetting(2);
}

void MainWindow::on_pb_sett_4_clicked()
{
    setting_->show();
    setting_->SetButtonForSetting(3);
}
