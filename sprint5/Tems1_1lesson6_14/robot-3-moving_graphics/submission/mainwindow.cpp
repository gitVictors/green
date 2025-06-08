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

void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter qt_painter(this);
    Painter game_painter{qt_painter};
    DrawContext context{game_painter};

    game_painter.PreparePaint(
        game_.GetPlayer().GetPosition(),
        game_.GetField().GetRect(),
        {width(), height()}
        );

    // Отрисовка
    game_.DrawFrame(context);
}
