
// Core headers
#include <QtTest>
#include <QtWidgets/QApplication>
#include <memory>
#include <prac/QTimer>

#include "characters.h"
#include "field_elements.h"
#include "game.h"
#include "mainwindow.h"
#include "objects.h"
#include "player.h"
#include "utility/assets.h"
#include "utility/random.h"
#include "utility/timer.h"
#include "utility/utility.h"

class TestYourApp : public QObject {
    Q_OBJECT
public:
    TestYourApp() = default;
    ~TestYourApp() = default;

private slots:

    void init();
    void cleanup();

    void TestContext();
    void TestDoorDrawing();
    void TestFloorDrawing();
};


void TestYourApp::init() {
}

void TestYourApp::TestContext() {
    ObjectMap<Object> object_map{};
    Field field{10, 20};
    RandomGen random_gen;
    AssetLoader asset_loader;
    const GameContext context{object_map, field, random_gen, asset_loader};

    [[maybe_unused]] const RandomGen& random_gen_ref = context.random;
    [[maybe_unused]] const AssetLoader& asset_loader_ref = context.asset_loader;

    QPainter qpainter{};
    Painter painter{qpainter};
    const DrawContext draw_context{painter};
    [[maybe_unused]] const Painter& painter_ref = draw_context.painter;
}

void TestYourApp::TestDoorDrawing() {
    QPainter qpainter{};
    Painter painter{qpainter};
    DrawContext draw_context{painter};
    constexpr Coordinate current_pose{10, 20};
    constexpr Orientation direction{Orientation::kHorizontal};
    const Door door;
    door.Draw(draw_context, current_pose, direction);

    auto& rect_params = painter.GetRectParams();

    QVERIFY(rect_params.size() == 2);

    // First frame
    const auto first_params = rect_params.at(0);

    QCOMPARE(first_params.p1, CoordinateF(current_pose));
    QCOMPARE(first_params.p2, CoordinateF(current_pose) + CoordinateF(0, 0, 1));
    QCOMPARE(first_params.p3,
             first_params.p2 + CoordinateF(Coordinate::FromOrientation(direction)) * 0.5);

    // Second frame
    const auto second_params = rect_params.at(1);

    QCOMPARE(second_params.p1,
             CoordinateF(current_pose) + CoordinateF(Coordinate::FromOrientation(direction)));
    QCOMPARE(second_params.p2, second_params.p1 + CoordinateF(0, 0, 1));
    QCOMPARE(second_params.p3,
             second_params.p2 - CoordinateF(Coordinate::FromOrientation(direction)) * 0.5);

    rect_params.clear();

    constexpr QColor expected_fill{100, 100, 100, 128};
    constexpr QColor expected_edge{50, 50, 100, 128};
    constexpr int expected_width = 1;

    QCOMPARE(first_params.fill_color, expected_fill);
    QCOMPARE(second_params.fill_color, expected_fill);

    QCOMPARE(first_params.edge_color, expected_edge);
    QCOMPARE(second_params.edge_color, expected_edge);

    QCOMPARE(first_params.edge_width, expected_width);
    QCOMPARE(second_params.edge_width, expected_width);
}

class TestTile final : public Tile {
public:
    void Draw(DrawContext&, Coordinate) const override {
        ++rendered;
    }
    int getRendered() const {
        return rendered;
    }

private:
    mutable int rendered{0};
};

void TestYourApp::TestFloorDrawing() {
    std::vector<std::shared_ptr<TestTile>> tiles{};

    Floor floor{5, 12, 17};
    for (int x = 3; x < 7; ++x) {
        for (int y = 5; y < 12; ++y) {
            auto new_tile = std::make_shared<TestTile>();
            floor.SetTile(Coordinate2D(x, y), new_tile.get());
            tiles.push_back(new_tile);
        }
    }

    for (int x = 10; x < 12; ++x) {
        for (int y = 15; y < 17; ++y) {
            auto new_tile = std::make_shared<TestTile>();
            floor.SetTile(Coordinate2D(x, y), new_tile.get());
            tiles.push_back(new_tile);
        }
    }

    QPainter qpainter{};
    Painter painter{qpainter};
    DrawContext draw_context{painter};

    floor.DrawFloor(draw_context);

    for (const auto& tile : tiles) {
        QVERIFY(tile->getRendered() == 1);
    }
}

void TestYourApp::cleanup() {
}

QTEST_MAIN(TestYourApp)

#include "tests.moc"
