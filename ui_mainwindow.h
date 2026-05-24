/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *city;
    QLabel *label;
    QLabel *label_2;
    QPushButton *result;
    QLabel *tempr;
    QLabel *descrip;
    QLabel *today;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(618, 351);
        QFont font;
        font.setUnderline(false);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-image: url(:/images/fon.jpeg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}\n"
"\n"
"QPushButton, QLineEdit, QLabel {\n"
"    color: #FFD700\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        city = new QLineEdit(centralwidget);
        city->setObjectName("city");
        city->setGeometry(QRect(30, 130, 221, 28));
        city->setStyleSheet(QString::fromUtf8("color: black"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 161, 51));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 60, 271, 21));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        label_2->setFont(font2);
        label_2->setStyleSheet(QString::fromUtf8("color: white"));
        result = new QPushButton(centralwidget);
        result->setObjectName("result");
        result->setGeometry(QRect(30, 180, 131, 29));
        result->setFont(font1);
        result->setStyleSheet(QString::fromUtf8("color: black"));
        tempr = new QLabel(centralwidget);
        tempr->setObjectName("tempr");
        tempr->setGeometry(QRect(360, 250, 251, 31));
        QFont font3;
        font3.setBold(true);
        font3.setUnderline(true);
        tempr->setFont(font3);
        tempr->setStyleSheet(QString::fromUtf8("color: white"));
        descrip = new QLabel(centralwidget);
        descrip->setObjectName("descrip");
        descrip->setGeometry(QRect(360, 220, 251, 31));
        descrip->setFont(font3);
        descrip->setStyleSheet(QString::fromUtf8("color: white"));
        today = new QLabel(centralwidget);
        today->setObjectName("today");
        today->setGeometry(QRect(160, 220, 191, 31));
        QFont font4;
        font4.setBold(true);
        font4.setItalic(false);
        font4.setUnderline(true);
        today->setFont(font4);
        today->setStyleSheet(QString::fromUtf8(""));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 90, 271, 21));
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("color: white"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 618, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\263\320\275\320\276\320\267 \320\277\320\276\320\263\320\276\320\264\320\270", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\321\226\321\202\321\214 \320\274\321\226\321\201\321\202\320\276, \320\264\320\273\321\217 \321\217\320\272\320\276\320\263\320\276 \321\205\320\276\321\207\320\265\321\202\320\265", nullptr));
        result->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\263\320\275\320\276\320\267", nullptr));
        tempr->setText(QString());
        descrip->setText(QString());
        today->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\276\321\202\321\200\320\270\320\274\320\260\321\202\320\270 \320\277\321\200\320\276\320\263\320\275\320\276\320\267 \320\277\320\276\320\263\320\276\320\264\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
