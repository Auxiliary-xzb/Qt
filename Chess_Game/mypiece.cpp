#include "mypiece.h"
#include <QPainter>
#include <QPixmap>

MyPiece::MyPiece(QWidget *parent) : QWidget(parent)
{
    //设置widget的边框为隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | this->windowFlags());
    //设置背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void MyPiece::paintEvent(QPaintEvent *event){
    //获取图片
    QPixmap pixmap(":/new/prefix1/picture/piece.png");
    //定义画家
    QPainter painter;
    //设置当前widget为绘图设备
    painter.begin(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
    //结束绘图
    painter.end();
}
