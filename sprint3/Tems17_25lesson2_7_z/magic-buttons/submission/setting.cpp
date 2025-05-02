#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    for (const auto& action : actions_) {
        ui->cb_action->addItem(action.name);
    }
}

Setting::~Setting() {
    delete ui;
}

void Setting::on_pb_save_clicked() {
    auto index = ui->cb_action->currentIndex();
    if (index < 0 || static_cast<size_t>(index) >= actions_.size()) {
        return;
    }

    emit signalSetAction(current_button_idx_, actions_[index].name, actions_[index].action);
    ui->cb_action->setCurrentIndex(0);
    this->close();
}
