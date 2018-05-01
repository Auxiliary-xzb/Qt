#include "widget.h"
#include "ui_widget.h"
#include <QEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QDebug>
#include <QKeyEvent>
#include "myeventfilter.h"
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->startTimer(10);

    ui->label_2->installEventFilter(this);
    ui->label_2->setMouseTracking(true);
}

bool Widget::event(QEvent *event){
    /*
    * event函数根据对事件的判断，在判断完后将event强制转换为
    * 所判断出来的类型，然后交由该方法处理。或者是自己来实
    * 现处理该事件的处理方法。
    */
    //通过type函数来判断事件的类型。可以在帮助文档中查看。

    if( QEvent::KeyPress == event->type()){
        QKeyEvent *env = static_cast<QKeyEvent *>(event);
        if ( env->key() != Qt::Key_A )
            qDebug() << env->key();
    }
    switch(event->type()){
    case QEvent::MouseButtonPress:
        QWidget::mousePressEvent(static_cast<QMouseEvent *>(event));
        break;
    case QEvent::MouseMove:
        QWidget::mouseMoveEvent(static_cast<QMouseEvent *>(event));
        break;
        //... 类似上面的形式。
    case QEvent::Timer:
        //当该函数返回true时，该事件将不再传播。
        return true;
    default:
        QWidget::event(event);
        return false;
    }
}

bool Widget::eventFilter(QObject *watched, QEvent *event){
    //判断对象是否为需要过滤的对象
    if(watched == ui->label_2){
        //判断事件类型
        if(event->type() == QEvent::MouseMove){
            //强制类型转换
            QMouseEvent *ev = static_cast<QMouseEvent *>(event);
            if(ev->type() == QMouseEvent::MouseMove){
                ui->label_2->setText(QString("Position is %1, %2").arg(ev->x()).arg(ev->y()));
                //不让事件继续传播
                return true;
            }
        }
    }

    QWidget::eventFilter(watched, event);
}

void Widget::timerEvent(QTimerEvent *event){
    static int count = 0;
    ui->label->setText(tr("Count is %1").arg(count++));
}

void Widget::mousePressEvent(QMouseEvent *event){
    qDebug() << "按钮被按下";
}

Widget::~Widget()
{
    delete ui;
}
