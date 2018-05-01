#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QCloseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer_1 = new QTimer(this);
    timer_2 = new QTimer(this);

    isFirstTime = true;
    isFirstTime_1 = true;

    mythread_1 = new MyThread_1(this);

    //第一种方式创建和处理线程
    //线程在处理完信息后会发出threadDone()信号
    connect(mythread_1, &MyThread_1::threadDone, this, &Widget::deal_Thread_1);
    //帮助文档中指明了该句，所以协商。
    connect(mythread_1, &MyThread_1::finished, mythread_1, &MyThread_1::deleteLater);


    //第二种方式创建和处理线程
    thread = new QThread(this);
    mythread_2 = new MyThread_2;
    mythread_2->moveToThread(thread);
    connect(thread,&QThread::finished, thread, &QThread::deleteLater);
    /*
     * 该方法不会主动调用线程的操作函数，而上述方法会主动调用run()函数。
     * 所以上述方法会发出threadDone()信号，而下述方法，只有主动调用线
     * 程的操作函数后才会获得操作所发出的信号
     */
    connect(this,&Widget::wakeThread, mythread_2, &MyThread_2::doWork);
    connect(mythread_2, &MyThread_2::workDone, this, &Widget::deal_Thread_2);
    //启动线程
    thread->start();

    connect(timer_1, &QTimer::timeout, this, &Widget::deal_Timer_1);
    connect(timer_2, &QTimer::timeout, this, &Widget::deal_Timer_2);

    connect(this, &Widget::destroyed, this, &Widget::deal_Destroy);
}

void Widget::deal_Timer_1(){
    static int value_1 = 0;
    value_1++;

    ui->lcdNumber_1->display(value_1);
}

void Widget::deal_Timer_2(){
    static int value_2 = 0;
    value_2++;

    ui->lcdNumber_2->display(value_2);
}

void Widget::deal_Thread_1(){
    qDebug() << "Child_1 thread had done!";
}

void Widget::deal_Thread_2(){
    qDebug() << "Child_2 thread had done!";
}

void Widget::deal_Destroy(){
    /*
     * 当没有主动关闭线程时，线程可能继续自己运行，所以每次在线程
     * 使用完后就要手动关闭线程
     * QThread: Destroyed while thread is still running
    */

    //办完手头的事在停止。terminate()函数在帮助文档中表示，使用是十分危险的。
    mythread_1->quit();
    mythread_1->threadStop();
    mythread_1->wait();

    thread->quit();
    mythread_2->threadStop();
    thread->wait();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_Start_1_clicked()
{
    if(timer_1->isActive() == false){
        //如果计时器没有活动，则开启计时器，然后开启线程,
        timer_1->start(250);
        mythread_1->start();
        if(!isFirstTime_1){
            //如果不是第一次开启计时器则线程继续
            mythread_1->threadResume();
        }
        isFirstTime_1 = false;
    }
}

void Widget::on_pushButton_Stop_1_clicked()
{
    if(timer_1->isActive()){
        //当计时器在活动则关闭计时器，然后不让其发射信号。
        timer_1->stop();
        //线程挂起
        mythread_1->threadPause();
    }
}

void Widget::on_pushButton_Start_2_clicked()
{
    if(timer_2->isActive() == false){
        timer_2->start(50);
        thread->start();
        if(!isFirstTime){
            mythread_2->threadResume();
        }
        isFirstTime = false;
        emit wakeThread();
    }
}

void Widget::on_pushButton_Stop_2_clicked()
{
    if(timer_2->isActive()){
        timer_2->stop();
        mythread_2->threadPause();
    }
}


/*
 * 这里存在一个问题，只有退出的处理函数和close或者destroyed信号
 * 链接才能完成线程的退出。否则就一直无法正常退出。
*/
//void Widget::closeEvent(QCloseEvent *event){
//    /*
//     * 当没有主动关闭线程时，线程可能继续自己运行，所以每次在线程
//     * 使用完后就要手动关闭线程
//     * QThread: Destroyed while thread is still running
//    */

//    //terminate()函数在帮助文档中表示，使用是十分危险的。
//    mythread_1->threadStop();
//    //办完手头的事在停止。
//    mythread_1->quit();
//    mythread_1->wait();
//}
