#include "field_elements.h"
#include "mainwindow.h"

#include "player.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game game{};
    Player player{game.GetContext(), {10, 10, 0}, Direction::kRight};
    FloorTile floor1;
    EdgeWall wall1;

    MainWindow w{game};
    w.show();
    return a.exec();
}
