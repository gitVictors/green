#pragma once

#include "calculator.h"

#include <QMainWindow>

enum class Operation {
    NO_OPERATION,
    MULTIPLICATION,
    DIVISION,
    SUBTRACTION,
    ADDITION,
    POWER,
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

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

    //void SetNumIfNotOperation (double act);
    void SetOperatorToFormula (QString opr);
    void CalculatingExpression (QString oprt );
    void SetNumberToFormula (QString num);

private:
    Ui::MainWindow* ui;
    Operation current_operation_ = Operation::NO_OPERATION;
    QString input_number_ = "0";
    Calculator calculator_;
    double active_number_;
    double memory_cell_;
    bool memory_saved_ = false;
    bool dot_ = false;
};
