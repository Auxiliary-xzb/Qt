#include "myeventfilter.h"
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

MyEventFilter::MyEventFilter(QObject *parent) : QObject(parent)
{

}

/*
 * 可以这样设置过滤器，但是不能完成很多东西，比如传递值就
 * 不行。还是直接用父组件的方式来管理比较好。
*/
bool MyEventFilter::eventFilter(QObject *watched, QEvent *event){
    if(event->type() == QEvent::MouseMove){
        QMouseEvent *ev = static_cast<QMouseEvent *>(event);
        this->setProperty("xposition", QVariant(ev->x()));
        this->setProperty("yposition", QVariant(ev->y()));
        qDebug() << tr("Postion is %1, %2").arg(ev->x()).arg(ev->y());
        return true;
    }else{
        return QObject::eventFilter(watched, event);
    }
}
