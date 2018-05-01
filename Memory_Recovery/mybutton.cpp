#include "mybutton.h"
#include <QDebug>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

MyButton::~MyButton(){
      qDebug()<<"析构函数被调用";
}
