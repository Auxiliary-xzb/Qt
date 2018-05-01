#include "jumppage.h"

JumpPage::JumpPage(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(500, 500);
    this->setWindowTitle("this is jump page");
    return_button.setParent(this);
    return_button.setText("return");

    //按钮return_button接收到鼠标点击信号后，当前页面就利用槽函数发出信号
    connect(&return_button, &QPushButton::clicked, this, &JumpPage::DealSolts);
}
//发出信号
void JumpPage::DealSolts()
{
    emit ReturnPage();
}
