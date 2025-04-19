#include "game.h"

int main() {
    using namespace std::literals;
    Game game;
    std::cout << "Enter max score:"s << std::endl;
    if (int max_score; std::cin >> max_score) {
        game.StartGame(max_score);
    }
}
