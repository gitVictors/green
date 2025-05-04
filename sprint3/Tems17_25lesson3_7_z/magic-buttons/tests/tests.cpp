
// Core headers
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
//#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
//#include <QtWidgets/QListWidget>
//#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtTest>

#include <vector>

#include "mainwindow.h"

#include "utils.h"
#include "actions_logger.h"

class TestYourApp : public QObject
{
    Q_OBJECT
public:
    TestYourApp()=default;
    ~TestYourApp()=default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void TestActions();

private:

    void getButtons();
    void setAction(int button_index, std::function<void()> action);
    inline void clickButton(int button_index);

    MainWindow* window;
    std::vector<QPushButton*> pb_buttons;

    ActionsLogger logger;

};


void TestYourApp::initTestCase()
{

}

#include <iostream>

void TestYourApp::init()
{
    window = new MainWindow();
    QVERIFY2(window != nullptr, "Окно приложения не создано");
    window->show();
    QVERIFY2(window->isVisible(), "Окно приложения не активируется");

    getButtons();
}

void TestYourApp::getButtons()
{
    for (int i = 1; i <= 4; ++i)
    {
        auto pb_name = QString("pb_button_%1").arg(i);
        auto pb_button = getChild<QPushButton>(window, pb_name, "QPushButton");
        pb_buttons.push_back(pb_button);
    }
}

void TestYourApp::setAction(int button_index, std::function<void()> action)
{
    window->slotShowAction(button_index, {}, action);
}

inline void TestYourApp::clickButton(int button_index)
{
    clickWidget(pb_buttons.at(button_index));
}
void TestYourApp::TestActions()
{

    for (int i = 0; i < 4; ++i)
    {
        setAction(i, logger.getAction(i));
    }

    for (int i = 0; i < 4; ++i)
    {
        logger.clear();
        clickButton(i);

        QVERIFY2(logger.checkActionCorrectness(i), qPrintable(QString("Вызвано действие от другой кнопки при нажатии на кнопку %1").arg(i + 1)));
        QVERIFY2(logger.checkActionCalls(i), qPrintable(QString("Количество вызовов действия для кнопки %1 отлично от одного").arg(i + 1)));
    }

}

void TestYourApp::cleanupTestCase()
{
}

void TestYourApp::cleanup()
{
    delete window;
}

QTEST_MAIN(TestYourApp)

#include "tests.moc"
