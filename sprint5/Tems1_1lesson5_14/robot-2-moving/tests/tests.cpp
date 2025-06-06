
// Core headers
#include <QtTest>
#include <QTest>

#include <QtWidgets/QApplication>
#include <memory>
#include <prac/QTimer>

#include "characters.h"
#include "field_elements.h"
#include "game.h"
#include "mainwindow.h"
#include "objects.h"
#include "player.h"
#include "utility/timer.h"

class ActiveCharacter : public Character {
public:
    ActiveCharacter(GameContext& context, Coordinate position, Direction dir)
        : Character(context, position, dir) {
    }
    [[nodiscard]] bool IsActive() const override {
        return true;
    }
};

class TestYourApp : public QObject {
    Q_OBJECT
public:
    TestYourApp() = default;
    ~TestYourApp() = default;

private slots:

    void init();
    void cleanup();

    void TestFloor();
    void TestField();
    void TestCharacter();
    void TestDoor();
    void TestStairs();
    void TestGame();
    void TestController();
    void TestKeyEvents();

private:
    std::shared_ptr<MainWindow> window;
    std::shared_ptr<Game> game;
    std::shared_ptr<Controller> controller;
    std::shared_ptr<EdgeWall> edge_wall;
    std::shared_ptr<EmptyWall> empty_wall;
    std::shared_ptr<Door> door1, door2;
};

