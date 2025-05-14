#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

static std::vector<std::string> days_of_week = {
    "Понедельник",
    "Вторник",
    "Среда",
    "Четверг",
    "Пятница",
    "Суббота",
    "Воскресенье"
};

static std::vector<std::string> months_of_year = {
    "Январь",
    "Февраль",
    "Март",
    "Апрель",
    "Май",
    "Июнь",
    "Июль",
    "Август",
    "Сентябрь",
    "Октябрь",
    "Ноябрь",
    "Декабрь"
};



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    // Реализуйте этот метод.
    ui->list_widget->clear();

    if (vector_model_.items.size() == 0)
        ui->pop_back->setDisabled(true);
    else
        ui->pop_back->setDisabled(false); //активный элемент

    ui->txt_size->setText( QString::number( vector_model_.items.size() ) );

    for (size_t i = 0; i < vector_model_.items.size();  ++i){
        QString itm = QString::number(i) + ": " + QString::fromStdString (vector_model_.items[i]);
        ui->list_widget->addItem(itm);
    }
}

void MainWindow::on_push_back_clicked()
{
    QString txt = ui->txt_elem_content->text();

    vector_model_.items.push_back(txt.toStdString());
    ApplyModel();
}


void MainWindow::on_clear_clicked()
{
    vector_model_.items.clear();;
    ApplyModel();
}


void MainWindow::on_pop_back_clicked()
{
    vector_model_.items.pop_back();
    ApplyModel();
}


void MainWindow::on_pushButton_5_clicked()
{
    vector_model_.items = months_of_year;
    ApplyModel();
}


void MainWindow::on_pushButton_4_clicked()
{
    vector_model_.items = days_of_week;
    ApplyModel();
}

