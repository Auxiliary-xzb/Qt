#include "mybutton.h"
#include <QMouseEvent>
#include <QDebug>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

void MyButton::mousePressEvent(QMouseEvent *e){

        if(Qt::LeftButton == e->button()){
               qDebug()<< "左键按下，事件已经被接收，不再传递";
                e->accept();
         }else{
                qDebug() << "事件被忽略，传递给其父部件，消息可能被父组件的mousePressEvent函数接收";
                e->ignore();
         }


       /*
        * 当重写mousePressEvent函数时，如果什么实现虚函数，
        * 默认是不会将事件传递下去的。
        * 可以选择调用父类的mousePressEvent函数来处理事件。
        * 处理结果是显示“按钮被按下”
        */
      // QPushButton::mousePressEvent(e);
}
