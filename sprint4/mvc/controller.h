#pragma once

#ifdef PRAC_TESTS
#include "../tests/model.h"
#include "../tests/view.h"
#else
#include "model.h"
#include "view.h"
#endif

class Controller {
public:
    Controller() {
        //начало игры
        auto newGameHandler = [this](size_t x, size_t y) {
            model_.Reset(x, y);
            view_.SetupField(x, y);
            UpdateGameStatus();
        };

        //ход игры
        auto moveGameHandler = [this](size_t row, size_t col ){
            Symbol smb = model_.DoMove(row, col);
            if (smb != Symbol::kEmpty){
                view_.UpdateCell(row,col, ToQString(smb));
                UpdateGameStatus();
            }

        };

        // Устанавливаем обработчики
        view_.SetNewgameCallback(newGameHandler);
        view_.SetMoveCallback(moveGameHandler);

        // Запускаем игру с полем 3x3
        newGameHandler(3, 3);
        view_.show();

    }




private:

    void UpdateGameStatus() {
        auto winner = model_.GetWinner();

        if (!winner.has_value()) {
            // Игра продолжается
            QString status = "Ход игрока " + ToQString(model_.GetNextPlayer());
            view_.SetStatus(status);
            view_.SetStatusStyle("black", false);
        } else if (winner.value() == Symbol::kEmpty) {
            // Ничья
            view_.SetStatus("Ничья");
            view_.SetStatusStyle("red", true);
        } else {
            // Есть победитель
            QString status = "Выиграл " + ToQString(winner.value());
            view_.SetStatus(status);
            view_.SetStatusStyle("green", true);

            // Подсвечиваем выигрышную комбинацию
            for (auto [x, y] : model_.GetWinnerPath()) {
                view_.SetCellStyle(x, y, "green", true);
            }
        }
    }

private:
    Model model_;
    View view_;
};
