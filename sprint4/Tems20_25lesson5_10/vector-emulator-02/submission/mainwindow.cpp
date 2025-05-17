#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <string.h>

using namespace std::literals ;



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

    ui->pop_back->setDisabled(vector_model_.items.size() == 0);
    ui->txt_size->setText( QString::number( vector_model_.items.size() ) );

    ui->list_widget->clear();
    if (!vector_model_.items.empty()) {
        auto preserve_iter = vector_model_.iterator;

        size_t index = 0;
        for (const auto& item : vector_model_.items)
        {
            ui->list_widget->addItem(QString::number(index++) + ": " + QString::fromStdString(item));
        }

        vector_model_.iterator = preserve_iter;
    }

    ui->list_widget->addItem("end");

    ApplyIterator();
}

void MainWindow::ApplyIterator(){


    //vector_model_.iterator = vector_model_.items.begin();
    if ( !vector_model_.items.empty() && vector_model_.iterator != vector_model_.items.end() ){
        int itr = std::distance( vector_model_.items.begin(), vector_model_.iterator);
        ui->list_widget->setCurrentRow(itr); //выделение
    }else{
          ui->list_widget->setCurrentRow(-1);
    }


    if ( !vector_model_.items.empty() && vector_model_.iterator != vector_model_.items.end() )
    {
        ui->Button_Edit->setDisabled(vector_model_.iterator == vector_model_.items.end() );
        ui->erase->setDisabled(vector_model_.iterator == vector_model_.items.end() );
    }else {
        ui->Button_Edit->setDisabled(true);
        ui->pop_back->setDisabled(true);
        ui->erase->setDisabled(true);
    }

    ui->plus_plus->setDisabled(vector_model_.iterator == vector_model_.items.end() );
    ui->minus_minus->setDisabled( vector_model_.iterator == vector_model_.items.begin() );

}

void MainWindow::on_push_back_clicked()
{
    QString txt = ui->txt_elem_content->text();

    vector_model_.items.push_back(txt.toStdString());
    vector_model_.iterator = std::prev(vector_model_.items.end());
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
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_days_clicked()
{
    vector_model_.items = days_of_week;
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();

}


void MainWindow::on_month_clicked()
{
    vector_model_.items = months_of_year;
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}



void MainWindow::on_list_widget_currentRowChanged(int currentRow)
{
    if (currentRow >= 0 && currentRow <= (static_cast<int>(vector_model_.items.size()-1))){
        if ( !vector_model_.items.empty() && vector_model_.iterator != vector_model_.items.end() ){
            vector_model_.iterator = vector_model_.items.begin();
            std::advance(vector_model_.iterator, currentRow);
            ui->txt_elem_content->setText( QString::fromStdString(*vector_model_.iterator) );
        }
    }

    ApplyIterator();
}


void MainWindow::on_Button_Edit_clicked()
{
    QString txt_str =  ui->txt_elem_content->text();

    auto iter = vector_model_.iterator;
    *iter = txt_str.toStdString();
    ApplyModel();
}


void MainWindow::on_erase_clicked()
{
    if (vector_model_.iterator != vector_model_.items.end()) {
        vector_model_.items.erase(vector_model_.iterator);
        vector_model_.iterator = vector_model_.items.begin();
    }

    ApplyModel(); // Полное обновление, так как изменился контейнер
}


void MainWindow::on_insert_clicked()
{
    std::string new_item = ui->txt_elem_content->text().toStdString();
    if (!new_item.empty()) {
        vector_model_.items.insert(vector_model_.iterator, new_item);
        vector_model_.iterator = vector_model_.items.begin();
    }
    ApplyModel();
}


void MainWindow::on_minus_minus_clicked()
{
    if (vector_model_.iterator != vector_model_.items.begin()){
        --vector_model_.iterator;
        ui->txt_elem_content->setText( QString::fromStdString(*vector_model_.iterator) );
    }
    ApplyIterator();
}


void MainWindow::on_plus_plus_clicked()
{
    if (vector_model_.iterator != vector_model_.items.end() ){
        ++vector_model_.iterator;
        if (vector_model_.iterator != vector_model_.items.end())
            ui->txt_elem_content->setText( QString::fromStdString(*vector_model_.iterator) );
    }
    ApplyIterator();
}


void MainWindow::on_begin_clicked()
{
    vector_model_.iterator = vector_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_end_clicked()
{
    vector_model_.iterator = std::prev( vector_model_.items.end());
    ApplyIterator();
}

