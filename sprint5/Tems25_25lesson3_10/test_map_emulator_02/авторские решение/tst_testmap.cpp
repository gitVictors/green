#include <QCoreApplication>
#include <QtTest>

#include <mainwindow.h>
#include "ui_mainwindow.h"

class TestMap : public QObject
{
    Q_OBJECT

public:
    TestMap();
    ~TestMap();

private slots:
    void init();

    void TestSizeInit();
    void TestSizeWithBooks();
    void TestSizeWithAddedItem();

    void TestMainWidgetInit();
    void TestMainWidgetWithBooks();
    void TestMainWidgetWithAddedItem();

    void TestEnableButtonsInit();
    void TestEnableButtonsWithBooks();
    void TestEnableButtonsWithAddedItem();

private:
    MainWindow map;
};

TestMap::TestMap() {}

TestMap::~TestMap() {}

void TestMap::init() {
    QTest::mouseClick(map.ui->btn_clear, Qt::LeftButton);
}

void TestMap::TestSizeInit() {
    QVERIFY2(map.ui->txt_size->text() == "0", "Размер словаря не равен 0");
}

void TestMap::TestSizeWithBooks() {
    QTest::mouseClick(map.ui->btn_books, Qt::LeftButton);
    QVERIFY2(map.ui->txt_size->text() == "6", "Размер словаря не равен 7");
}

void TestMap::TestSizeWithAddedItem() {
    QTest::keyClicks(map.ui->txt_elem_key, "E. Yudkowsky");
    QTest::keyClicks(map.ui->txt_elem_value, "Methods of Rationality");
    QTest::mouseClick(map.ui->btn_set_by_key, Qt::LeftButton);

    QVERIFY2(map.ui->txt_size->text() == "1", "Размер словаря не равен 1");
}

void TestMap::TestMainWidgetInit() {
    QVERIFY2(map.ui->list_widget->count() > 0, "Список не должен быть пустым");
    QVERIFY2(map.ui->list_widget->item(0)->text() == "end", "В списке должен быть элемент end");
}

void TestMap::TestMainWidgetWithBooks() {
    QTest::mouseClick(map.ui->btn_books, Qt::LeftButton);

    int true_num = 7;
    std::vector true_items {
                           "А. и Б. Стругацкие: Жук в муравейнике",
                           "Д. Адамс: В основном безвредна",
                           "Р. Брэдбери: Лёд и пламя",
                           "Т. Пратчетт: Плоский мир",
                           "Ф. Дик: Солнечная лотерея",
                           "Ф. Кафка: Превращение",
                           "end"};

    QVERIFY2(map.ui->list_widget->count() == true_num, "Список не должен быть пустым");
    for (int i = 0; i < true_num; i++) {
        QVERIFY2(map.ui->list_widget->item(i)->text() == true_items[i], "Неверный элемент в списке");
    }
}

void TestMap::TestMainWidgetWithAddedItem() {
    QTest::keyClicks(map.ui->txt_elem_key, "E. Yudkowsky");
    QTest::keyClicks(map.ui->txt_elem_value, "Methods of Rationality");
    QTest::mouseClick(map.ui->btn_set_by_key, Qt::LeftButton);

    QVERIFY2(map.ui->list_widget->count() == 2, "Список не должен быть пустым");
    QVERIFY2(map.ui->list_widget->item(0)->text() == "E. Yudkowsky: Methods of Rationality", "Неверный элемент в списке");
    QVERIFY2(map.ui->list_widget->item(1)->text() == "end", "Неверный элемент в списке");
}

void TestMap::TestEnableButtonsInit() {
    QVERIFY2(map.ui->btn_set_by_key->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(!map.ui->btn_erase->isEnabled(), "Кнопка не заблокирована");
    QVERIFY2(map.ui->btn_clear->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(map.ui->btn_find->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(!map.ui->btn_dec_iterator->isEnabled(), "Кнопка не заблокирована");
    QVERIFY2(!map.ui->btn_inc_iterator->isEnabled(), "Кнопка не заблокирована");
    QVERIFY2(map.ui->btn_begin->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(map.ui->btn_end->isEnabled(), "Кнопка заблокирована");
}

void TestMap::TestEnableButtonsWithBooks() {
    QTest::mouseClick(map.ui->btn_books, Qt::LeftButton);

    QVERIFY2(map.ui->btn_set_by_key->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(map.ui->btn_erase->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(map.ui->btn_clear->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(map.ui->btn_find->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(!map.ui->btn_dec_iterator->isEnabled(), "Кнопка не заблокирована");
    QVERIFY2(map.ui->btn_inc_iterator->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(map.ui->btn_begin->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(map.ui->btn_end->isEnabled(), "Кнопка заблокирована");
}

void TestMap::TestEnableButtonsWithAddedItem() {
    QTest::keyClicks(map.ui->txt_elem_key, "E. Yudkowsky");
    QTest::keyClicks(map.ui->txt_elem_value, "Methods of Rationality");
    QTest::mouseClick(map.ui->btn_set_by_key, Qt::LeftButton);

    QVERIFY2(map.ui->btn_set_by_key->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(!map.ui->btn_erase->isEnabled(), "Кнопка не заблокирована");
    QVERIFY2(map.ui->btn_clear->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(map.ui->btn_find->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(map.ui->btn_dec_iterator->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(!map.ui->btn_inc_iterator->isEnabled(), "Кнопка не заблокирована");
    QVERIFY2(map.ui->btn_begin->isEnabled(), "Кнопка заблокирована");
    QVERIFY2(map.ui->btn_end->isEnabled(), "Кнопка заблокирована");
}

QTEST_MAIN(TestMap)

#include "tst_testmap.moc"