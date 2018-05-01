#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //创建自定义的线程
    mythread = new MyThread;
    //创建QThread线程
    thread = new QThread(this);
    mythread->moveToThread(thread);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    //调用线程的处理函数
    connect(this, &Widget::wakePaint, mythread, &MyThread::threadDrawImage);
    //处理返回的图片
    connect(mythread, &MyThread::drawDone, this, &Widget::dealImage);
    //开启线程
    thread->start();

    painter = new QPainter();

    connect(this, &Widget::destroyed, this, &Widget::dealClose);
}

void Widget::dealImage(QImage *image){
    receive_image = image;
    //间接调用paintEvent()
    this->update();
}

void Widget::dealClose(){
    thread->quit();
    thread->wait();
}

//因为是在widget中画图，所以就要在paintEvent中实现
void Widget::paintEvent(QPaintEvent *event){
    painter->begin(this);
    painter->drawImage(0, 0, *receive_image);
    painter->end();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_DrawImage_clicked()
{
    //发出唤醒线程的信号
    emit wakePaint();
}
