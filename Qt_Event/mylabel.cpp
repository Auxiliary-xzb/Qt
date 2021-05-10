#include "mylabel.h"
#include <QMouseEvent>
#include <QPoint>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    /*
     *      This property holds whether mouse tracking is enabled for the widget.
     *      If mouse tracking is disabled (the default), the widget only receives mouse move
     *  events when at least one mouse button is pressed while the mouse is being moved.
     *      If mouse tracking is enabled, the widget receives mouse move events even if no
     * buttons are pressed.
     *
     *      该属性表示widget的鼠标追踪有用。
     *      如果鼠标追踪不可用（默认值），当鼠标移动且至少一个鼠标按钮
     * 被按下时，widget才会接收鼠标移动事件。
     *      如果鼠标追踪可用，widget接收鼠标移动事件即使没有按钮被按下。
     *
     * 也就是说，在鼠标追踪不可用时，只有按下了一个按钮之后才会接收
     * 鼠标移动事件。
    */
    this->setMouseTracking(true);
}

void MyLabel::mouseMoveEvent(QMouseEvent *ev){
    /*
     * 获取相对于当前窗口的坐标，两者等价于ev->pos()
     * int x = ev->x();
     * int y = ev->y();
    */
    QPoint position = ev->pos();
    QString text = QString("<center><h1>Mouse Position:(%1,%2)</h1></center>").arg(ev->x()).arg(ev->y());
    this->setText(text);
}

void MyLabel::mousePressEvent(QMouseEvent *ev){

    QString text = QString("<center><h1>鼠标按下</h1></center>");
    this->setText(text);
}

void MyLabel::mouseReleaseEvent(QMouseEvent *ev){
    QString text = QString("<center><h2>鼠标释放</h2></center>");
    this->setText(text);
}
