#pragma once
#include <QMainWindow>
#include <QDebug>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();

    void SetupField(size_t size_x, size_t size_y);

    void UpdateCell(size_t x, size_t y, QString new_value);
    void SetCellStyle(size_t x, size_t y, const QString& new_color, bool bold);

    void SetStatus(const QString& status);
    void SetStatusStyle(const QString& new_color, bool bold);

    void SetMoveCallback(const std::function<void (size_t x,size_t y)>& callback) {
        move_callback_ = callback;
    }

    void SetNewgameCallback(const std::function<void (size_t size_x,size_t size_y)>& callback) {
        newgame_callback_ = callback;
    }

private slots:
    void on_pb_new_game_3_clicked();

    void on_pb_new_game_15_clicked();

    void on_pb_new_game_34_clicked();

private:
    Ui::View *ui;

    std::map<std::pair<size_t, size_t>, QPushButton> added_buttons_;
    std::function<void (size_t x,size_t y)> move_callback_;
    std::function<void (size_t size_x,size_t size_y)> newgame_callback_;
};