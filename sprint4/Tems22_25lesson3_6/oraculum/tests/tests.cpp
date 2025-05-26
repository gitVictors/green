
// Core headers
#include <QMessageBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

#include <QtTest>

#include <string>
#include <regex>

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

    void Test1();
    void Test12();
    void Test35();
    void Test51();
    void Test74();
    void Test100();

private:

    enum STATE : int8_t {
        ERROR = -1,
        IS_BIGGER = 0,
        IS_SMALLER = 1,
        FINISH = 2,
    };

    [[nodiscard]] STATE getState() const;
    [[nodiscard]] int getNumber() const;
    void clickCorrectButton(bool is_it_yes) const;
    void runPipeline(int desired_number) const;

    MainWindow *window;

    QLabel *lbl_question{};

    QPushButton *btn_yes{};
    QPushButton *btn_no{};


    const std::regex bigger_regex{"^Ваше число больше \\d+\\?$"};
    const std::regex smaller_regex{"^Ваше число меньше \\d+\\?$"};
    const std::regex finish_regex{"^Ваше число \\d+\\!$"};
    const std::regex number_regex{"\\d+"};
};

void TestYourApp::init()
{
    window = new MainWindow();

    QVERIFY2(window != nullptr, "Главное окно не создано");
    window->show();
    QVERIFY2(window->isVisible(), "Главное окно не активируется");

    btn_yes = getChild<QPushButton>(window, "btn_yes", "QPushButton");
    btn_no = getChild<QPushButton>(window, "btn_no", "QPushButton");

    lbl_question = getChild<QLabel>(window, "lbl_question", "QLabel");
}

TestYourApp::STATE TestYourApp::getState() const
{
    const std::string lbl_question_text = lbl_question->text().toStdString();

    if(std::regex_match(lbl_question_text, bigger_regex)) {
        return IS_BIGGER;
    }
    if(std::regex_match(lbl_question_text, smaller_regex)) {
        return IS_SMALLER;
    }
    if(std::regex_match(lbl_question_text, finish_regex)) {
        return FINISH;
    }
    return ERROR;
}

int TestYourApp::getNumber() const
{
    const std::string lbl_question_text = lbl_question->text().toStdString();

    std::smatch number_match;
    if(std::regex_search(lbl_question_text, number_match, number_regex)) {
        return std::stoi(number_match.str());
    }
    throw std::runtime_error("Number expected but not found!");
}

void TestYourApp::clickCorrectButton(bool is_it_yes) const
{
    const auto& widget = is_it_yes ? btn_yes : btn_no;
    clickWidget(widget);
}

void TestYourApp::runPipeline(const int desired_number) const
{
    int answered_questions = 0;

    while(answered_questions <= 7) {
        const auto current_state = getState();
        if(current_state == ERROR) {
            QVERIFY2(false, "Текст в lbl_question не соответствует шаблонам");
            return;
        }
        const auto current_number = getNumber();
        if(current_state == IS_BIGGER) {
            const bool is_it = desired_number > current_number;
            clickCorrectButton(is_it);
            ++answered_questions;
        }
        else if(current_state == IS_SMALLER) {
            const bool is_it = desired_number < current_number;
            clickCorrectButton(is_it);
            ++answered_questions;
        }
        // Redundant if, just to be sure
        else if(current_state == FINISH) {
            QCOMPARE(current_number, desired_number);
            return;
        }
    }
    QVERIFY2(false, "Алгоритм превысил 7 вопросов, не дав ответ");
}

void TestYourApp::Test1()
{
    runPipeline(1);
}

void TestYourApp::Test12()
{
    runPipeline(12);
}

void TestYourApp::Test35()
{
    runPipeline(35);
}

void TestYourApp::Test51()
{
    runPipeline(51);
}

void TestYourApp::Test74()
{
    runPipeline(74);
}

void TestYourApp::Test100()
{
    runPipeline(100);
}

void TestYourApp::cleanup()
{
    delete window;
}

QTEST_MAIN(TestYourApp)

#include "tests.moc"
