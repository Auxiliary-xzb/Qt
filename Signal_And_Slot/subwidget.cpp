#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("子窗口");
    button = new QPushButton("返回父窗口", this);
    connect(button, &QPushButton::clicked, this, &SubWidget::SendSignal);
}

//当点击了鼠标后，让槽函数去发送一个信号，可以在主窗口接收该信号并设置槽函数进行处理
void SubWidget::SendSignal(){
    emit Return_Parent();
    emit Return_Parent(250, "哈哈");
}
