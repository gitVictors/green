#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enums.h"

#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
}

MainWindow::~MainWindow () {
    delete ui;
}

 //устанавливает вводимое число или результат вычисления в ui->l_result.
void MainWindow::SetInputText(const std::string& text){
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

//устанавливает текст ошибки (подробности об отображении ошибки ниже) в ui->l_result.
void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

//устанавливает текст формулы, отображаемой над вводом числа в ui->l_formula.
void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

//устанавливает индикатор памяти ui->l_memory.
void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

// устанавливает текст экстра-кнопки. Если передано nullopt, то нужно скрыть экстра-кнопку.
void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key.has_value()) {
        ui->pushButton_dot->setText(QString::fromStdString(key.value()));
        ui->pushButton_dot->setVisible(true);
    } else {
        ui->pushButton_dot->setVisible(false);
    }
}

//колбэк-функция. нужно вызывать при нажатии кнопки с цифрами от 0 до 9.
void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb) {
    digit_cb_ = cb;
}

//колбэк-функция. нужно вызывать при нажатии кнопки операции (сложение, вычитание, умножение, деление, возведение в степень).
void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
    operation_cb_ = cb;
}

//колбэк-функция. нужно вызывать при нажатии других кнопок. Они перечислены в типе ControlKey в enums.h.
void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
    control_cb_ = cb;
}

// колбэк-функция. нужно вызывать при изменении типа чисел.
void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb) {
    controller_cb_ = cb;
}

//---- Нажатие 0-9 ---------------------------------------------
void MainWindow::on_pushButton_one_clicked() {
    digit_cb_(1);
}

void MainWindow::on_pushButton_two_clicked() {
    digit_cb_(2);
}

void MainWindow::on_pushButton_three_clicked()
{
    digit_cb_(3);
}


void MainWindow::on_pushButton_four_clicked()
{
    digit_cb_(4);
}


void MainWindow::on_pushButton_five_clicked()
{
    digit_cb_(5);
}


void MainWindow::on_pushButton_six_clicked()
{
    digit_cb_(6);
}


void MainWindow::on_pushButton_seven_clicked()
{
    digit_cb_(7);
}


void MainWindow::on_pushButton_eight_clicked()
{
    digit_cb_(8);
}


void MainWindow::on_pushButton_nine_clicked()
{
    digit_cb_(9);
}


void MainWindow::on_pushButton_zero_clicked()
{
     digit_cb_(0);
}

//----Операции (+ - * /)----------------------------------------------
void MainWindow::on_pushButton_add_clicked()
{
    operation_cb_(Operation::ADDITION);
}

void MainWindow::on_pushButton_sub_clicked()
{
    operation_cb_(Operation::SUBTRACTION);
}

void MainWindow::on_pushButton_mult_clicked()
{
    operation_cb_(Operation::MULTIPLICATION);
}

void MainWindow::on_pushButton_div_clicked()
{
    operation_cb_(Operation::DIVISION);
}

//----Кнопрки управления ----------------------------------------------
void MainWindow::on_pushButton_delete_clicked()
{
    control_cb_(ControlKey::BACKSPACE);
}

void MainWindow::on_pushButton_result_clicked()
{
    control_cb_(ControlKey::EQUALS);
}

void MainWindow::on_pushButton_clean_clicked()
{
    control_cb_(ControlKey::CLEAR);
}

void MainWindow::on_pushButton_negative_clicked()
{
    control_cb_(ControlKey::PLUS_MINUS);
}

void MainWindow::on_pushButton_MemClean_clicked()
{
    control_cb_(ControlKey::MEM_CLEAR);
}

void MainWindow::on_pushButton_MemRead_clicked()
{
    control_cb_(ControlKey::MEM_LOAD);
}

void MainWindow::on_pushButton_MemSave_clicked()
{
    control_cb_(ControlKey::MEM_SAVE);
}


void MainWindow::on_pushButton_dot_clicked()
{
    control_cb_(ControlKey::EXTRA_KEY);
}

void MainWindow::on_cmb_controller_currentIndexChanged(int index)
{
    if (!controller_cb_) return;

    ControllerType type = static_cast<ControllerType> (ui->cmb_controller->itemData(index).toInt());
    controller_cb_(type);  //SetControllerCallback
}

