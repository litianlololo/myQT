#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListIterator>
#include <QMessageBox>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDir>
#include <QDialogButtonBox>
#include <QTimer>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    levelGroup=nullptr;     //界面中存在的元素
    deleteBtnList=nullptr;  //被选中待消除的元素
    modelGroup=nullptr;     //模板元素

    timer = new QTimer;
    //定时器时间到
    connect(timer,&QTimer::timeout,this,&MainWindow::timeoutSlot);

    initGame();
}

void MainWindow::initGame()
{

    //两个if都是重新初始化
    if(levelGroup!=nullptr)
    {
        int listSize=levelGroup->buttons().size();
        for(int i=0;i<listSize;i++)
        {
            auto btn=levelGroup->buttons().at(0);
            levelGroup->buttons().at(0)->setParent(NULL);
            levelGroup->removeButton(btn);
        }
    }
    if(deleteBtnList!=nullptr)
    {
        int listSize=deleteBtnList->size();
        for(int i=0;i<listSize;i++)
        {
            deleteBtnList->at(0)->setParent(NULL);
            deleteBtnList->removeAt(0);
        }
    }

    deleteBtnList=new QList<MyButton *>();

    //初始化随机数生成器，设置种子
    init_randomGenerator();

    //添加背景
    QPixmap pix(":/icons/background.png");
    ui->label->setPixmap(pix);

    //加载模版图案
    //创建15个模版按钮
    modelGroup = new QButtonGroup();
    this->load_element();

    // 随机生成关卡中需要的元素
    levelGroup = new QButtonGroup();

    //输出排行榜
    showRanking();

    //重新开始按钮disable
    ui->remake->setDisabled(1);
    ui->beginGameBtn->setDisabled(0);

    Diffculty = 3;
    DeletedNum = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//添加入消除槽，并实时扫描删除槽内元素
void MainWindow::addToDeleteWidget(MyButton *btn)
{
    //按照按钮的文字排序
    if(deleteBtnList->size()==0)
    {
        deleteBtnList->append(btn);
    }
    else{
        for (int i = 0; i < deleteBtnList->size(); i++)
        {
            MyButton *oldBtn = (MyButton *)deleteBtnList->at(i);
            if (oldBtn->myId == btn->myId)
            {
                deleteBtnList->insert(i,btn);
                break;
            }
            else if(i==deleteBtnList->size()-1)
            {
                deleteBtnList->append(btn);
                break;
            }
        }
    }

    //消除连续相同的三个按钮
    removeSame();

    //展示新的消除槽内元素
    int size=deleteBtnList->size();
    for(int i=0;i<size;i++){
        deleteBtnList->at(i)->setParent(ui->deleteWidget);
        deleteBtnList->at(i)->setGeometry(i*33+8,8,30,30);
        deleteBtnList->at(i)->show();
    }
    //gameover
    //槽中元素已满
    if(deleteBtnList->size()==7)
    {
        //新建弹窗
        QDialog  dialog;
        dialog.setWindowTitle(tr("游戏失败"));
        QDialogButtonBox *button = new QDialogButtonBox(&dialog);
        button->addButton( "再试一次", QDialogButtonBox::YesRole);
        button->addButton( "退出游戏", QDialogButtonBox::NoRole);
        //点击再试一次
        connect(button, SIGNAL(accepted()), &dialog, SLOT(accept()));
        //点击退出游戏
        connect(button, SIGNAL(rejected()), &dialog, SLOT(reject()));

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget( button);
        dialog.setLayout(layout);

        QString suffix ;
        if ( dialog.exec() == QDialog::Accepted)
        {
            initGame();
        }
        else
        {
            this->close();
        }
    }
}

//移除槽内3个相同的元素
void MainWindow::removeSame()
{
    int sum=1;
    for (int i = 0; i < deleteBtnList->size(); i++)
    {
        MyButton *oldBtn = (MyButton *)deleteBtnList->at(i);
        for (int j = i+1; j < deleteBtnList->size(); j++)
        {
            MyButton *nextBtn = (MyButton *)deleteBtnList->at(j);
            if(oldBtn->myId==nextBtn->myId){
                sum++;
                continue;
            }
        }
        if(sum==Diffculty)
        {
            //remove
            for(int tmp_int = 0; tmp_int < Diffculty; tmp_int++){
                deleteBtnList->at(i)->setParent(NULL);
                deleteBtnList->removeAt(i);
            }
            break;
        }
        else
        {
            sum=1;
        }
    }
}

//选中元素后，从levelGroup中移除btn，并加入到deleteWidget（调用addToDeleteWidget）
void MainWindow::addToDeleteSlot(QAbstractButton *aBtn)
{
    MyButton *btn=(MyButton *)(aBtn);
    // 首先判断button是否为最外层的元素, 通过判断元素四个顶角是否为最表层元素
    bool ret=isClickable(btn);
    if(!ret)
        return;

    // 从levelGroup中移除btn，并加入到deleteWidget。
    QPoint current_btn_point = btn->pos();
    levelGroup->removeButton(btn);
    btn->setParent(ui->deleteWidget);
    ui->deleteWidget->show();
    addToDeleteWidget((MyButton*)btn);

    DeletedNum++;



    //重新计算是否可以被点击及样式
    setSideBtn(current_btn_point);

    //判断面版上是否有元素
    if (DeletedNum  == AllElementNum)
    {
        //新建弹窗
        QDialog  dialog;
        dialog.setWindowTitle(tr("闯关成功"));

        QDialogButtonBox *button = new QDialogButtonBox(&dialog);
        button->addButton( "再玩一次", QDialogButtonBox::YesRole);
        button->addButton( "退出游戏", QDialogButtonBox::NoRole);

        //更新排行榜
        WRNewData();
        showRanking();

        //点击再试一次
        connect(button, SIGNAL(accepted()), &dialog, SLOT(accept()));
        //点击退出游戏
        connect(button, SIGNAL(rejected()), &dialog, SLOT(reject()));

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget( button);
        dialog.setLayout(layout);

        QString suffix ;
        if ( dialog.exec() == QDialog::Accepted)
        {
            initGame();
        }
        else
        {
            this->close();
        }
    }
}

//根据位置关系 判断是否可点击
bool MainWindow::isClickable(MyButton *btn)
{
    //左下角
    QPoint left_below(btn->pos().rx(),btn->pos().ry() + 28);
    MyButton * tmp_btn = (MyButton *) ui->goodsWidget->childAt(left_below);
    if (tmp_btn != btn)
    {
        return false;
    }
    //左上角
    QPoint left_top(btn->pos().rx(),btn->pos().ry());
    tmp_btn = (MyButton *) ui->goodsWidget->childAt(left_top);
    if (tmp_btn != btn)
    {
        return false;
    }
    //右上角
    QPoint rigth_top(btn->pos().rx() + 28,btn->pos().ry());
    tmp_btn = (MyButton *) ui->goodsWidget->childAt(rigth_top);
    if (tmp_btn != btn)
    {
        return false;
    }
    //右下角
    QPoint rigth_below(btn->pos().rx() + 28,btn->pos().ry() + 28);
    tmp_btn = (MyButton *) ui->goodsWidget->childAt(rigth_below);
    if (tmp_btn != btn)
    {
        return false;
    }
    return true;
}

//根据元素可否点击设置颜色
void MainWindow::setPictureByStatus(MyButton *btn)
{
    //isClickable 返回可否点击 可点击返回true
    bool btnStatus=isClickable(btn);
    if(btnStatus)
    {
        //可点击则选择亮色图片
        QString style=btn->styleSheet();
        btn->setStyleSheet(style+QString("image : url(:/icons/%1.png);").arg(btn->myId));
    }
    else
    {
        //不可点击则选择灰色图片
        QString style=btn->styleSheet();
        btn->setStyleSheet(style+QString("image : url(:/icons/%1gray.png);").arg(btn->myId));
    }
}

//重新计算是否可以被点击及样式
//需要调整图片与isclickable不一样
void MainWindow::setSideBtn(QPoint current_btn_point)
{

    MyButton * tmp_btn = (MyButton *) ui->goodsWidget->childAt(current_btn_point);
    if(tmp_btn)
    {
        setPictureByStatus(tmp_btn);
    }

    QPoint left_below(current_btn_point.rx(),current_btn_point.ry() + 28);
    tmp_btn = (MyButton *) ui->goodsWidget->childAt(left_below);
    if(tmp_btn)
    {
        setPictureByStatus(tmp_btn);
    }

    QPoint rigth_top(current_btn_point.rx() + 28,current_btn_point.ry());
    tmp_btn = (MyButton *) ui->goodsWidget->childAt(rigth_top);
    if(tmp_btn)
    {
        setPictureByStatus(tmp_btn);
    }
    QPoint rigth_below(current_btn_point.rx() + 28,current_btn_point.ry() + 28);
    tmp_btn = (MyButton *) ui->goodsWidget->childAt(rigth_below);
    if(tmp_btn)
    {
        setPictureByStatus(tmp_btn);
    }
}



//点击开始按钮
void MainWindow::on_beginGameBtn_clicked()
{

    choose_Diffculty();

    // 将关卡元素随机分配到空间中
    this->distribution_element(0);
    //根据是否可点击设置添加的元素颜色
    for (int i = 0 ; i < levelGroup->buttons().size(); i ++)
    {
        //根据是否可点击设置颜色
        MyButton *btn=(MyButton *)levelGroup->buttons().at(i);
        setPictureByStatus(btn);
    }
    //禁用开始按钮，解禁重新开始按钮
    ui->beginGameBtn->setDisabled(1);
    ui->remake->setDisabled(0);

    //计数器开始
    timeShow=0;
    ui->timeshow->setNum(timeShow);
    timer->start(TIMEOUT);
}

//载入模板元素
void MainWindow::load_element()
{
    //加载模版图案
    //创建15个模版按钮
    for(int i=0; i<15; i++){
        MyButton *btn = new MyButton(NULL);
        btn->myId=QString::number(i+1);
        btn->setStyleSheet(QString("image : url(:/icons/%1.png);"
                                   "border-top: 1px solid green;"
                                   "border-left: 1px solid green;"
                                   "border-right: 1px solid green;"
                                   "border-bottom: 5px solid green;"
                                   "border-radius:5px;").arg(QString::number(i+1)));


        this->modelGroup->addButton(btn);
    }
}

//将关卡元素随机分配到空间中
//并显示到parent上
void MainWindow::distribution_element(int level)
{
    //将关卡元素随机分配到空间中
    //并显示到parent上。
    if( 0 == level ){   //无意义

        // 读取每个元素的位置
        QString path=QDir::currentPath();
        QFile json_file(":/json/level_3.json");  //选择关卡配置文件。
        json_file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString value = json_file.readAll();
        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&error);
        json_file.close();

        QJsonObject jsonObject=document.object();
        QJsonArray array=jsonObject["node"].toArray();

        int max_element = array.size();
        max_element = max_element  - max_element % 3;

        AllElementNum = max_element;


        //随机生成三个一组的按钮
        for(int i=0; i < max_element / 3; i ++)
        {
            int luck_index = generator.bounded(0,this->modelGroup->buttons().size());
            MyButton *btn=((MyButton *) (this->modelGroup->buttons().at(luck_index)))->copyMyButton();
            MyButton *btn2=((MyButton *) (this->modelGroup->buttons().at(luck_index)))->copyMyButton();
            MyButton *btn3=((MyButton *) (this->modelGroup->buttons().at(luck_index)))->copyMyButton();

            this->levelGroup->addButton(btn);
            this->levelGroup->addButton(btn2);
            this->levelGroup->addButton(btn3);

        }
        //点击后消除该按钮
        connect(levelGroup,SIGNAL(buttonClicked(QAbstractButton *)),this,SLOT(addToDeleteSlot(QAbstractButton *)));

        // 打乱levelGroup的顺序
        QVector<int> *placement_num = new QVector<int>();     //顺序编号
        QVector<int> *placement_state = new QVector<int>();   //levelGroup中每个button放置的位置
        //append 在末尾插入元素
        //从0至max_element编号
        for(int i = 0 ; i < max_element ; i ++){
            placement_num->append(i);
        }
        for(int i = 0; i < max_element ;i ++){
            //随机取得一个编号
            int luck_index = generator.bounded(0,placement_num->size());
            placement_state->append(placement_num->at(luck_index));
            //移除该编号，防止重复
            placement_num->removeAt(luck_index);
        }

        //  循环读取每个位置的图案
        for (int i = 0 ; i < max_element; i ++)
        {
            //将文件中读取的位置信息提取出来
            QList<QString> tmp_list = array.at(i)[QString::number(i)].toString().split(",");
            int tmp_x = tmp_list.at(0).toInt();
            int tmp_y = tmp_list.at(1).toInt();
            //at(i) 相当于数组的[]
            this->levelGroup->buttons().at(placement_state->at(i))->setParent(ui->goodsWidget);
            this->levelGroup->buttons().at(placement_state->at(i))->setGeometry(tmp_x,tmp_y,30,30);
            this->levelGroup->buttons().at(placement_state->at(i))->show();
        }
    }
}

