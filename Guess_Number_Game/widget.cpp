#include "widget.h"
#include "ui_widget.h"
#include <QTime>
#include <QTimerEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QTextCursor>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化参数
    /*
     * Clears the contents of the string and makes it null.
     * 清除String的内容，设置它内容为null
    */
    inputNumber.clear();
    randNumber.clear();
    startTimerId = 0;
    winTimerId = 0;
    overTimerId = 0;
    maxNumber = 10000;
    minNumber = 0;

    //设置初始页面
    ui->stackedWidget->setCurrentWidget(ui->page);

    //初始化失败动画和成功动画。
    failMovie = new QMovie(QString("../fail.gif"));
    ui->movie_fail->setMovie(failMovie);
    //设置自适应标签大小
    ui->movie_fail->setScaledContents(true);
    winMovie = new QMovie(QString("../win.gif"));
    ui->movie_win->setMovie(winMovie);
    //设置自适应标签大小
    ui->movie_win->setScaledContents(true);

    //设置textedit为只读
    ui->textEdit->setReadOnly(true);
    //设置字体
    ui->textEdit->setFont(QFont("华文隶书", 10));
    //和Android的hint功能相似，都是显示提示信息
    ui->textEdit->setPlaceholderText("请输入");

    /*
     * 0~9数字按钮被按下所需要做的事情：
     *      1.显示所按下的数字，并且显示的首位不为0
     *      2.每次显示以追加的方式
    */
    connect(ui->pushButton_0, &QPushButton::clicked, this, &Widget::deal_Number);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &Widget::deal_Number);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Widget::deal_Number);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Widget::deal_Number);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &Widget::deal_Number);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &Widget::deal_Number);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &Widget::deal_Number);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &Widget::deal_Number);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &Widget::deal_Number);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &Widget::deal_Number);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonStart_clicked()
{
    /*
     * 点击开始按钮时需要完成以下几件事：
     *  1.切换页面
     *  2.获取combobox的内容
     *  3.开启计时器
     *  4.产生随机数
     *  5.设置进度条的初始值
     *  6.清除textedit的内容
    */

    //切换页面
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    //获取combobox内容，以int的形式保存在time中
    time = ui->comboBox->currentText().toInt();

    //产生随机数
    //以0时0分0秒到现在的秒数为种子
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    //调用全局的qrand()函数生成随机数，对10000区余，保证位于10000的范围内
    int number;
    while( 999 > ( number = qrand()%10000) )
        ;
    randNumber = QString::number(number);
    qDebug() << "Rand Nuber is: "<<randNumber.toInt();

    //设置进度条的最小值
    ui->progressBar->setMinimum(0);
    //设置进度条最大值
    ui->progressBar->setMaximum(time);
    //设置初始值最大值，因为是倒计时
    ui->progressBar->setValue(time);

    //开启计时器
    startTimerId = this->startTimer(1000);

    //清除textedit的内容
    ui->textEdit->clear();
}

void Widget::on_pushButtonEnd_clicked()
{
    this->close();
}

void Widget::whetherRestart(){
    int choose = QMessageBox::question(this, "提示", "再来一局?");
    if(QMessageBox::Yes == choose){
        //回到初始页面
        ui->stackedWidget->setCurrentWidget(ui->page);
        maxNumber = 10000;
        minNumber = 0;
    }else if(QMessageBox::No){
        this->close();
    }
    //二分法做提示，最大和最小在每次游戏之前都应该先初始化为固定值
    inputNumber.clear();
    randNumber.clear();
    minNumber = 0;
    maxNumber = 10000;
}

void Widget::timerEvent(QTimerEvent *event){
    //游戏时间计时器
    if(event->timerId() == startTimerId){
        time--;
        ui->progressBar->setValue(time);
        //游戏时间到了
        if(0 == time){
            //关闭游戏计时器
            this->killTimer(startTimerId);

            //显示提示信息
            QMessageBox::information(this, "失败", "时间到!");

            //启动失败的动画
            failMovie->start();

            //切换至失败动画页面
            ui->stackedWidget->setCurrentWidget(ui->page_fail);

            /*
             * 在这里加定时器的原因是想让动画停留一段时间，
             * 此处不能用sleep。
                */
            //启动定时器,，此时动画会播放五秒
            overTimerId = this->startTimer(5000);
        }
    }else if(overTimerId == event->timerId()){
        //停止动画
        failMovie->stop();
        //关闭定时器
        this->killTimer(overTimerId);
        //判断是否要重来
        this->whetherRestart();
    }else if(winTimerId == event->timerId()){
        //停止动画
        winMovie->stop();
        //关闭定时器
        this->killTimer(winTimerId);
        //判断是否要重来
        this->whetherRestart();
    }
}

