#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPicture>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //定义一个绘图设备
    QPicture picture;
    //定义一个画家
    QPainter painter;
    //开始绘图
    painter.begin(&picture);
    painter.drawImage(0, 0, QImage(":/new/prefix1/picture/a.jpeg"));

    //结束绘图
    painter.end();

    //保存后，在该图片中是看不见任何显示的。
    picture.save("../picture.png");
}

void Widget::paintEvent(QPaintEvent *event){
    QPicture picture;
    //加载图片
    picture.load("../picture.png");
    QPainter painter;
    //指定绘图设备为当前窗口
    painter.begin(this);
    painter.drawPicture(0, 0, picture);
    painter.end();
}

Widget::~Widget()
{
    delete ui;
}
