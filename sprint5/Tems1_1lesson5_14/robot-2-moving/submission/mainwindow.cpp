#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Game& game, Controller& controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , game_(game)
    , controller_(controller)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
