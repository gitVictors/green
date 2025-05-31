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

    void on_btn_set_by_key_clicked();

    void on_btn_erase_clicked();

    void on_list_widget_currentRowChanged(int currentRow);

    void on_btn_clear_clicked();

    void on_btn_find_clicked();

    void on_btn_inc_iterator_clicked();

    void on_btn_dec_iterator_clicked();

    void on_btn_begin_clicked();

    void on_btn_end_clicked();

    void on_btn_books_clicked();

    void on_btn_words_clicked();

private:
    void ApplyModel();
    void ApplyIterator();

private:
    Model map_model_;
    Ui::MainWindow *ui;
};
