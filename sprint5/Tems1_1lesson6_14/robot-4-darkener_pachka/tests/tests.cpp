
// Core headers
#include <QtTest>
#include <QtWidgets/QApplication>
#include <memory>
#include <prac/QTimer>

#include "field_elements.h"
#include "objects.h"
#include "game.h"
#include "mainwindow.h"
#include "player.h"
#include "utility/timer.h"
#include "characters.h"

class TestYourApp : public QObject
{
    Q_OBJECT
public:
    TestYourApp()=default;
    ~TestYourApp()=default;

private slots:

    void init();
    void cleanup();

    void TestContext();
    void TestPaintEvent();
    void TestDarkness();

};

void MakeRoom(Floor& floor, Wall& wall, Tile& tile, int x1, int x2, int y1, int y2) {
    for(int i = x1; i <= x2; ++i) {
        for(int j = y1; j <= y2; ++j) {
            floor.SetTile({i, j}, &tile);
            if (i == x1) {
                floor.SetWall({i, j}, Direction::kLeft, &wall);
            }
            if (i == x2) {
                floor.SetWall({i, j}, Direction::kRight, &wall);
            }
            if (j == y1) {
                floor.SetWall({i, j}, Direction::kUp, &wall);
            }
            if (j == y2) {
                floor.SetWall({i, j}, Direction::kDown, &wall);
            }
        }
    }
}

void TestYourApp::init()
{
}

void TestYourApp::TestContext() {

    QPainter qpainter{};
    Painter painter{qpainter};
    const FlashlightDarkener darkener{CoordinateF{1, 2}, 2, Direction::kRight, 12};
    const DrawContext context{painter, darkener};

    [[maybe_unused]] const Darkener& darkener_ref = context.darkener;

}


void TestYourApp::TestPaintEvent() {
    //TODO
    AssetLoader loader;

    Game game{loader, 15, 15};
    Player player{game.GetContext(), {5, 5, 0}, Direction::kRight};
    game.SetPlayer(&player);
    Controller controller{game};
    game.AddFloor(0);

    MainWindow window{game, controller};
    window.show();
    QVERIFY(window.isVisible());

    window.paintEvent(nullptr);

    const auto& [start_point, radius, direction, distance] = FlashlightDarkener::getLastDarkenerParams();

    QVERIFY(start_point == CoordinateF(5, 5, 0));
    QVERIFY(direction == Direction::kRight);
    QVERIFY(radius == 7);
    QVERIFY(distance == 4);

}


void TestYourApp::TestDarkness() {

    //TODO
    AssetLoader loader;

    Game game{loader, 15, 15};
    Player player{game.GetContext(), {5, 5, 0}, Direction::kRight};
    game.SetPlayer(&player);
    Controller controller{game};
    game.AddFloor(0);
    Victim victim{game.GetContext(), {12, 3, 0}, Direction::kRight};

    MainWindow window{game, controller};
    window.show();
    QVERIFY(window.isVisible());
    window.paintEvent(nullptr);

    double last_darkness = Painter::GetLastDarkness();


    const auto& [start_point, radius, direction, distance] = FlashlightDarkener::getLastDarkenerParams();
    FlashlightDarkener used_darkener(start_point, radius, direction, distance);

    double expected_darkness = used_darkener.GetDarkness(CoordinateF(12, 3, 0));

    qDebug() << last_darkness << "\t" << expected_darkness << "\t" << (expected_darkness == last_darkness);
    QVERIFY(expected_darkness == last_darkness);

}


void TestYourApp::cleanup()
{
}

QTEST_MAIN(TestYourApp)

#include "tests.moc"
