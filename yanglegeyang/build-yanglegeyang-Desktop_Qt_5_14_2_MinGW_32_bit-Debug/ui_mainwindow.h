/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QPushButton *beginGameBtn;
    QListWidget *deleteWidget;
    QTableWidget *goodsWidget;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(780, 472);
        beginGameBtn = new QPushButton(MainWindow);
        beginGameBtn->setObjectName(QString::fromUtf8("beginGameBtn"));
        beginGameBtn->setGeometry(QRect(40, 80, 111, 71));
        beginGameBtn->setIconSize(QSize(32, 32));
        deleteWidget = new QListWidget(MainWindow);
        deleteWidget->setObjectName(QString::fromUtf8("deleteWidget"));
        deleteWidget->setGeometry(QRect(260, 390, 244, 46));
        goodsWidget = new QTableWidget(MainWindow);
        goodsWidget->setObjectName(QString::fromUtf8("goodsWidget"));
        goodsWidget->setGeometry(QRect(241, 20, 280, 280));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Widget", nullptr));
        beginGameBtn->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
