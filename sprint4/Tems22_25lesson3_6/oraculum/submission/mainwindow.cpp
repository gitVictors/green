#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Reset();
    ShowQuestion();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Reset() {
    a_ = 1;
    b_ = 101;
    m_ = ( a_ + b_ )/2;
}

void MainWindow::ShowQuestion() {
    // Показываем вопрос, используя ui->lbl_question->setText.
    // Если b_ - a_ <= 1, то мы угадали. Нужно показать не вопрос,
    // а ответ.

    if (b_ - a_ <= 1) {
        // Поиск завершен, показываем ответ
        ui->lbl_question->setText(QString("Ваше число %1!").arg(a_));
    } else {
        // Показываем вопрос
        m_ = (a_ + b_) / 2;
        ui->lbl_question->setText(QString("Ваше число меньше %1?").arg(m_));
    }
}

void MainWindow::on_btn_yes_clicked() {
    // Ответ "Да".
    // Делаем шаг алгоритма и обновляем вопрос.
    // Ответ "Да" - число меньше m_
    b_ = m_;
    ShowQuestion();
}

void MainWindow::on_btn_no_clicked() {
    // Ответ "Нет".
    // Делаем шаг алгоритма и обновляем вопрос.
    a_ = m_;
    ShowQuestion();
}
