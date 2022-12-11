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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QPushButton *beginGameBtn;
    QListWidget *deleteWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *goodsWidget;
    QLabel *label;
    QToolButton *remake;

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
        deleteWidget->setGeometry(QRect(250, 370, 244, 46));
        horizontalLayoutWidget = new QWidget(MainWindow);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(230, 60, 281, 281));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        goodsWidget = new QTableWidget(horizontalLayoutWidget);
        goodsWidget->setObjectName(QString::fromUtf8("goodsWidget"));
        goodsWidget->setAutoFillBackground(true);
        goodsWidget->horizontalHeader()->setVisible(false);
        goodsWidget->verticalHeader()->setVisible(false);

        horizontalLayout->addWidget(goodsWidget);

        label = new QLabel(MainWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(-10, 0, 781, 471));
        label->setScaledContents(true);
        remake = new QToolButton(MainWindow);
        remake->setObjectName(QString::fromUtf8("remake"));
        remake->setGeometry(QRect(40, 180, 111, 71));
        label->raise();
        beginGameBtn->raise();
        deleteWidget->raise();
        horizontalLayoutWidget->raise();
        remake->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Widget", nullptr));
        beginGameBtn->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        label->setText(QString());
        remake->setText(QCoreApplication::translate("MainWindow", "\351\207\215\346\226\260\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
