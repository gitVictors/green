#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(Game& game, Controller& controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , game_(game)
    , controller_{controller}
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
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
    default:
        QWidget::keyPressEvent(event); // call base class implementation
    }
}
