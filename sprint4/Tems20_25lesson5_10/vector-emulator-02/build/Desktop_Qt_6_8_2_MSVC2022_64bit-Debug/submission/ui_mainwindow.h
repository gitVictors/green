/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_3;
    QLineEdit *txt_size;
    QGridLayout *gridLayout_2;
    QPushButton *Button_Edit;
    QLineEdit *txt_elem_content;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *pop_back;
    QPushButton *push_back;
    QPushButton *erase;
    QPushButton *insert;
    QPushButton *clear;
    QLabel *label_4;
    QPushButton *minus_minus;
    QPushButton *plus_plus;
    QPushButton *begin;
    QPushButton *end;
    QLabel *label_2;
    QPushButton *days;
    QPushButton *month;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QListWidget *list_widget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(567, 606);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(320, 21, 232, 571));
        gridLayout_3 = new QGridLayout(layoutWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        txt_size = new QLineEdit(layoutWidget);
        txt_size->setObjectName("txt_size");

        gridLayout_3->addWidget(txt_size, 2, 1, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        Button_Edit = new QPushButton(layoutWidget);
        Button_Edit->setObjectName("Button_Edit");

        gridLayout_2->addWidget(Button_Edit, 0, 1, 1, 1);

        txt_elem_content = new QLineEdit(layoutWidget);
        txt_elem_content->setObjectName("txt_elem_content");

        gridLayout_2->addWidget(txt_elem_content, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pop_back = new QPushButton(layoutWidget);
        pop_back->setObjectName("pop_back");

        gridLayout->addWidget(pop_back, 1, 0, 1, 1);

        push_back = new QPushButton(layoutWidget);
        push_back->setObjectName("push_back");

        gridLayout->addWidget(push_back, 1, 1, 1, 1);

        erase = new QPushButton(layoutWidget);
        erase->setObjectName("erase");

        gridLayout->addWidget(erase, 2, 0, 1, 1);

        insert = new QPushButton(layoutWidget);
        insert->setObjectName("insert");

        gridLayout->addWidget(insert, 2, 1, 1, 1);

        clear = new QPushButton(layoutWidget);
        clear->setObjectName("clear");

        gridLayout->addWidget(clear, 3, 0, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        minus_minus = new QPushButton(layoutWidget);
        minus_minus->setObjectName("minus_minus");

        gridLayout->addWidget(minus_minus, 5, 0, 1, 1);

        plus_plus = new QPushButton(layoutWidget);
        plus_plus->setObjectName("plus_plus");

        gridLayout->addWidget(plus_plus, 5, 1, 1, 1);

        begin = new QPushButton(layoutWidget);
        begin->setObjectName("begin");

        gridLayout->addWidget(begin, 6, 0, 1, 1);

        end = new QPushButton(layoutWidget);
        end->setObjectName("end");

        gridLayout->addWidget(end, 6, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 7, 0, 1, 1);

        days = new QPushButton(layoutWidget);
        days->setObjectName("days");

        gridLayout->addWidget(days, 8, 0, 1, 1);

        month = new QPushButton(layoutWidget);
        month->setObjectName("month");

        gridLayout->addWidget(month, 8, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 2);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 1, 0, 1, 2);

        list_widget = new QListWidget(centralwidget);
        list_widget->setObjectName("list_widget");
        list_widget->setGeometry(QRect(20, 20, 281, 571));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "std::vector demo", nullptr));
        Button_Edit->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\234\320\265\321\202\320\276\320\264\321\213", nullptr));
        pop_back->setText(QCoreApplication::translate("MainWindow", "pop_back", nullptr));
        push_back->setText(QCoreApplication::translate("MainWindow", "push_back", nullptr));
        erase->setText(QCoreApplication::translate("MainWindow", "erase", nullptr));
        insert->setText(QCoreApplication::translate("MainWindow", "insert", nullptr));
        clear->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\230\321\202\320\265\321\200\320\260\321\202\320\276\321\200", nullptr));
        minus_minus->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
        plus_plus->setText(QCoreApplication::translate("MainWindow", "++", nullptr));
        begin->setText(QCoreApplication::translate("MainWindow", "begin", nullptr));
        end->setText(QCoreApplication::translate("MainWindow", "end", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\320\276\320\273\320\276\320\262\320\272\320\270", nullptr));
        days->setText(QCoreApplication::translate("MainWindow", "= \320\264\320\275\320\270 \320\275\320\265\320\264\320\265\320\273\320\270", nullptr));
        month->setText(QCoreApplication::translate("MainWindow", "= \320\274\320\265\321\201\321\217\321\206\321\213", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "size():", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
