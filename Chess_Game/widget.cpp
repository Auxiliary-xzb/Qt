#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPixmap>
#include <QPen>
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    locateX = 0;
    locateY = 0;
    this->setMinimumWidth(1200);
    this->setMinimumHeight(800);
    ui->setupUi(this);

    //创建棋子对象，默认不显示，在点击后才显示
    piece = new MyPiece(this);
    piece->hide();
}

void Widget::paintEvent(QPaintEvent *event){
    //将当前窗口的宽度等分为十份
    boxWidth = this->width()/10;
    //将当前窗口的高度等分为十份
    boxHeight = this->height()/10;

    //当窗口需要重绘时调用，所以就不生成对象，那样会内存泄漏
    QPixmap pixmap(":/new/prefix1/picture/bk.jpg");
    QPainter painter;
    QPen pen;
    pen.setWidth(8);
    //指定当前widget为绘图设备
    painter.begin(this);
    //将pen交给painter之前必须先开启画家
    painter.setPen(pen);
    //绘制背景图片
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);

    //绘制一个8*8的网格
    for(int r = 0 ; r < 9 ; r++){
        painter.drawLine(boxWidth, boxHeight*(r+1), boxWidth*9, boxHeight*(r+1));
    }

    for(int c = 0 ; c < 9 ; c++){
        painter.drawLine(boxWidth*(c+1), boxHeight, boxWidth*(c+1), boxHeight*9);
    }
    painter.end();
}

void Widget::mousePressEvent(QMouseEvent *event){
    /*
     * 根据鼠标点击的位置来确定方格所在的格的坐标
     * 根据坐标来显示棋子。
     *
     * 如何计算格数：
     *   1.获取当前鼠标的横坐标，将该坐标对一个单元格的宽度相除，
     *      得到的整数部分为该方格在第几列。locateX
     *   2.获取当前鼠标的纵坐标，将该坐标对一个单元格的高度相除，
     *      得到的整数部分为该方格在第几行。locateY
     *
     * 得到的坐标即为方格的格子号。
     * 将棋子以格子的大小显示出来，在鼠标松开后棋子隐藏。
     */
     int x = event->x();
     int y = event->y();
     locateX = x / boxWidth;
     locateY = y / boxHeight;

     /*
      * 从该例子可以得出以下结论：
      *    画笔pen的宽度是由线的中间对半分的，
      * 所以在移动位置时需要加上一半的线宽
        */
     piece->move(boxWidth*locateX + 4, boxHeight*locateY + 4);
     piece->setMinimumHeight(boxHeight - 8);
     piece->setMaximumHeight(boxHeight - 8);
     piece->setMinimumWidth(boxWidth - 8);
     piece->setMaximumWidth(boxWidth - 8);
     piece->show();
}

void Widget::mouseReleaseEvent(QMouseEvent *event){
      /*
       * 当鼠标松开后图片隐藏，图片定位被初始化。
        */
    piece->hide();
    locateX = 0;
    locateY = 0;
}

Widget::~Widget()
{
    delete ui;
}
