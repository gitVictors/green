#include <cassert>
#include <iostream>

#include "mocks.h"
#include "controller.h"

void GrasshopperTestEasy(){
    unsigned int seed = 42;
    int board_size = 10;
    int winning_score = 3;

    MockModel mock_model(seed, board_size);
    MockView mock_view;
    Controller controller(mock_view, mock_model, winning_score);

    controller.StartGame();

    const auto& mock_results = mock_view.GetCounter();
    assert(mock_results.at("ShowScore") == 3);
    assert(mock_results.at("PrintBoard") == 3);
    assert(mock_results.at("GetUserInput") == 3);
    assert(mock_results.at("ShowWinMessage") == 1);
}

void GrasshopperTestHard(){
    unsigned int seed = 1984;
    int board_size = 100;
    int winning_score = 5;

    MockModel mock_model(seed, board_size);
    MockView mock_view;
    Controller controller(mock_view, mock_model, winning_score);

    controller.StartGame();

    const auto& mock_results= mock_view.GetCounter();
    assert(mock_results.at("ShowScore") == 5);
    assert(mock_results.at("PrintBoard") == 5);
    assert(mock_results.at("GetUserInput") == 5);
    assert(mock_results.at("ShowWinMessage") == 1);
}


int main() {
    GrasshopperTestEasy();
    GrasshopperTestHard();
    std::cout << "All tests passed!" << std::endl;
}