#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    qInfo() << "Приложение запущено";
}

MainWindow::~MainWindow() {
    delete ui;
}

double MainWindow::ConvertToMiles(double km) {

    return km * coef;
}

double MainWindow::ConvertToKm(double miles) {

    return miles / coef;
}

void MainWindow::on_btn_convert_to_miles_clicked() {

    qInfo() << "Нажата кнопка для конвертирования в мили";

    bool ok;
    auto input_text = ui->txt_km_input->text();
    double km = input_text.toDouble(&ok);

    if (ok) {
        double miles = ConvertToMiles(km);
        qDebug() << "Вызвана функция ConvertToMiles, km =" << km;
        qDebug() << "Преобразование выполнено:"<< km<< "км =" << miles << "миль";
        ui->result_label_miles->setText("  = " + QString::number(miles) + " miles");
    } else {
        qDebug() << "Не удалось преобразовать ввод в число:" << input_text;
        ui->result_label_miles->setText("Invalid input for km");
    }
}

void MainWindow::on_btn_convert_to_km_clicked() {

    qInfo() << "Нажата кнопка для конвертирования в километры";
    bool ok;
    auto input_text = ui->txt_miles_input->text();
    double miles = input_text.toDouble(&ok);

    if (ok) {
        double km = ConvertToKm(miles);
        qDebug() << "Вызвана функция ConvertToKm, miles =" << miles;
        qDebug() << "Преобразование выполнено:" << miles << "миль =" << km << "км";
        ui->result_label_km->setText("  = " + QString::number(km) + " km");
    } else {
        qDebug() << "Не удалось преобразовать ввод в число:" << input_text;
        ui->result_label_km->setText("Invalid input for miles");
    }
}
