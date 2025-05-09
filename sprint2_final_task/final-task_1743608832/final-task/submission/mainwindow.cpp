#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
    input_number_ = ""; //ui->l_result->text();

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::CalculatingExpression (QString oprt )
{
    ui->l_formula->setText( QString::number( calculator_.GetNumber() ) + " "+ oprt + " " +  ui->l_result->text() + " =");
}

void MainWindow::SetOperatorToFormula (QString opr)
{
    if (ui->l_formula->text() == "" || current_operation_ == Operation::NO_OPERATION)
    {
        ui->l_formula->setText(  QString::number(active_number_) + " " + opr );
        calculator_.Set(active_number_);
        input_number_ = "";
    }
    else
    {
        QString str = ui->l_formula->text();
        str.chop(1);
        ui->l_formula->setText(str + opr);
    }
}

void MainWindow::SetNumberToFormula (QString num){

    if ( current_operation_ == Operation::NO_OPERATION )
        ui->l_formula->setText("");

    if(input_number_ == "0")
    {
        input_number_ = num;
    }
    else
    {
        input_number_ += num;
    }

    ui->l_result->setText(input_number_);
    active_number_ = input_number_.toDouble();

}

//1
void MainWindow::on_pushButton_one_clicked()
{

    SetNumberToFormula("1");

}

//2
void MainWindow::on_pushButton_two_clicked()
{


    SetNumberToFormula("2");

}

//3
void MainWindow::on_pushButton_three_clicked()
{

    SetNumberToFormula("3");

}

//4
void MainWindow::on_pushButton_four_clicked()
{

    SetNumberToFormula("4");

}

//5
void MainWindow::on_pushButton_five_clicked()
{

    SetNumberToFormula("5");

}

//6
void MainWindow::on_pushButton_six_clicked()
{
    SetNumberToFormula("6");
}

//7
void MainWindow::on_pushButton_seven_clicked()
{
    SetNumberToFormula("7");

}

//8
void MainWindow::on_pushButton_eight_clicked()
{
    SetNumberToFormula("8");

}

//9
void MainWindow::on_pushButton_nine_clicked()
{
    SetNumberToFormula("9");

}

//0
void MainWindow::on_pushButton_zero_clicked()
{

     SetNumberToFormula("0");

}

//clean
void MainWindow::on_pushButton_clean_clicked()
{
    input_number_ =  "";
    ui->l_result->setText("0");
    ui->l_formula->setText("");
    calculator_.Set(0);
}

//<= удление
void MainWindow::on_pushButton_delete_clicked()
{
    if (input_number_ == "")
    {
      return;
    }

    input_number_.chop(1);
    if (input_number_ == "")
        ui->l_result->setText( "0" );
    else
        ui->l_result->setText( input_number_ );
    active_number_ = input_number_.toDouble();

}

//, плавающая точка
void MainWindow::on_pushButton_dot_clicked()
{

    //при повторном нажатии "." возврат
    if (input_number_.contains('.'))
    {
        return;
    }

    if (input_number_ == "")
        input_number_ += "0.";
    else
        input_number_ += '.';

    ui->l_result->setText( input_number_ );
    active_number_ = input_number_.toDouble();
}


//= Результат вычисления
void MainWindow::on_pushButton_result_clicked()
{

    if (current_operation_ == Operation::NO_OPERATION)
    {
        return;
    }

    switch (current_operation_) {

    case Operation::ADDITION :
        CalculatingExpression ("+");
        calculator_.Add( ui->l_result->text().toDouble() );
        current_operation_ = Operation::NO_OPERATION;
        break;
    case Operation::SUBTRACTION:
        CalculatingExpression ("−");
        calculator_.Sub(ui->l_result->text().toDouble());
        current_operation_ = Operation::NO_OPERATION;
        break;
    case Operation::MULTIPLICATION:
        CalculatingExpression ("×");
        calculator_.Mul(ui->l_result->text().toDouble());
        current_operation_ = Operation::NO_OPERATION;
        break;
    case Operation::DIVISION:
        CalculatingExpression ("÷");
        calculator_.Div(ui->l_result->text().toDouble());
        current_operation_ = Operation::NO_OPERATION;
        break;
    case Operation::POWER:
        CalculatingExpression ("^");
        calculator_.Pow(ui->l_result->text().toDouble());
        current_operation_ = Operation::NO_OPERATION;
        break;

    default:
        break;
    }

    active_number_ = calculator_.GetNumber();
    ui->l_result->setText( QString::number(  active_number_ )  );
    input_number_ = ""; //очистка перед новым операндом

}


//+
void MainWindow::on_pushButton_add_clicked()
{
    if (current_operation_ == Operation::ADDITION)
    {
        return;
    }

    SetOperatorToFormula("+");

    current_operation_ = Operation::ADDITION;


}

//- вычитание
void MainWindow::on_pushButton_sub_clicked()
{
    if (current_operation_ == Operation::SUBTRACTION)
    {
        return;
    }


    SetOperatorToFormula("−");

    current_operation_ = Operation::SUBTRACTION;

}

//* Умножение
void MainWindow::on_pushButton_mult_clicked()
{
    if (current_operation_ == Operation::MULTIPLICATION)
    {
        return;
    }

    SetOperatorToFormula("×");

    current_operation_ = Operation::MULTIPLICATION;


}

//÷  делениеи
void MainWindow::on_pushButton_div_clicked()
{
    if (current_operation_ == Operation::DIVISION)
    {
        return;
    }

    SetOperatorToFormula("÷");

    current_operation_ = Operation::DIVISION;

}

//^ степень
void MainWindow::on_pushButton_power_clicked()
{
    if (current_operation_ == Operation::POWER)
    {
        return;
    }

    SetOperatorToFormula("^");

    current_operation_ = Operation::POWER;

}

// +/- отрицательное число
void MainWindow::on_pushButton_negative_clicked()
{

    if (input_number_ == "")
        return;

    if (input_number_.startsWith('-')) {
        input_number_ = input_number_.mid(1);
        active_number_ = input_number_.toDouble();
    } else {
        input_number_ = "-" + input_number_;
        active_number_ = input_number_.toDouble();
    }

    ui->l_result->setText(input_number_);
}

//Очистить пмять
void MainWindow::on_pushButton_MemClean_clicked()
{
    if (memory_saved_)
    {
        memory_saved_ = false;
        memory_cell_ = 0;
        ui->l_memory->setText("");
    }
}

//Вывод сохранненых данных в окно калькулятора
void MainWindow::on_pushButton_MemRead_clicked()
{
    if ( memory_saved_  )
    {
        ui->l_result->setText( QString::number(memory_cell_));
        active_number_ = memory_cell_;
        input_number_ = "";
    }
}

//Сохранение  числа в памяти
void MainWindow::on_pushButton_MemSave_clicked()
{
    memory_cell_ = ui->l_result->text().toDouble();
    memory_saved_ = true;
    ui->l_memory->setText("M");
    input_number_ = "";
}



