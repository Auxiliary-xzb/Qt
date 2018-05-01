#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
      /*
       * 按照c++的语法，如何不显示调用delete函数，那么程序时绝对不会调用
       * 析构函数的。
       *        由于要验证是否在没有调用delete方法时，调用了析构函数，
       * 所以我们要自己创建一个按钮继承自QPushButton。然后在其析构
       * 函数中显示提示信息，然后根据提示信息证明在没有显示delete的情况
       * 下调用了delete。
       */
        /*
         * 自动条用delete条件：
         *      1.指定了父对象
         *      2.直接或间接继承与QObject
            */
        mybutton = new MyButton(this);
        mybutton->setText("shit");

        /*
         *可以发现，在程序输出了析构函数被调用
        */
}

Widget::~Widget()
{

}
