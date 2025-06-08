#include "mainwindow.h"
#include "qevent.h"
#include "ui_mainwindow.h"
#include "utility/painter.h"

MainWindow::MainWindow(Game& game, Controller& controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , game_(game)
    , controller_{controller}
{
    ui->setupUi(this);
    controller_.SetRedrawCallback([this](){this->repaint();});
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

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter qpainter(this);

    //Инициализируем графический движок
    Painter  game_painter(qpainter);

    Size window_size{width(), height()};
    auto player_pos = game_.GetPlayer().GetPosition();
    auto field_size = game_.GetField().GetRect();

    //Насройка графического движка
    game_painter.PreparePaint(player_pos, field_size, window_size);

    DrawContext context{
        .painter = game_painter
    };

    //Отрисовка
    game_.DrawFrame(context);
}