void MainWindow::init_randomGenerator()
{
    quint32 seed = quint32(QDateTime::currentDateTime().toMSecsSinceEpoch());
    this->generator.seed(seed);
}

void MainWindow::on_remake_clicked()
{
    choose_Diffculty();
    timeShow=0;
    ui->timeshow->setNum(timeShow);
    // 将关卡元素随机分配到空间中
    this->distribution_element(0);
    //根据是否可点击设置添加的元素颜色
    for (int i = 0 ; i < levelGroup->buttons().size(); i ++)
    {
        //根据是否可点击设置颜色
        MyButton *btn=(MyButton *)levelGroup->buttons().at(i);
        setPictureByStatus(btn);
    }

    //清空消除槽内容
    if(deleteBtnList!=nullptr)
    {
        int listSize=deleteBtnList->size();
        for(int i=0;i<listSize;i++)
        {
            deleteBtnList->at(0)->setParent(NULL);
            deleteBtnList->removeAt(0);
        }
    }

    DeletedNum=0;
}

void MainWindow::choose_Diffculty()
{
    //新建弹窗
    QDialog  dialog;
    dialog.setWindowTitle(tr("选择难度"));
    QDialogButtonBox *button_1 = new QDialogButtonBox(&dialog);
    QDialogButtonBox *button_2 = new QDialogButtonBox(&dialog);

    button_1->addButton( "easy", QDialogButtonBox::YesRole);
    button_2->addButton( "hard", QDialogButtonBox::NoRole);
    //easy
    connect(button_1, SIGNAL(accepted()), &dialog, SLOT(accept()));
    //hard
    connect(button_2, SIGNAL(rejected()), &dialog, SLOT(reject()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget( button_1);
    layout->addWidget( button_2);
    dialog.setLayout(layout);

    QString suffix ;
    if ( dialog.exec() == QDialog::Accepted)
    {
        Diffculty = 1;
    }
    else
    {
       Diffculty = 4;
    }
}


void MainWindow::timeoutSlot()
{
    timeShow+=1;
    ui->timeshow->setNum(timeShow);
}

void MainWindow::WRNewData()
{
    //读取所有旧成绩
    QSettings config(":/Data.ini",QSettings::IniFormat);
    if(config.value("Data/num").toString()=="")
        config.setValue("Data/num",0);
    DataNum=config.value("Data/num").toInt();

    int* TimeData;    //从0开始存储
    TimeData=new int[DataNum+2];
    for(int i=0; i<DataNum;i++)
        TimeData[i]=config.value("/Data/"+QString::number(i)).toInt();
    ++DataNum;
    qDebug()<<DataNum<<" "<<timeShow;
    TimeData[DataNum-1]=timeShow;
     qDebug()<<"TimeData[DataNum]="<<TimeData[DataNum];
    //进行升序排序（快速排序）
    QuickSort(TimeData,DataNum);
    qDebug()<<"\n"<<"1:"<<TimeData[0]<<"2:"<<TimeData[1]<<"3:"<<TimeData[2];
    //写入新成绩
    //更新数据量
    config.setValue("/Data/num",DataNum);
    for(int i=0;i<DataNum;i++)
        config.setValue("/Data/"+QString::number(i),QString::number(TimeData[i]));
    delete [] TimeData;

}

void MainWindow::showRanking()
{
    QSettings config(":/Data.ini",QSettings::IniFormat);
    QString RankingShow="排行榜：\n";
    DataNum=config.value("/Data/num").toInt();
    int maxShow=DataNum;
    if(DataNum>=6)
        maxShow=6;
    for(int i=0; i<maxShow;i++)
        RankingShow+=QString::number(i+1)+"\t"+
                        config.value("/Data/"+QString::number(i)).toString()+"\n";
    ui->RankingLabel->setText(RankingShow);
}

//快速排序
template<typename T>
void Swap(T& x, T& y)
{
    T t;
    t = x;
    x = y;
    y = t;
    return;
}
int part(int arr[], int low, int high)
{
    int i = low, j = high, pivot = arr[low]; //基准元素
    while (i < j)
    {
        while (i < j && ( arr[j] > pivot)) //从右向左开始找一个 小于等于 pivot的数值
        {
            j--;
        }
        if (i < j)
        {
            Swap(arr[i++], arr[j]);  //r[i]和r[j]交换后 i 向右移动一位
        }
        while (i < j && (arr[i] <= pivot)) //从左向右开始找一个 大于 pivot的数值
        {
            i++;
        }
        if (i < j)
        {
            Swap(arr[i], arr[j--]);  //r[i]和r[j]交换后 i 向左移动一位
        }
    }
    return i;  //返回最终划分完成后基准元素所在的位置
}
void _QuickSort(int arr[], int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = part(arr, low, high);
        _QuickSort(arr, low, mid - 1);
        _QuickSort(arr, mid + 1, high);
    }
}
void MainWindow::QuickSort(int arr[], int num)
{
    _QuickSort(arr, 0, num-1);
    return;
}
