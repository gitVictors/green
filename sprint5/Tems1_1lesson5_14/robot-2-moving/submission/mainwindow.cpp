#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Game& game, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , game_(game)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
