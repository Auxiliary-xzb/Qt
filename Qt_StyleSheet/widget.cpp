#include "widget.h"
#include "ui_widget.h"
#include <QLabel>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //将该widget下所有的QLabel对象都设置该style
    this->setStyleSheet("QLabel {border:5px solid black}");
    //设置名为label_2标签的背景色为red，与下面的相等。
    this->setStyleSheet("QLabel#label_2 {background-color:red}");
    ui->setupUi(this);
    //设置某一个
    ui->label->setStyleSheet("border:2px solid red");
}

Widget::~Widget()
{
    delete ui;
}
