#include "view.h"
#include "ui_view.h"
#include <QModelIndex>

QString MakeStyleSheet(const QString& new_color, bool bold) {
    return QString("font-weight: %1; color: %2").arg(bold ? "bold" : "normal").arg(new_color);
}

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);
}

View::~View()
{
    delete ui;
}

void View::UpdateCell(size_t x, size_t y, QString new_value) {
    added_buttons_[{x, y}].setText(new_value);
}

void View::SetupField(size_t size_x, size_t size_y) {
    added_buttons_.clear();

    for(size_t i = 0; i < size_x; ++i) {
        for(size_t j = 0; j < size_y; ++j) {
            added_buttons_.emplace(std::pair{i,j}, " ");
            ui->field->addWidget(&added_buttons_[{i, j}], i, j);
            connect(&added_buttons_[{i, j}], &QPushButton::clicked, &added_buttons_[{i, j}], [=, this](){
                if (move_callback_) {
                    move_callback_(i, j);
                }
            });
        }
    }
}

void View::SetStatus(const QString& new_status) {
    ui->l_status->setText(new_status);
}

void View::SetStatusStyle(const QString& new_color, bool bold) {
    ui->l_status->setStyleSheet(MakeStyleSheet(new_color, bold));
}

void View::SetCellStyle(size_t x, size_t y, const QString& new_color, bool bold) {
    auto& button = added_buttons_[{x, y}];

    button.setStyleSheet(MakeStyleSheet(new_color, bold));
}

void View::on_pb_new_game_3_clicked() {
    if (newgame_callback_) {
        newgame_callback_(3, 3);
    }
}

void View::on_pb_new_game_15_clicked() {
    if (newgame_callback_) {
        newgame_callback_(15, 15);
    }
}

void View::on_pb_new_game_34_clicked() {
    if (newgame_callback_) {
        newgame_callback_(3, 4);
    }
}