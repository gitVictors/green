#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"

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
    MainWindow(Game& game, QWidget *parent = nullptr);
    ~MainWindow();


    void keyPressEvent(QKeyEvent *event) override {

        if (event->isAutoRepeat()) {
            return QWidget::keyPressEvent(event);
        }

        switch (event->key()) {
        case Qt::Key_Right:
            controller_.OnMoveKey(Direction::kRight);
            break;
        case Qt::Key_Left:
            controller_.OnMoveKey(Direction::kLeft);
            break;
        case Qt::Key_Up:
            controller_.OnMoveKey(Direction::kUp);
            break;
        case Qt::Key_Down:
            controller_.OnMoveKey(Direction::kDown);
            break;

        // Здесь обрабатываются различные клавиши.

        default:
            QWidget::keyPressEvent(event); // call base class implementation
        }
    }



private:
    Ui::MainWindow *ui;
    Game& game_;
};
#endif // MAINWINDOW_H
