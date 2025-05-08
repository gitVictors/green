#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <functional>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_rb_desc_clicked();

    void on_rb_asc_clicked();

    void on_cb_case_clicked();

    void on_le_unsorted_textChanged(const QString &arg1);

    void SortAndDisplayWords (void);

private:
    Ui::MainWindow *ui;
    bool case_sens_ = false;
    bool rb_asc_ = true;
    bool rb_desc_ = false;
};
#endif // MAINWINDOW_H
