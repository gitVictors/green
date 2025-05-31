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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_div;
    QPushButton *pushButton_four;
    QPushButton *pushButton_seven;
    QPushButton *pushButton_nine;
    QPushButton *pushButton_mult;
    QPushButton *pushButton_result;
    QPushButton *pushButton_two;
    QPushButton *pushButton_five;
    QPushButton *pushButton_sub;
    QPushButton *pushButton_MemClean;
    QPushButton *pushButton_zero;
    QPushButton *pushButton_one;
    QPushButton *pushButton_clean;
    QPushButton *pushButton_add;
    QHBoxLayout *horizontalLayout;
    QLabel *l_memory;
    QLabel *l_result;
    QPushButton *pushButton_power;
    QPushButton *pushButton_negative;
    QPushButton *pushButton_three;
    QLabel *l_formula;
    QPushButton *pushButton_dot;
    QPushButton *pushButton_MemRead;
    QPushButton *pushButton_MemSave;
    QPushButton *pushButton_eight;
    QPushButton *pushButton_six;
    QPushButton *pushButton_delete;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(339, 376);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        MainWindow->setFont(font);
        MainWindow->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        pushButton_div = new QPushButton(centralwidget);
        pushButton_div->setObjectName("pushButton_div");

        gridLayout->addWidget(pushButton_div, 3, 3, 1, 1);

        pushButton_four = new QPushButton(centralwidget);
        pushButton_four->setObjectName("pushButton_four");

        gridLayout->addWidget(pushButton_four, 5, 0, 1, 1);

        pushButton_seven = new QPushButton(centralwidget);
        pushButton_seven->setObjectName("pushButton_seven");

        gridLayout->addWidget(pushButton_seven, 4, 0, 1, 1);

        pushButton_nine = new QPushButton(centralwidget);
        pushButton_nine->setObjectName("pushButton_nine");

        gridLayout->addWidget(pushButton_nine, 4, 2, 1, 1);

        pushButton_mult = new QPushButton(centralwidget);
        pushButton_mult->setObjectName("pushButton_mult");

        gridLayout->addWidget(pushButton_mult, 4, 3, 1, 1);

        pushButton_result = new QPushButton(centralwidget);
        pushButton_result->setObjectName("pushButton_result");

        gridLayout->addWidget(pushButton_result, 7, 3, 1, 1);

        pushButton_two = new QPushButton(centralwidget);
        pushButton_two->setObjectName("pushButton_two");

        gridLayout->addWidget(pushButton_two, 6, 1, 1, 1);

        pushButton_five = new QPushButton(centralwidget);
        pushButton_five->setObjectName("pushButton_five");

        gridLayout->addWidget(pushButton_five, 5, 1, 1, 1);

        pushButton_sub = new QPushButton(centralwidget);
        pushButton_sub->setObjectName("pushButton_sub");

        gridLayout->addWidget(pushButton_sub, 5, 3, 1, 1);

        pushButton_MemClean = new QPushButton(centralwidget);
        pushButton_MemClean->setObjectName("pushButton_MemClean");

        gridLayout->addWidget(pushButton_MemClean, 2, 0, 1, 1);

        pushButton_zero = new QPushButton(centralwidget);
        pushButton_zero->setObjectName("pushButton_zero");

        gridLayout->addWidget(pushButton_zero, 7, 1, 1, 1);

        pushButton_one = new QPushButton(centralwidget);
        pushButton_one->setObjectName("pushButton_one");

        gridLayout->addWidget(pushButton_one, 6, 0, 1, 1);

        pushButton_clean = new QPushButton(centralwidget);
        pushButton_clean->setObjectName("pushButton_clean");

        gridLayout->addWidget(pushButton_clean, 3, 0, 1, 2);

        pushButton_add = new QPushButton(centralwidget);
        pushButton_add->setObjectName("pushButton_add");

        gridLayout->addWidget(pushButton_add, 6, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        l_memory = new QLabel(centralwidget);
        l_memory->setObjectName("l_memory");

        horizontalLayout->addWidget(l_memory);

        l_result = new QLabel(centralwidget);
        l_result->setObjectName("l_result");
        l_result->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout->addWidget(l_result);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 4);

        pushButton_power = new QPushButton(centralwidget);
        pushButton_power->setObjectName("pushButton_power");

        gridLayout->addWidget(pushButton_power, 2, 3, 1, 1);

        pushButton_negative = new QPushButton(centralwidget);
        pushButton_negative->setObjectName("pushButton_negative");

        gridLayout->addWidget(pushButton_negative, 3, 2, 1, 1);

        pushButton_three = new QPushButton(centralwidget);
        pushButton_three->setObjectName("pushButton_three");

        gridLayout->addWidget(pushButton_three, 6, 2, 1, 1);

        l_formula = new QLabel(centralwidget);
        l_formula->setObjectName("l_formula");
        l_formula->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(l_formula, 0, 3, 1, 1);

        pushButton_dot = new QPushButton(centralwidget);
        pushButton_dot->setObjectName("pushButton_dot");

        gridLayout->addWidget(pushButton_dot, 7, 0, 1, 1);

        pushButton_MemRead = new QPushButton(centralwidget);
        pushButton_MemRead->setObjectName("pushButton_MemRead");

        gridLayout->addWidget(pushButton_MemRead, 2, 1, 1, 1);

        pushButton_MemSave = new QPushButton(centralwidget);
        pushButton_MemSave->setObjectName("pushButton_MemSave");

        gridLayout->addWidget(pushButton_MemSave, 2, 2, 1, 1);

        pushButton_eight = new QPushButton(centralwidget);
        pushButton_eight->setObjectName("pushButton_eight");

        gridLayout->addWidget(pushButton_eight, 4, 1, 1, 1);

        pushButton_six = new QPushButton(centralwidget);
        pushButton_six->setObjectName("pushButton_six");

        gridLayout->addWidget(pushButton_six, 5, 2, 1, 1);

        pushButton_delete = new QPushButton(centralwidget);
        pushButton_delete->setObjectName("pushButton_delete");

        gridLayout->addWidget(pushButton_delete, 7, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\232\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200", nullptr));
        pushButton_div->setText(QCoreApplication::translate("MainWindow", "\303\267", nullptr));
        pushButton_four->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        pushButton_seven->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        pushButton_nine->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        pushButton_mult->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
        pushButton_result->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        pushButton_two->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        pushButton_five->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        pushButton_sub->setText(QCoreApplication::translate("MainWindow", "\342\210\222", nullptr));
        pushButton_MemClean->setText(QCoreApplication::translate("MainWindow", "MC", nullptr));
        pushButton_zero->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushButton_one->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        pushButton_clean->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        pushButton_add->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        l_memory->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        l_result->setText(QCoreApplication::translate("MainWindow", "123", nullptr));
        pushButton_power->setText(QCoreApplication::translate("MainWindow", "x\312\270", nullptr));
        pushButton_negative->setText(QCoreApplication::translate("MainWindow", "\302\261", nullptr));
        pushButton_three->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        l_formula->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_dot->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        pushButton_MemRead->setText(QCoreApplication::translate("MainWindow", "MR", nullptr));
        pushButton_MemSave->setText(QCoreApplication::translate("MainWindow", "MS", nullptr));
        pushButton_eight->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        pushButton_six->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("MainWindow", "\342\214\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
