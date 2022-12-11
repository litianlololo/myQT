#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mybutton.h"
#include <QButtonGroup>
#include <qrandom.h>
#include <QDateTime>
#include <QImage>
#include<QtWidgets>
#include<QSettings>
#include <QString>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define TIMEOUT 1 *1000

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int Diffculty;//选择难度，easy：三个相同可消除，hard：四个相同可消除
    int DeletedNum;//已经进入消除槽的元素数量
    int AllElementNum;//所有元素数量

    QTimer *timer;
    int timeShow=0;
    void choose_Diffculty();

public:
    MainWindow(QWidget *parent = nullptr);

    QButtonGroup *modelGroup;          // 用于存放模板元素，
    QButtonGroup *levelGroup;          // 用于存放关卡中涉及的元素
    QList<MyButton*> *deleteBtnList;   // 用于存放消除区的元素
    QRandomGenerator generator;        // 随机数产生器

    int DataNum=0;
    void initGame();
    //添加到下面消除窗口
    void addToDeleteWidget(MyButton *btn);

    // 销毁三个相同物品
    void removeSame();

    // 加载模版图案
    void load_element();

    // 将关卡元素随机分配到空间中
    void distribution_element(int level = 0); // level代表关卡数量

    //产生随机数
    void init_randomGenerator();

    //判断是否可以点击
    bool isClickable(MyButton *btn);
;
    //判断按钮状态并设置图片

    void setPictureByStatus(MyButton *btn);
    //设置邻近的按钮的状态

    void setSideBtn(QPoint current_btn_point);

    //展示排行榜
    void showRanking();

    //写入新成绩
    void WRNewData();
    //快速排序
    void QuickSort(int *arr,int num);

    ~MainWindow();
public slots:
    //添加到消除栏槽函数
    void addToDeleteSlot(QAbstractButton *);
    void on_beginGameBtn_clicked();

private slots:
    void on_remake_clicked();

    void timeoutSlot();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
