#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

// Инициализация статических членов
Model::Map Model::words = {
    {"Book", "Книга"},
    {"Cinnamon", "Корица"},
    {"Cup", "Чашка"},
    {"Kettle", "Чайник"},
    {"Saucer", "Блюдце"},
    {"Sugar", "Сахар"},
    {"Tea", "Чай"},
    {"Teaspoon", "Чайная ложка"},
    };

Model::Map Model::authors_and_books = {
    {"Т. Пратчетт", "Плоский мир"},
    {"Р. Брэдбери", "Лёд и пламя"},
    {"Д. Адамс", "В основном безвредна"},
    {"Ф. Дик", "Солнечная лотерея"},
    {"А. и Б. Стругацкие", "Жук в муравейнике"},
    {"Ф. Кафка", "Превращение"},
    };

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    // Сохраняем текущую позицию итератора
    auto it_tmp = map_model_.iterator;

    ui->list_widget->clear();
    for (const auto& [key, value] : map_model_.items) {
        ui->list_widget->addItem(QString::fromStdString(key + ": " + value));
    }

    ui->list_widget->addItem("end");

    // Восстанавливаем итератор
    map_model_.iterator = it_tmp;
    ApplyIterator();

    // Обновляем размер
    ui->txt_size->setText(QString::number(map_model_.items.size()));
}

void MainWindow::ApplyIterator() {

    // Устанавливаем выделение на текущий элемент итератора

    int index = std::distance(map_model_.items.begin(), map_model_.iterator);
    ui->list_widget->setCurrentRow(index);

    // Обновляем активность кнопок
    ui->btn_erase->setEnabled(map_model_.iterator != map_model_.items.end());
    ui->btn_dec_iterator->setEnabled(map_model_.iterator != map_model_.items.begin());
    ui->btn_inc_iterator->setEnabled(map_model_.iterator != map_model_.items.end());
 // &&  std::next(map_model_.iterator) != map_model_.items.end());



    if (map_model_.iterator != map_model_.items.end()) {
        // Обновляем поля ключа и значения
        ui->txt_elem_key->setText(QString::fromStdString(map_model_.iterator->first));
        ui->txt_elem_value->setText(QString::fromStdString(map_model_.iterator->second));
    } else {
        ui->txt_elem_key->clear();
        ui->txt_elem_value->clear();
    }

}
void MainWindow::on_btn_set_by_key_clicked()
{
    std::string key = ui->txt_elem_key->text().toStdString();
    std::string value = ui->txt_elem_value->text().toStdString();

    if (!key.empty())
    {
        map_model_.items[key] = value;
        ApplyModel();
    }
}


void MainWindow::on_btn_erase_clicked()
{
    if (map_model_.iterator != map_model_.items.end()) {
        map_model_.items.erase(map_model_.iterator);
        map_model_.iterator = map_model_.items.begin(); // После erase итератор инвалидируется
        ApplyModel();
    }

}


void MainWindow::on_list_widget_currentRowChanged(int currentRow)
{
    if(currentRow >= 0){
        auto it = map_model_.items.begin();
        std::advance(it, currentRow);
        map_model_.iterator = it;
        ApplyIterator();
    }
}


void MainWindow::on_btn_clear_clicked()
{
    map_model_.items.clear();
    map_model_.iterator = map_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_find_clicked()
{
    std::string key = ui->txt_elem_key->text().toStdString();
    if (!key.empty()) {
        map_model_.iterator = map_model_.items.find(key);
        ApplyIterator();
    }
}


void MainWindow::on_btn_inc_iterator_clicked()
{
    // if (map_model_.iterator != map_model_.items.end()) {

    // }

    ++map_model_.iterator;
    ApplyIterator();
}


void MainWindow::on_btn_dec_iterator_clicked()
{
    if (map_model_.iterator != map_model_.items.begin()) {
        --map_model_.iterator;
    }
    ApplyIterator();
}


void MainWindow::on_btn_begin_clicked()
{
    map_model_.iterator = map_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_btn_end_clicked()
{
    map_model_.iterator = map_model_.items.end();
    ApplyIterator();
}


void MainWindow::on_btn_books_clicked()
{
    map_model_.items = Model::authors_and_books;
    map_model_.iterator = map_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_words_clicked()
{
    map_model_.items = Model::words;
    map_model_.iterator = map_model_.items.begin();
    ApplyModel();
}

