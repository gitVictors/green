#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rb_asc_clicked()
{
    rb_asc_ = ui->rb_asc->isChecked();
    rb_desc_ = ui->rb_desc->isChecked();
    SortAndDisplayWords();

}

void MainWindow::on_rb_desc_clicked()
{
    rb_asc_ = ui->rb_asc->isChecked();
    rb_desc_ = ui->rb_desc->isChecked();;
    SortAndDisplayWords();
}

void MainWindow::on_cb_case_clicked()
{

    case_sens_ = ui->cb_case->isChecked();
    SortAndDisplayWords();

}

void MainWindow::on_le_unsorted_textChanged(const QString&)
{
    SortAndDisplayWords();
}

void MainWindow::SortAndDisplayWords (void){

    QString unsorted_text = ui->le_unsorted->text();
    QStringList word_list = unsorted_text.split(' ');

    Qt::CaseSensitivity cs_s = case_sens_ ? Qt::CaseSensitive  : Qt::CaseInsensitive;

    if (rb_asc_ ==  true)
        std::sort(word_list.begin(), word_list.end(), [&](const QString& str1, const QString& str2){
        return str1.compare(str2, cs_s ) < 0;
        } );
    else if (rb_desc_ == true)
        std::sort(word_list.begin(), word_list.end(), [&](const QString& str1, const QString& str2){
            return str1.compare(str2, cs_s ) > 0;
        } );


    ui->le_sorted->setText(word_list.join(" "));
}
