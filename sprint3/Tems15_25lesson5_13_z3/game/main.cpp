#include "game.h"
#include <windows.h>

using namespace std::literals;

int main() {
    // Установка кодовой страницы UTF-8 для Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int board_size, scores;
    std::cout << "Размер поля: "s << std::endl;
    std::cin >> board_size;
    std::cout << "Сколько очков нужно для победы: "s << std::endl;
    std::cin >> scores;

    std::random_device rd;

    Game game{rd(), board_size, scores};
    game.Start();
}