void Widget::on_pushButton_Hint_clicked()
{
    int randnumber = randNumber.toInt();
    int number = (maxNumber + minNumber) / 2;
    if(randnumber > number){
        minNumber = number;
        ui->textEdit->clear();
        ui->textEdit->setText(QString("数字在%1与%2之间。").arg(minNumber).arg(maxNumber));
    }else if(randnumber < number){
        maxNumber = number;
        ui->textEdit->clear();
        ui->textEdit->setText(QString("数字在%1与%2之间。").arg(minNumber).arg(maxNumber));
    }else{
        /*
         * 用下述缩小范围的方式会出现一个问题，当提示的数和重合时，
         * 且该数为奇数并且是最小值，那么加一之后提示的数就比随机
         * 数要大了，程序就崩溃了，那么就可以人为定义一下范围
        */
        if(randnumber - 5 < minNumber || randnumber +5 > maxNumber){
            ui->textEdit->append("已经不能再提示了。");
            return;
        }
        /*
         * 因为最后产生的两个数中肯定是一个为奇数一个为偶数，
         * 所以要提示的范围更小，则需要在将为奇数的值变为偶数，
         * 再进行更进一步的二分计算。
         *
         * 哪一个数为奇数则加一。
        */
        if(maxNumber % 2 == 1){
            maxNumber += 1;
        }
        if(minNumber %2 == 1){
            minNumber += 1;
        }
        //设置完数后再来处理数
        this->on_pushButton_Hint_clicked();
    }
}

void Widget::deal_Number(){
    //获取信号的发送者
    QObject *signalSender = this->sender();
    //将信号转换为想要的类型
    QPushButton *button = (QPushButton *)signalSender;

    //当发送者不为空时开始处理
    if(NULL != button){
        //获取按钮的内容
        QString content = button->text();
        //将按钮的内容加入到作为输出的inputNumber字符串中
        inputNumber += content;

        //如果resultStr的长度为1，那么首字符不能为0，否则清空textEdit
        if(inputNumber.size() == 1 && content == "0"){
            ui->textEdit->clear();
        }
        ui->textEdit->setText(inputNumber);
    }
}

void Widget::on_pushButton_Submit_clicked()
{
    if(inputNumber.toInt() > randNumber.toInt()){
        ui->textEdit->append("数字太大");
        ui->textEdit->clear();
    }else if(inputNumber.toInt() < randNumber.toInt()){
        ui->textEdit->append("数字太小");
        ui->textEdit->clear();
    }else{
        ui->textEdit->append("恭喜你答对了");

        //关闭游戏时间定时器
        this->killTimer(startTimerId);
        QMessageBox::information(this, "胜利", "恭喜你胜利了!");

        //切换到胜利页面
        winMovie->start();
        ui->stackedWidget->setCurrentWidget(ui->page_win);

        //启动定时器，动画播放五秒钟
        winTimerId = this->startTimer(5000);
    }
    qDebug() << inputNumber;
}

void Widget::on_pushButton_BackSpace_clicked()
{
    //inputNumber最后一位去掉
    if(inputNumber.size() > 1){
        //直接将其最后一位设置为"\0"
        // inputNumber[inputNumber.size() - 1] = '\0';

        /*
         * Removes n characters from the end of the string.
         * 从字符串的结尾移除n个字符
            */
        inputNumber.chop(1);
        //写在这里是因为，在给出提示信息时，不会覆盖提示信息
        ui->textEdit->setText(inputNumber);
    }else if(inputNumber.size() == 1){
        //少于一位时则直接清除
        inputNumber.clear();
        ui->textEdit->setText(inputNumber);
    }
    //写在这里时，程序的提示信息会被覆盖
    // ui->textEdit->setText(inputNumber);
}
