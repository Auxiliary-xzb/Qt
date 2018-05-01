#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QBitmap>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->setMinimumWidth(600);
    this->setMinimumHeight(800);
    ui->setupUi(this);

    //绘图设备， 400， 400
    QPixmap pixmap(400, 300);
    //画家
    QPainter p;
    //画家开始在绘图设备上绘图
    p.begin(&pixmap);
    //填充背景色，因为保存图片时默认背景是黑色
    p.fillRect(pixmap.rect(), QBrush(Qt::red));
    pixmap.fill(Qt::red);
    //进行绘图
    p.drawPixmap(0, 0, 80, 80, QPixmap("../image/bk.jpg"));
    //结束画图
    p.end();
    //保存绘图设备所产生的绘图
    pixmap.save("../pixmap.jpg");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event){
    QPainter painter;
    //背景为透明
    QPixmap pixmap_transparent(":/new/prefix1/picture/b.png");
    QBitmap bitmap_transparent(":/new/prefix1/picture/b.png");
    //背景为白色
    QPixmap pixmap_background(":/new/prefix1/picture/a.jpeg");
    QBitmap bitmap_background(":/new/prefix1/picture/a.jpeg");
    //指定绘图设备为当前的widget
    painter.begin(this);
    //绘图
    painter.drawPixmap(0, 0, 300, 400, pixmap_transparent);
    //由于QBitmap是QPixmap的子类，所以使用父类的方法画图
    painter.drawPixmap(300, 0, 300, 400,  bitmap_transparent);
    painter.drawPixmap(0, 400, 300, 400, pixmap_background);
    painter.drawPixmap(300, 400, 300, 400, bitmap_background);
    //结束绘图
    painter.end();
}
