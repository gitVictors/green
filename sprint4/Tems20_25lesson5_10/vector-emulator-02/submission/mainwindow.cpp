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

    vector_model_.iterator = vector_model_.items.end();
    ApplyModel();
    ApplyIterator();
}

MainWindow::~MainWindow() {
    delete ui;
}



void MainWindow::ApplyModel() {
    // Реализуйте этот метод.
    ui->list_widget->clear();

    ui->pop_back->setDisabled(vector_model_.items.size() == 0);

    ui->txt_size->setText( QString::number( vector_model_.items.size() ) );

    for (size_t i = 0; i < vector_model_.items.size();  ++i){
        QString itm = QString::number(i) + ": " + QString::fromStdString (vector_model_.items[i]);
        ui->list_widget->addItem(itm);
    }
}

void MainWindow::ApplyIterator(){

    // if (vector_model_.items.empty())
    //     return;

    int itr = 0;
    if ( vector_model_.items.begin() != vector_model_.iterator ){
        itr = std::distance( vector_model_.items.begin(), vector_model_.iterator);
    }

    ui->list_widget->setCurrentRow(itr); //выделение
    ui->Button_Edit->setDisabled(vector_model_.iterator == vector_model_.items.end() );
    ui->erase->setDisabled(vector_model_.iterator == vector_model_.items.end() );
    ui->plus_plus->setDisabled(vector_model_.iterator == vector_model_.items.end() );
    ui->minus_minus->setDisabled( vector_model_.iterator == vector_model_.items.begin() );


    auto preserve_iter = vector_model_.iterator;

    ui->list_widget->clear();

    size_t index = 0;
    for (const auto& it : vector_model_.items){
        ui->list_widget->addItem(  QString::number(index) + ": " + QString::fromStdString(it) );
        index++;
    }
    ui->list_widget->addItem("end");
    vector_model_.iterator = preserve_iter;

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


void MainWindow::on_days_clicked()
{
    vector_model_.items = months_of_year;
    ApplyModel();
}


void MainWindow::on_month_clicked()
{
    vector_model_.items = days_of_week;
    ApplyModel();
}



void MainWindow::on_list_widget_currentRowChanged(int currentRow)
{
    if (currentRow < 0 || currentRow >= (static_cast<int>(vector_model_.items.size()+1))){
        return ;
    }

    vector_model_.iterator = vector_model_.items.begin();
    std::advance(vector_model_.iterator, currentRow);

    ui->txt_elem_content->setText( QString::fromStdString(*vector_model_.iterator) );
    ApplyIterator();
}

