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

private:
    void ApplyModel();
    void ApplyIterator();

private:
    Model vector_model_;
    Ui::MainWindow *ui;
};

