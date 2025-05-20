#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_push_back_clicked();

    void on_clear_clicked();

    void on_pop_back_clicked();

    void on_days_clicked();

    void on_month_clicked();

    void on_list_widget_currentRowChanged(int currentRow);

    void on_btn_edit_clicked();

    void on_erase_clicked();

    void on_insert_clicked();

    void on_minus_minus_clicked();

    void on_plus_plus_clicked();

    void on_begin_clicked();

    void on_end_clicked();

    void on_btn_reserve_clicked();

    void on_btn_resize_clicked();

    void on_count_clicked();


    void on_btn_find_clicked();

    void on_min_element_clicked();

    void on_max_element_clicked();

private:
    void ApplyModel();
    void ApplyIterator();

private:
    Model vector_model_;
    Ui::MainWindow *ui;
};

