#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <iostream>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <string.h>

#include <random>   // со случайными числами
#include <QInputDialog> // Для использования QInputDialog в slots
#include <deque>
#include <algo.h>

using namespace std::literals ;


static std::deque<std::string> tea {
    "Чай Лунцзин",
    "Эрл Грей",
    "Сенча",
    "Пуэр",
    "Дарджилинг",
    "Ассам",
    "Матча",
    "Ганпаудер",
    "Оолонг",
    "Лапсанг Сушонг"
};

static std::deque<std::string> cakes {
    "Красный бархат",
    "Наполеон",
    "Медовик",
    "Тирамису",
    "Прага",
    "Чизкейк",
    "Захер",
    "Эстерхази",
    "Морковный торт",
    "Чёрный лес",
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


    ui->btn_pop_back->setDisabled(/*deque_model_.items.size() == 0*/deque_model_.items.empty());

    if (!deque_model_.items.empty())
        ui->txt_size->setText( QString::number( deque_model_.items.size() ) );
    else
        ui->txt_size->setText("0");


    ui->list_widget->clear();

    if (!deque_model_.items.empty()) {


        auto preserve_iter = deque_model_.iterator;

        size_t index = 0;
        for (const auto& item : deque_model_.items)
        {
            ui->list_widget->addItem(QString::number(index++) + ": " + QString::fromStdString(item));
        }

        deque_model_.iterator = preserve_iter;
    }

    ui->list_widget->addItem("end");

    ApplyIterator();
}

void MainWindow::ApplyIterator() {


    int itr = std::distance( deque_model_.items.begin(), deque_model_.iterator);
    ui->list_widget->setCurrentRow(itr); //выделение

    ui->btn_pop_front->setDisabled(  deque_model_.items.empty() );
    ui->btn_edit->setDisabled(deque_model_.iterator == deque_model_.items.end() );
    ui->btn_pop_back->setDisabled(  deque_model_.items.empty());
    ui->btn_erase->setDisabled(deque_model_.iterator == deque_model_.items.end() );


    ui->btn_inc_iterator->setDisabled(deque_model_.iterator == deque_model_.items.end() );
    ui->btn_dec->setDisabled( deque_model_.iterator == deque_model_.items.begin() );


    if (deque_model_.iterator == deque_model_.items.end()) {
        ui->txt_elem_content->clear();
    } else {
        ui->txt_elem_content->setText( QString::fromStdString(*deque_model_.iterator) );
    }

}

