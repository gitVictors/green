
// Core headers

#include <QtWidgets/QWidget>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>

#include <QtTest>

#include <vector>
#include <string>

#include "mainwindow.h"

#include "utils.h"


class TestYourApp : public QObject
{
    Q_OBJECT
public:
    TestYourApp()=default;
    ~TestYourApp()=default;

private slots:
    void cleanupTestCase();
    void init();
    void cleanup();
    void Test1();
    void Test2();
    void Test3();
    void Test4();
    void Test5();



private:
    static void setLogger();
    static void log(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    void checkLogs(const std::vector<QString>& expected_logs) const;

    MainWindow *window;

    QPushButton *btn_convert_to_miles{};
    QPushButton *btn_convert_to_km{};

    QLineEdit *txt_km_input{};
    QLineEdit *txt_miles_input{};

    static inline std::vector<QString> logs;
};

void TestYourApp::log(const QtMsgType type, [[maybe_unused]] const QMessageLogContext &context, const QString &msg) {
    const QString message = qFormatLogMessage(type, context, msg);
    logs.push_back(message);
}

void TestYourApp::setLogger() {
    logs.clear();
    const QString pattern ="%{if-debug}DEBUG%{endif}%{if-info}INFO%{endif}%{if-warning}WARNING%{endif}%{if-critical}CRITICAL%{endif}%{if-fatal}FATAL%{endif}: %{message}";
    qSetMessagePattern(pattern);
    qInstallMessageHandler(log);
}

void TestYourApp::checkLogs(const std::vector<QString>& expected_logs) const {
    QCOMPARE(logs, expected_logs);
}


void TestYourApp::init()
{
    setLogger();

    window = new MainWindow();

    QVERIFY2(window != nullptr, "Главное окно не создано");
    window->show();
    QVERIFY2(window->isVisible(), "Главное окно не активируется");

    btn_convert_to_km = getChild<QPushButton>(window, "btn_convert_to_km", "QPushButton");
    btn_convert_to_miles = getChild<QPushButton>(window, "btn_convert_to_miles", "QPushButton");

    txt_km_input = getChild<QLineEdit>(window, "txt_km_input", "QLineEdit");
    txt_miles_input = getChild<QLineEdit>(window, "txt_miles_input", "QLineEdit");
}

void TestYourApp::Test1(){
    const std::vector<QString> expected_logs{
        "INFO: Приложение запущено",
        "INFO: Нажата кнопка для конвертирования в мили",
        "DEBUG: Вызвана функция ConvertToMiles, km = 100",
        "DEBUG: Преобразование выполнено: 100 км = 62.1371 миль"
    };

    txt_km_input->setText("100");
    clickWidget(btn_convert_to_miles);
    checkLogs(expected_logs);
}

void TestYourApp::Test2(){
    const std::vector<QString> expected_logs{
        "INFO: Приложение запущено",
        "INFO: Нажата кнопка для конвертирования в мили",
        "DEBUG: Не удалось преобразовать ввод в число: \"*-*\""
    };

    txt_km_input->setText("*-*");
    clickWidget(btn_convert_to_miles);
    checkLogs(expected_logs);
}

void TestYourApp::Test3(){
    const std::vector<QString> expected_logs{
        "INFO: Приложение запущено",
        "INFO: Нажата кнопка для конвертирования в километры",
        "DEBUG: Вызвана функция ConvertToKm, miles = 0",
        "DEBUG: Преобразование выполнено: 0 миль = 0 км"
    };

    txt_miles_input->setText("0");
    clickWidget(btn_convert_to_km);
    checkLogs(expected_logs);
}

void TestYourApp::Test4(){
    const std::vector<QString> expected_logs{
        "INFO: Приложение запущено",
        "INFO: Нажата кнопка для конвертирования в километры",
        "DEBUG: Не удалось преобразовать ввод в число: \"!!!\"",
    };

    txt_miles_input->setText("!!!");
    clickWidget(btn_convert_to_km);
    checkLogs(expected_logs);
}

void TestYourApp::Test5(){
    const std::vector<QString> expected_logs{
        "INFO: Приложение запущено",
        "INFO: Нажата кнопка для конвертирования в мили",
        "DEBUG: Вызвана функция ConvertToMiles, km = 100000",
        "DEBUG: Преобразование выполнено: 100000 км = 62137.1 миль",
        "INFO: Нажата кнопка для конвертирования в километры",
        "DEBUG: Вызвана функция ConvertToKm, miles = 62137",
        "DEBUG: Преобразование выполнено: 62137 миль = 99999.8 км"
    };

    txt_km_input->setText("100000");
    clickWidget(btn_convert_to_miles);
    txt_miles_input->setText("62137");
    clickWidget(btn_convert_to_km);
    checkLogs(expected_logs);
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
