#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
      /*在没有指定父对象时，控件就只是一个单独的控件，显示在一个属于自己的单独窗口,此时要单独调用显示
        控件可以装入容器，这里的容器就是主窗口*/
      //b.show();

      //设定父对象，就是装载他的容器
      close_button.setParent(this);
      close_button.setText("close button");
      //设置按钮位置
      close_button.move(225, 50);

      jump_button.setParent(this);
      jump_button.setText("jump button");
      jump_button.move(225, 450);

      //信号和槽
      //信号发出者，&发送者的类名::信号名称 信号接受者 &接受者的类名::槽函数名字
      connect(&close_button, &QPushButton::clicked, this, &QWidget::close);

      /*自定义槽函数
       *  槽函数需要跟信号一致（参数，返回值）
       *  由于信号没有返回值，所以，槽函数一定没有返回值
      */

      /*
       *  1.按钮jump_button捕捉到鼠标敲击信号后调用槽函数:
       *    将当前窗口隐藏，子窗口显示
       *  2.子窗口按钮return捕捉到鼠标敲击信号后调用槽函数：
       *    发送信号，该信号在之前已经定义好
       *  3.父窗口接收到子窗口SubPage发送来的ReturnPage信号后调用槽函数：
       *    将子窗口隐藏，父窗口显示
      */

      //捕捉到鼠标在jump_button上的点击后用槽函数响应点击
      connect(&jump_button, &QPushButton::clicked, this, &Widget::DealSolts);

      //主窗口接收到SubPage发来的ReturnPage信号后，相应信号
      connect(&SubPage, &JumpPage::ReturnPage, this, &Widget::DealSignals);
}

void Widget::DealSolts(void)
{
    this->hide();
    SubPage.show();
}

void Widget::DealSignals()
{
    SubPage.hide();
    this->show();
}

Widget::~Widget()
{

}
