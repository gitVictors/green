#include "field_elements.h"
#include "mainwindow.h"

#include "objects.h"
#include "player.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game game{10, 10};
    Player player{game.GetContext(), {5, 5, 0}, Direction::kRight};
    game.SetPlayer(&player);

    Floor& floor0 = game.AddFloor(0);
    Floor& floor1 = game.AddFloor(1);

    EdgeWall edge_wall;
    Door door1;
    Door door2;

    floor0.SetWall({5, 5}, Direction::kLeft, &edge_wall);
    floor0.SetWall({5, 4}, Direction::kLeft, &edge_wall);
    floor0.SetWall({5, 3}, Direction::kLeft, &edge_wall);
    floor0.SetWall({5, 2}, Direction::kLeft, &edge_wall);
    floor0.SetWall({5, 5}, Direction::kDown, &edge_wall);
    floor0.SetWall({5, 5}, Direction::kRight, &edge_wall);
    floor0.SetWall({5, 4}, Direction::kRight, &edge_wall);
    floor0.SetWall({5, 3}, Direction::kRight, &edge_wall);
    floor0.SetWall({5, 2}, Direction::kRight, &edge_wall);
    floor0.SetWall({5, 4}, Direction::kUp, &door1);
    floor0.SetWall({5, 3}, Direction::kUp, &door2);
    Stairs stair_up{game.GetContext(), {5, 1, 0}, Direction::kDown, false};
    Stairs stair_down{game.GetContext(), {5, 1, 1}, Direction::kUp, true};

    Controller controller{game};

    MainWindow w{game, controller};
    w.show();
    return a.exec();
}