void MakeRoom(Floor& floor, Wall& wall, Tile& tile, int x1, int x2, int y1, int y2) {
    for (int i = x1; i <= x2; ++i) {
        for (int j = y1; j <= y2; ++j) {
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

void TestYourApp::init() {
    game.reset();
    controller.reset();
    game = std::make_shared<Game>(10, 12);
    controller = std::make_shared<Controller>(*game);

    Floor& floor0 = game->AddFloor(0);
    Floor& floor1 = game->AddFloor(1);


    edge_wall = std::make_shared<EdgeWall>();
    empty_wall = std::make_shared<EmptyWall>();
    door1 = std::make_shared<Door>();
    door2 = std::make_shared<Door>();

    floor0.SetWall({5, 5}, Direction::kLeft, edge_wall.get());
    floor0.SetWall({5, 4}, Direction::kLeft, edge_wall.get());
    floor0.SetWall({5, 3}, Direction::kLeft, edge_wall.get());
    floor0.SetWall({5, 2}, Direction::kLeft, edge_wall.get());
    floor0.SetWall({5, 5}, Direction::kDown, edge_wall.get());
    floor0.SetWall({5, 5}, Direction::kRight, edge_wall.get());
    floor0.SetWall({5, 4}, Direction::kRight, empty_wall.get());
    floor0.SetWall({5, 3}, Direction::kRight, edge_wall.get());
    floor0.SetWall({5, 2}, Direction::kRight, edge_wall.get());
    floor0.SetWall({5, 4}, Direction::kUp, door1.get());
    floor0.SetWall({5, 2}, Direction::kUp, door2.get());
    // stairs_up = std::make_shared<Stairs>(game->GetContext(), {5, 1, 0}, Direction::kDown, false);
    // stairs_down = std::make_shared<Stairs>(game->GetContext(), {5, 1, 1}, Direction::kUp, true);

    window = std::make_shared<MainWindow>(*game, *controller);
    window->show();
    QVERIFY2(window->isVisible(), "Главное окно не активируется");
}

void TestYourApp::TestFloor() {
    Floor floor(2, 15, 10);
    QCOMPARE(floor.GetLevel(), 2);
    for (int x = 0; x < 15; x += 2) {
        for (int y = 0; y < 5; ++y) {
            floor.SetTile({x, y}, new FloorTile);
            floor.SetWall({x, y}, Direction::kRight, new EdgeWall);
        }
        for (int y = 5; y < 10; y += 2) {
            floor.SetTile({x, y}, new FloorTile);
            qInfo() << "Setting up wall" << x << "," << y;
            floor.SetWall({x, y}, Direction::kLeft, new EdgeWall);
        }
    }
    for (int x = 0; x < 15; x += 2) {
        for (int y = 0; y < 5; y += 2) {
            try {
                const auto wall = floor.GetWall({x, y}, Direction::kRight);
                QVERIFY(wall != nullptr);
                QVERIFY(floor.GetWall({x, y}, Direction::kLeft) == nullptr);
                QVERIFY(floor.GetWall({x, y}, Direction::kDown) == nullptr);
                QVERIFY(floor.GetWall({x, y}, Direction::kUp) == nullptr);
            } catch (const std::exception& e) {
                QFAIL(e.what());
            }
        }
        for (int y = 5; y < 10; y += 2) {
            try {
                const auto wall = floor.GetWall({x, y}, Direction::kLeft);
                QVERIFY(wall != nullptr);
                QVERIFY(floor.GetWall({x, y}, Direction::kRight) == nullptr);
                QVERIFY(floor.GetWall({x, y}, Direction::kDown) == nullptr);
                QVERIFY(floor.GetWall({x, y}, Direction::kUp) == nullptr);
            } catch (const std::exception& e) {
                QFAIL(e.what());
            }
        }
    }
}

void TestYourApp::TestField() {
    Field field(15, 21);
    QCOMPARE(field.GetWidth(), 15);
    QCOMPARE(field.GetHeight(), 21);
    const Size size = field.GetRect();
    QCOMPARE(size.width, 15);
    QCOMPARE(size.height, 21);

    field.AddFloor(2);
    Floor& floor = field.GetFloor(2);

    floor.SetWall({0, 0}, Direction::kUp, new EdgeWall);
    floor.SetWall({14, 20}, Direction::kDown, new EdgeWall);

    QVERIFY(floor.GetWall({0, 0}, Direction::kUp) != nullptr);
    QVERIFY(floor.GetWall({14, 20}, Direction::kDown) != nullptr);
}

void TestYourApp::TestCharacter() {
    Character character(game->GetContext(), {5, 4, 0}, Direction::kRight);
    qInfo() << "Placing active character";
    ActiveCharacter active_character(game->GetContext(), {5, 5, 0}, Direction::kRight);

    QVERIFY(character.CanPassWall(Direction::kRight));  // Empty wall
    QVERIFY(!character.CanPassWall(Direction::kLeft));  // Edge Wall
    QVERIFY(character.CanPassWall(Direction::kDown));   // No wall
    QVERIFY(!character.CanPassWall(Direction::kUp));    // Closed door

    QVERIFY(character.CanGo(Direction::kRight));  // Nothing
    QVERIFY(!character.CanGo(Direction::kDown));  // active_character
    QVERIFY(door1->CanPass(active_character, Direction::kLeft) == false);
    door1->Interact(active_character, Direction::kRight);
    QVERIFY(door1->CanPass(active_character, Direction::kLeft) == true);
    QVERIFY(character.CanPassWall(Direction::kUp));  // Opened door
}

void TestYourApp::TestDoor() {
    ActiveCharacter active_character(game->GetContext(), {1, 2, 0}, Direction::kRight);
    QVERIFY(door2->CanPass(active_character, Direction::kUp) == false);
    door2->Interact(active_character, Direction::kRight);
    QVERIFY(door2->CanPass(active_character, Direction::kUp) == true);
}

void TestYourApp::TestStairs() {
    constexpr Coordinate initial_pose{5, 2, 0};
    ActiveCharacter active_character(game->GetContext(), initial_pose, Direction::kUp);
    QCOMPARE(active_character.GetPosition(), initial_pose);
    Stairs stairs_up{game->GetContext(), {5, 1, 0}, Direction::kDown, false};
    Stairs stairs_down{game->GetContext(), {5, 1, 1}, Direction::kUp, true};

    // Interaction in the wrong directions - do nothing
    stairs_up.Interact(active_character, Direction::kRight);
    QCOMPARE(active_character.GetPosition(), initial_pose);

    stairs_up.Interact(active_character, Direction::kLeft);
    QCOMPARE(active_character.GetPosition(), initial_pose);

    stairs_up.Interact(active_character, Direction::kDown);
    QCOMPARE(active_character.GetPosition(), initial_pose);

    // Once interacted in the correct on - go up a level and another cell forward
    // so it'll be next to stairs on the second level
    stairs_up.Interact(active_character, Direction::kUp);
    const Coordinate expected_pose
        = initial_pose + Coordinate::FromDirection(Direction::kUp) * 2 + Coordinate(0, 0, 1);
    QCOMPARE(active_character.GetPosition(), expected_pose);

    // Same with going down - wrong direction shouldn't make any effect
    stairs_down.Interact(active_character, Direction::kRight);
    QCOMPARE(active_character.GetPosition(), expected_pose);
    stairs_down.Interact(active_character, Direction::kUp);
    QCOMPARE(active_character.GetPosition(), expected_pose);
    stairs_up.Interact(active_character, Direction::kLeft);
    QCOMPARE(active_character.GetPosition(), expected_pose);

    // Once interacted correctly - should return character to the initial position
    stairs_down.Interact(active_character, Direction::kDown);
    QCOMPARE(active_character.GetPosition(), initial_pose);
}

void TestYourApp::TestGame(){

    Player player {game->GetContext(), {3, 3, 0}, Direction::kRight};
    game->SetPlayer(&player);

    const Player& player_link = game->GetPlayer();

    QVERIFY(player.GetPosition() == Coordinate(3, 3, 0));
    QVERIFY(&player_link == &player);

    Floor& floor0 = game->GetCurrentFloor();  // Should be the floor #0
    Field& field = game->GetField();

    const auto left_wall = floor0.GetWall({5, 4}, Direction::kRight); // Empty wall
    const auto same_left_wall = field.GetFloor(0).GetWall({5, 4}, Direction::kRight);

    QVERIFY(left_wall != nullptr);
    QVERIFY(left_wall->CanPass(player, Direction::kLeft));

    QVERIFY(same_left_wall != nullptr);
    QVERIFY(same_left_wall->CanPass(player, Direction::kLeft));

    QVERIFY(left_wall == same_left_wall);
}

void TestYourApp::TestController(){

    Coordinate expected_position{3, 3, 0};
    Direction expected_direction = Direction::kRight;
    Player player {game->GetContext(), expected_position, expected_direction};
    game->SetPlayer(&player);
    QVERIFY(player.GetPosition() == expected_position);
    QVERIFY(player.GetDirection() == expected_direction);

    expected_direction = Direction::kLeft;
    controller->OnMoveKey(expected_direction);

    QVERIFY(player.GetDirection() == expected_direction);
    QVERIFY(player.GetPosition() == expected_position);

    expected_position = expected_position + Coordinate::FromDirection(expected_direction);
    controller->OnMoveKey(expected_direction);
    QVERIFY(player.GetDirection() == expected_direction);
    QVERIFY(player.GetPosition() == expected_position);
}

void TestYourApp::TestKeyEvents(){
    Coordinate expected_position{3, 3, 0};
    Direction expected_direction = Direction::kRight;
    Player player {game->GetContext(), expected_position, expected_direction};
    game->SetPlayer(&player);
    QVERIFY(player.GetPosition() == expected_position);
    QVERIFY(player.GetDirection() == expected_direction);

    QTest::keyPress(window.get(), Qt::Key_Left);
    expected_direction = Direction::kLeft;
    QVERIFY(player.GetDirection() == expected_direction);
    QVERIFY(player.GetPosition() == expected_position);

    expected_position = expected_position + Coordinate::FromDirection(expected_direction);
    QTest::keyPress(window.get(), Qt::Key_Left);
    QVERIFY(player.GetDirection() == expected_direction);
    QVERIFY(player.GetPosition() == expected_position);
}


void TestYourApp::cleanup() {
}

QTEST_MAIN(TestYourApp)

#include "tests.moc"
