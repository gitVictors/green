#include "setting.h"
#include "ui_setting.h"
#include <../../../mocks_library/prac/QInputDialog>

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    for (const auto& action : actions_) {
        ui->cb_action->addItem(action.name);
    }

    ui->cb_action->addItem("Открыть URL ");
    ui->cb_action->addItem("Открыть папку ");

}

Setting::~Setting() {
    delete ui;
}


void Setting::on_pb_save_clicked() {
    auto index = ui->cb_action->currentIndex();
    if (index < 0 || static_cast<size_t>(index) >= actions_.size()+2) {
        return;
    }

    if ( index >= 0 && index <= 4 ){

        emit signalSetAction(current_button_idx_, actions_[index].name, actions_[index].action);

    }else if (index == 5){
        // Запрашиваем URL у пользователя.
        QString user_input = prac::QInputDialog::getText(this, "Введите URL", "URL:");
        auto action = [=](){OpenCustomUrl(user_input);};
        emit signalSetAction(current_button_idx_, "Введите URL "+user_input, action);
    }else if (index == 6){
        QString user_input = prac::QInputDialog::getText(this, "Введите пруть", "Путь:");
        auto action = [=]() { OpenCustomDirectory(user_input); };
        emit signalSetAction(current_button_idx_, "Введите пруть "+user_input, action);
    }

    ui->cb_action->setCurrentIndex(0);
    this->close();
}
