
// Core headers
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>

#include <QtTest>

#include <iostream>

#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

#include "field_elements.h"
#include "player.h"
#include "characters.h"
#include "objects.h"

#include "mainwindow.h"

#include "utils.h"


class TestYourApp : public QObject
{
    Q_OBJECT
public:
    TestYourApp()=default;
    ~TestYourApp()=default;

private slots:
    void init();
    void cleanup();

    void TestByStaticAsserts();

private:

    MainWindow *window;
};


void TestYourApp::init()
{
    Game game{};
    window = new MainWindow{game};

    QVERIFY2(window != nullptr, "Главное окно не создано");
    window->show();
    QVERIFY2(window->isVisible(), "Главное окно не активируется");
}

void TestYourApp::TestByStaticAsserts() {
    static_assert(std::is_base_of<Character, Player>::value, "Player must derive from Character");
    static_assert(std::is_base_of<Character, Victim>::value, "Victim must derive from Character");
    static_assert(std::is_base_of<Object, Character>::value, "Character must derive from Object");
    static_assert(std::is_base_of<Object, Stairs>::value, "Stairs must derive from Object");

    static_assert(std::is_base_of<Wall, EmptyWall>::value, "EmptyWall must derive from Wall");
    static_assert(std::is_base_of<Wall, EdgeWall>::value, "EdgeWall must derive from Wall");
    static_assert(std::is_base_of<Wall, Door>::value, "Door must derive from Wall");
    static_assert(std::is_base_of<Tile, EmptyTile>::value, "EmptyTile must derive from Tile");
    static_assert(std::is_base_of<Tile, FloorTile>::value, "FloorTile must derive from Tile");
}

void TestYourApp::cleanup()
{
    delete window;
}

QTEST_MAIN(TestYourApp)

#include "tests.moc"
