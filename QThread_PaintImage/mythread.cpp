#include "mythread.h"
#include <QPoint>
#include <QTime>

MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

void MyThread::threadDrawImage(){
    //在线程中绘图，然后将绘图完后的图片返回给主线程.
    image = new QImage(300, 300, QImage::Format_ARGB32);

    //创建画家
    painter = new QPainter();
    //设置线宽
    pen.setWidth(10);
    //创建画刷
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);

    //获取随机种子，由0时0分0秒到现在
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    //随机获取五点，将点连接形成图案
    QPoint point[5] = {
        QPoint(qrand()%300, qrand()%300),
        QPoint(qrand()%300, qrand()%300),
        QPoint(qrand()%300, qrand()%300),
        QPoint(qrand()%300, qrand()%300),
        QPoint(qrand()%300, qrand()%300)
    };
    //开始绘图并指定绘图设备
    painter->begin(image);
    painter->setBrush(brush);
    painter->setPen(pen);
    //绘制多边形的函数
    painter->drawPolygon(point, 5);

    //结束绘图
    painter->end();
    //绘制完图片后，发射信号表示绘图完成
    emit drawDone(image);
}
