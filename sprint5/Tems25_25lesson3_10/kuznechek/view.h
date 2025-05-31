#pragma once

#include <algorithm>
#include <iostream>
#include <map>

class View {
public:
    // Выводит текущий счёт.
    void ShowScore(int score) {
        std::cout << "Current score: " << score << std::endl;
    }

    // Выводит игровое поле.
    void PrintBoard(int grasshopper_pos, int fly_pos, int board_size) {
        for (int i = 0; i < board_size; i++) {
            if (i == grasshopper_pos) {
                std::cout << "k";
            } else if (i == fly_pos) {
                std::cout << "o";
            } else {
                std::cout << "-";
            }
        }
        std::cout << std::endl;
    }

    // Получает ввод пользователя — количество прыжков кузнечика.
    int GetUserInput() {
        int hops;
        if (!(std::cin >> hops)) {
            std::cerr << "Can't read input" << std::endl;
            return 0;
        }
        return hops;
    }

    // Выводит сообщение о победе.
    void ShowWinMessage() {
        std::cout << "You win!" << std::endl;
    }
};