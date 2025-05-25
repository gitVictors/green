#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_add_clicked() {
    // Получите данные о фильме методом GetMovie().
    // Если фильм уже есть в списке, то отредактируйте его.
    // Если нет — добавьте в список.
    // После изменения списка вызовите ApplyModel.
    // После этого можно вызвать ApplyMovie, чтобы
    // данные не сбивались.
    Movie newMovie = GetMovie();

    // Проверка на пустое название
    if(newMovie.name.isEmpty()) {
        return;
    }

    // Поиск фильма в списке
    int index = movies_.indexOf(newMovie);

    if(index != -1) {
        // Фильм найден - редактируем
        movies_[index].rating = newMovie.rating;
        movies_[index].is_watched = newMovie.is_watched;
    } else {
        // Фильм не найден - добавляем
        movies_.append(newMovie);
    }

    // Обновляем модель и интерфейс
    ApplyModel(newMovie);
    ApplyMovie(newMovie);
}

void MainWindow::ApplyModel(const Movie &selection) {
    // Заполните виджеты ui->cb_list_done и ui->cb_list_wait,
    // используя их методы clear и addItems.
    // Вам пригодится метод ToString.
    // Также примените выделение, используя метод 
    // setCurrentIndex.
    // Очищаем списки
    ui->cb_list_done->clear();
    ui->cb_list_wait->clear();

    // Формируем списки фильмов
    QList<Movie> watchedMovies;
    QList<Movie> unwatchedMovies;

    for(const Movie &movie : movies_) {
        if(movie.is_watched) {
            watchedMovies << movie;
        } else {
            unwatchedMovies << movie;
        }
    }

    // Заполняем выпадающие списки
    ui->cb_list_done->addItems(ToString(watchedMovies));
    ui->cb_list_wait->addItems(ToString(unwatchedMovies));

    // Выбираем текущий фильм в соответствующем списке
    if(selection.is_watched) {
        int index = watchedMovies.indexOf(selection);
        if(index != -1) {
            ui->cb_list_done->setCurrentIndex(index);
        }
    } else {
        int index = unwatchedMovies.indexOf(selection);
        if(index != -1) {
            ui->cb_list_wait->setCurrentIndex(index);
        }
    }
}

QString MainWindow::ToString(const Movie &movie) {
    QString str_genre = "";
    switch(movie.genre) {
    case Genre::kComedy : str_genre = "Комедия"; break;
    case Genre::kAction : str_genre = "Боевик"; break;
    case Genre::kDrama : str_genre = "Драма"; break;
    case Genre::kFairyTale : str_genre = "Сказка"; break;
    case Genre::kAnimation : str_genre = "Мультфильм"; break;
    case Genre::kHorror : str_genre = "Ужасы"; break;
    }
    return str_genre + " '" + movie.name + "' рейтинг: " + QString::number(movie.rating);
}

QStringList MainWindow::ToString(const QList<Movie> &movies) {
    // Напишите этот метод. Используйте ToString.
    QStringList result;
    for(const Movie &movie : movies) {
        result << ToString(movie);
    }
    return result;
}

Movie MainWindow::GetMovie() const {
  return Movie{.name = ui->le_name->text(),
    .genre = static_cast<Genre>(ui->cb_genre->currentIndex()),
    .rating = ui->dsb_rating->value(),
    .is_watched = ui->chb_is_done->isChecked()};
}

void MainWindow::ApplyMovie(const Movie &movie) {
    ui->le_name->setText(movie.name);
    ui->cb_genre->setCurrentIndex(static_cast<int>(movie.genre));
    ui->dsb_rating->setValue(movie.rating);
    ui->chb_is_done->setCheckState(movie.is_watched ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

void MainWindow::on_cb_list_wait_currentIndexChanged(int index) {
    // Если index неотрицательный, заполните интерфейс,
    // используя ApplyMovie.
    if(index >= 0) {
        // Получаем список непросмотренных фильмов
        QList<Movie> unwatchedMovies;
        for(const Movie &movie : movies_) {
            if(!movie.is_watched) {
                unwatchedMovies << movie;
            }
        }

        // Применяем выбранный фильм к интерфейсу
        if(index < unwatchedMovies.size()) {
            ApplyMovie(unwatchedMovies[index]);
        }
    }
}

void MainWindow::on_cb_list_done_currentIndexChanged(int index) {
    // Если index неотрицательный, заполните интерфейс,
    // используя ApplyMovie.

    if(index >= 0) {
        // Получаем список просмотренных фильмов
        QList<Movie> watchedMovies;
        for(const Movie &movie : movies_) {
            if(movie.is_watched) {
                watchedMovies << movie;
            }
        }

        // Применяем выбранный фильм к интерфейсу
        if(index < watchedMovies.size()) {
            ApplyMovie(watchedMovies[index]);
        }
    }

}