void MainWindow::on_btn_push_back_clicked()
{
    QString txt = ui->txt_elem_content->text();

    if(txt.isEmpty()) return ;

    deque_model_.items.push_back(txt.toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();

}




void MainWindow::on_list_widget_currentRowChanged(int currentRow)
{

    if (currentRow < 0) return;


    if (currentRow >= static_cast<int>(deque_model_.items.size())) {
        deque_model_.iterator = deque_model_.items.end();
    } else {
        deque_model_.iterator = deque_model_.items.begin() + currentRow;
    }

    ApplyIterator();
}


void MainWindow::on_btn_edit_clicked()
{
    QString txt_str =  ui->txt_elem_content->text();

    *deque_model_.iterator = txt_str.toStdString();

    ApplyModel();
}



void MainWindow:: on_btn_resize_clicked() //on_resize_clicked()
{
    QString txt_sz = ui->txt_size->text();

    deque_model_.items.resize( txt_sz.toUInt() );
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}



void MainWindow::on_count_clicked()
{
    std::string txt_f = ui->le_count->text().toStdString();

    int cnt_txt = std::count (deque_model_.items.begin(), deque_model_.items.end(), txt_f );

    ui->lbl_count->setText( QString::number(cnt_txt) );
}



void MainWindow::on_btn_find_clicked()
{
    std::string txt_f =  ui->txt_elem_content->text().toStdString();

    auto itrator = std::find (deque_model_.items.begin(), deque_model_.items.end(), txt_f);

    if (itrator == deque_model_.items.end())
        deque_model_.iterator = deque_model_.items.end();
    else
        deque_model_.iterator = itrator;

    ApplyIterator();

}


void MainWindow::on_min_element_clicked()
{
    auto itr = std::min_element(deque_model_.items.begin(), deque_model_.items.end());

    deque_model_.iterator = itr;

    ApplyIterator();

}


void MainWindow::on_max_element_clicked()
{
    auto itr = std::max_element(deque_model_.items.begin(), deque_model_.items.end());
    deque_model_.iterator = itr;
    ApplyIterator();
}


void MainWindow::on_btn_sort_clicked()
{

    std::deque<std::string> tmp  = deque_model_.items;
    tmp =  MergeSort ( tmp, std::less());
    deque_model_.items.swap(tmp);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();

}


void MainWindow::on_btn_sOrt_clicked()
{


    auto comparator = [](const std::string& s1, const std::string& s2) {
                       return QString::compare(QString::fromStdString(s1), QString::fromStdString(s2), Qt::CaseInsensitive) < 0;
    };

    std::deque<std::string> tmp = deque_model_.items;

    tmp  =   MergeSort (tmp, comparator);

    deque_model_.items.swap(tmp);

    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();

}

void MainWindow::SetRandomGen(const std::mt19937& random_gen) {
    random_gen_ = random_gen;
}


void MainWindow::on_btn_unique_clicked()
{
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        auto last = std::unique(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.items.erase(last, deque_model_.items.end());
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel(); // Обновляем отображение
    } else {
        return;
    }

}


void MainWindow::on_btn_revers_clicked()
{

    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    ApplyModel(); // Обновляем отображение
}


void MainWindow::on_btn_shuffle_clicked()
{
    std::shuffle(deque_model_.items.begin(), deque_model_.items.end(), random_gen_);
    ApplyModel(); // Обновляем отображение

}


void MainWindow::on_btn_pop_front_clicked()
{

    deque_model_.items.pop_front();
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}


void MainWindow::on_btn_push_front_clicked()
{
    QString txt = ui->txt_elem_content->text();

    if(txt.isEmpty()) return ;

    deque_model_.items.push_front(txt.toStdString());
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();

}


void MainWindow::on_btn_pop_back_clicked()
{
    deque_model_.items.pop_back();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}




void MainWindow::on_btn_insert_clicked()
{
    std::string new_item = ui->txt_elem_content->text().toStdString();
    if (!new_item.empty()) {
        deque_model_.items.insert(deque_model_.iterator, new_item);
        deque_model_.iterator = deque_model_.items.begin();
    }
    ApplyModel();
}



void MainWindow::on_btn_clear_clicked()
{
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_dec_clicked()
{
    if (deque_model_.iterator != deque_model_.items.begin()){
        --deque_model_.iterator;
        ui->txt_elem_content->setText( QString::fromStdString(*deque_model_.iterator) );
    }
    ApplyIterator();

}


void MainWindow::on_btn_inc_iterator_clicked()
{
    if (deque_model_.iterator != deque_model_.items.end() ){
        ++deque_model_.iterator;
        if (deque_model_.iterator != deque_model_.items.end())
            ui->txt_elem_content->setText( QString::fromStdString(*deque_model_.iterator) );
    }
    ApplyIterator();
}


void MainWindow::on_btn_begin_clicked()
{
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_btn_end_clicked()
{
    deque_model_.iterator =  deque_model_.items.end();
    ApplyIterator();
}


void MainWindow::on_btn_tea_clicked()
{
    deque_model_.items = tea;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_cakes_clicked()
{
    deque_model_.items = cakes;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_erase_clicked()
{
    if (deque_model_.iterator != deque_model_.items.end()) {
        deque_model_.items.erase(deque_model_.iterator);
        deque_model_.iterator = deque_model_.items.begin();
    }

    ApplyModel(); // Полное обновление, так как изменился контейнер
}


void MainWindow::on_lower_bound_clicked()
{

    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end() ))
        return ;

    // Получаем строку для поиска из интерфейса
    std::string search_value = ui->txt_elem_content->text().toStdString();

    auto it = std::lower_bound(deque_model_.items.begin(), deque_model_.items.end(), search_value);

    deque_model_.iterator = it;
    ApplyIterator();

}


void MainWindow::on_upper_bound_clicked()
{

    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end() ))
        return ;

    // Получаем строку для поиска из интерфейса
    std::string search_value = ui->txt_elem_content->text().toStdString();

    auto it = std::upper_bound(deque_model_.items.begin(), deque_model_.items.end(), search_value);

    deque_model_.iterator = it;
    ApplyIterator();

}

