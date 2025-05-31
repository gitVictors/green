#include <QtTest>
#include <QSignalSpy>
#include <QLineEdit>
#include <QPushButton>
#include "../../test_map_emulator/submission/mainwindow.h"

class TestMap : public QObject
{
    Q_OBJECT

public:
    TestMap();
    ~TestMap();

private slots:
    void init();

    // Первая группа тестов (размер словаря)
    void TestSizeInit();
    void TestSizeWithBooks();
    void TestSizeWithAddedItem();

    // Вторая группа тестов (содержимое виджета)
    void TestMainWidgetInit();
    void TestMainWidgetWithBooks();
    void TestMainWidgetWithAddedItem();

    // Третья группа тестов (состояние кнопок)
    void TestEnableButtonsInit();
    void TestEnableButtonsWithBooks();
    void TestEnableButtonsWithAddedItem();

private:
    MainWindow* m_mainWindow;
};

TestMap::TestMap() {}
TestMap::~TestMap() {}

void TestMap::init()
{
    if (m_mainWindow) {
        delete m_mainWindow;
    }
    m_mainWindow = new MainWindow();
    m_mainWindow->show();
}

// Первая группа тестов - проверка размера словаря
void TestMap::TestSizeInit()
{
    QCOMPARE(m_mainWindow->findChild<QLineEdit*>("txt_size")->text(), "0");
}

void TestMap::TestSizeWithBooks()
{
    QTest::mouseClick(m_mainWindow->findChild<QPushButton*>("btn_books"), Qt::LeftButton);
    QCOMPARE(m_mainWindow->findChild<QLineEdit*>("txt_size")->text(),
             QString::number(Model::authors_and_books.size()));
}

void TestMap::TestSizeWithAddedItem()
{
    QLineEdit* keyEdit = m_mainWindow->findChild<QLineEdit*>("txt_elem_key");
    QLineEdit* valueEdit = m_mainWindow->findChild<QLineEdit*>("txt_elem_value");

    keyEdit->setText("TestKey");
    valueEdit->setText("TestValue");
    QTest::mouseClick(m_mainWindow->findChild<QPushButton*>("btn_set_by_key"), Qt::LeftButton);

    QCOMPARE(m_mainWindow->findChild<QLineEdit*>("txt_size")->text(), "1");
}

// Вторая группа тестов - проверка содержимого виджета
void TestMap::TestMainWidgetInit()
{
    QListWidget* listWidget = m_mainWindow->findChild<QListWidget*>("list_widget");
    QCOMPARE(listWidget->count(), 1); // Только "end"
    QCOMPARE(listWidget->item(0)->text(), "end");
}

void TestMap::TestMainWidgetWithBooks()
{
    QTest::mouseClick(m_mainWindow->findChild<QPushButton*>("btn_books"), Qt::LeftButton);
    QListWidget* listWidget = m_mainWindow->findChild<QListWidget*>("list_widget");

    QCOMPARE(listWidget->count(), Model::authors_and_books.size() + 1); // +1 для "end"

    // Проверяем первый и последний элементы
    bool foundFirst = false;
    bool foundLast = false;

    for (int i = 0; i < listWidget->count() - 1; ++i) {
        QString itemText = listWidget->item(i)->text();
        if (itemText.startsWith("Т. Пратчетт:")) foundFirst = true;
        if (itemText.startsWith("Ф. Кафка:")) foundLast = true;
    }

    QVERIFY(foundFirst);
    QVERIFY(foundLast);
    QCOMPARE(listWidget->item(listWidget->count()-1)->text(), "end");
}

void TestMap::TestMainWidgetWithAddedItem()
{
    QLineEdit* keyEdit = m_mainWindow->findChild<QLineEdit*>("txt_elem_key");
    QLineEdit* valueEdit = m_mainWindow->findChild<QLineEdit*>("txt_elem_value");

    keyEdit->setText("TestKey");
    valueEdit->setText("TestValue");
    QTest::mouseClick(m_mainWindow->findChild<QPushButton*>("btn_set_by_key"), Qt::LeftButton);

    QListWidget* listWidget = m_mainWindow->findChild<QListWidget*>("list_widget");
    QCOMPARE(listWidget->count(), 2); // 1 элемент + "end"
    QVERIFY(listWidget->item(0)->text().startsWith("TestKey: TestValue"));
    QCOMPARE(listWidget->item(1)->text(), "end");
}

// Третья группа тестов - проверка состояния кнопок
void TestMap::TestEnableButtonsInit()
{
    QVERIFY(!m_mainWindow->findChild<QPushButton*>("btn_erase")->isEnabled());
    QVERIFY(!m_mainWindow->findChild<QPushButton*>("btn_dec_iterator")->isEnabled());
    QVERIFY(!m_mainWindow->findChild<QPushButton*>("btn_inc_iterator")->isEnabled());
}

void TestMap::TestEnableButtonsWithBooks()
{
    QTest::mouseClick(m_mainWindow->findChild<QPushButton*>("btn_books"), Qt::LeftButton);

    QVERIFY(m_mainWindow->findChild<QPushButton*>("btn_erase")->isEnabled());
    QVERIFY(!m_mainWindow->findChild<QPushButton*>("btn_dec_iterator")->isEnabled());
    QVERIFY(m_mainWindow->findChild<QPushButton*>("btn_inc_iterator")->isEnabled());
}

void TestMap::TestEnableButtonsWithAddedItem()
{
    QLineEdit* keyEdit = m_mainWindow->findChild<QLineEdit*>("txt_elem_key");
    QLineEdit* valueEdit = m_mainWindow->findChild<QLineEdit*>("txt_elem_value");

    keyEdit->setText("TestKey");
    valueEdit->setText("TestValue");
    QTest::mouseClick(m_mainWindow->findChild<QPushButton*>("btn_set_by_key"), Qt::LeftButton);

 //   QVERIFY(m_mainWindow->findChild<QPushButton*>("btn_erase")->isEnabled());
  //  QVERIFY(!m_mainWindow->findChild<QPushButton*>("btn_dec_iterator")->isEnabled());
  //  QVERIFY(m_mainWindow->findChild<QPushButton*>("btn_inc_iterator")->isEnabled());
}

QTEST_MAIN(TestMap)
//#include "tst_testmap.moc"
#include "tst_testmapemulator.moc"
