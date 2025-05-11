#pragma once

#include "calculator.h"
#include "enums.h"

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    // Вот методы для изменения текста
    void SetInputText(const std::string& text);  //устанавливает вводимое число или результат вычисления в ui->l_result.
    void SetErrorText(const std::string& text);  //устанавливает текст ошибки (подробности об отображении ошибки ниже) в ui->l_result.
    void SetFormulaText(const std::string& text); //устанавливает текст формулы, отображаемой над вводом числа в ui->l_formula.
    void SetMemText(const std::string& text);     //устанавливает индикатор памяти ui->l_memory.
    void SetExtraKey(const std::optional<std::string>& key); // устанавливает текст экстра-кнопки. Если передано nullopt, то нужно скрыть экстра-кнопку.

    //Для вызова кол-бек функций при определенном событии
    void SetDigitKeyCallback(std::function<void(int key)> cb);  //колбэк-функцию нужно вызывать при нажатии кнопки с цифрами от 0 до 9.

    // колбэк-функцию нужно вызывать при нажатии кнопки операции  (сложение, вычитание, умножение, деление, возведение в степень).
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);

    // колбэк-функцию нужно вызывать при нажатии других кнопок. Они перечислены в типе ControlKey в enums.h.
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);

    // колбэк-функцию нужно вызывать при изменении типа чисел.
    void SetControllerCallback(std::function<void(ControllerType controller)> cb);

private slots:

    void on_pushButton_one_clicked();

    void on_pushButton_two_clicked();

    void on_pushButton_three_clicked();

    void on_pushButton_four_clicked();

    void on_pushButton_five_clicked();

    void on_pushButton_six_clicked();

    void on_pushButton_seven_clicked();

    void on_pushButton_eight_clicked();

    void on_pushButton_nine_clicked();

    void on_pushButton_zero_clicked();

    void on_pushButton_clean_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_dot_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_result_clicked();

    void on_pushButton_sub_clicked();

    void on_pushButton_mult_clicked();

    void on_pushButton_div_clicked();


    void on_pushButton_power_clicked();

    void on_pushButton_negative_clicked();

    void on_pushButton_MemClean_clicked();

    void on_pushButton_MemRead_clicked();

    void on_pushButton_MemSave_clicked();


    void on_cmb_controller_currentIndexChanged(int index);



private:
    Ui::MainWindow* ui;

    //колбэк-функция нужно вызывать при нажатии кнопки с цифрами от 0 до 9.
    std::function<void(int key)> digit_cb_;  // Входной параметр — числовое значение кнопки.
    //колбэк-функция. нужно вызывать при нажатии кнопки операции (сложение, вычитание, умножение, деление, возведение в степень).
    std::function<void(Operation key)> operation_cb_; //Входной параметр — тип арифметической операции.
    //колбэк-функци. нужно вызывать при нажатии других кнопок. Они перечислены в типе ControlKey в enums.h.
    std::function<void(ControlKey key)> control_cb_;  // Входной параметр — тип нажатой управляющей кнопки.
    // колбэк-функция. нужно вызывать при изменении типа чисел.
    std::function<void(ControllerType controller)> controller_cb_;  // Входной параметр — тип выбранного типа чисел.

};
