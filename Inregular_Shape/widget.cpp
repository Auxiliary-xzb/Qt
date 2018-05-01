#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    /*
     * 调用该函数时可以看到，窗口移动时是移动的整个窗口，
     * 包括窗口的边框，而且可以看见，此时的(0, 0)坐标代表
     * 的是窗口边框的坐标。
        */
    this->move(0, 0);
    this->setMinimumWidth(400);
    this->setMinimumHeight(600);
    ui->setupUi(this);
    //隐藏窗口边框。
    /*
     * Qt::FramelessWindowHint为产生一个没有外边框的窗口。
     * 还是要包含原来的标志。
    */
    this->setWindowFlags(Qt::FramelessWindowHint | this->windowFlags());
    //该属性为整个窗口的透明度
    this->setWindowOpacity(0.5);
    //隐藏widget的背景
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void Widget::paintEvent(QPaintEvent *event){
    /*
     * QPixmap pixmpa(":/new/prefix1/picture/a.jpeg");
     * 当使用上诉图片时，可看见，就算隐藏了widget
     * 的背景，图片还是把白色的底色给显示出来了。
    */
    QPixmap pixmap(":/new/prefix1/picture/b.png");
    QPainter painter;
    //指定绘图设备为当前窗口
    painter.begin(this);
    painter.drawPixmap(0, 0, 400, 600, pixmap);
    painter.end();
}

/*
 * 如何做到窗口的拖动：
 *  1.在窗口拖动中有三个事件：
 *      1.1鼠标左键按下事件，当该事件单独发生时，什么都不干。
 *      1.2鼠标移动事件，当该事件单独发生时，什么都不干
 *      1.3鼠标放下事件。
 * 2.三个事件分别要做的事情：
 *      2.1当鼠标左键按下时，设置鼠标按下标志位1，保存当前鼠
 * 标坐标，保存窗口左上角的坐标。
 *      2.2当鼠标移动时，如果鼠标按下标志位1，则获取当前坐标，
 *           获取当前窗口左上角坐标。然后计算窗口移动的位置。
 *      2.3当鼠标松开时，设置鼠标按下标志位为0。
 * 3.计算窗口移动坐标：
 *      因为移动的是整个窗口，所以是包括边框的，在调用move函数
 * 时，指定的坐标为窗口边框左上角的坐标。
 *      左上角的坐标计算方法：
 *          将移动时的鼠标坐标减去按下左键时的坐标，就得到了一个
 * 坐标的差值，那么该差值就是左上角坐标的差值。
*/
void Widget::mousePressEvent(QMouseEvent *event){
    //如果是鼠标左键按下则关闭窗口
    if(event->button() == Qt::RightButton){
           this->close();
    }else if(event->button() == Qt::LeftButton){
        //设置鼠标按下标志位1
        isLeftButtonPressed = 1;
        beginMousePosition = event->globalPos();
        //先获取整个窗口的矩形区域，然后再获取左上角的坐标
        beginTopLefCorner = this->geometry().topLeft();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event){
    //鼠标左键按下
    if(isLeftButtonPressed == 1){
        //获取当前鼠标坐标
        currentMousePosition = event->globalPos();
        //计算两次移动的差值
        QPoint difference = currentMousePosition - beginMousePosition;
        //计算当前左上角的坐标
        /*
         * 为什么这里可以直接写'+':
         *      因为当鼠标上移时得到的坐标差值肯定为负数，当
         * 鼠标下移时得到的坐标差值为正数，那么加正数为加，
         * 加负数为减，所以就可以将鼠标的变化和为左上角的
         * 变化变成相同的了。
        */
        currentTopLeftCorner = beginTopLefCorner +difference;
        this->move(currentTopLeftCorner);
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event){
    isLeftButtonPressed = 0;
}

Widget::~Widget()
{
    delete ui;
}
