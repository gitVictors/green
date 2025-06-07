#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"
#include "controller.h"

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
    MainWindow(Game& game, Controller& controller, QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    Game& game_;
    Controller& controller_;
};
#endif // MAINWINDOW_H
