#include "mydialog.h"
#include <QMessageBox>
#include <QCloseEvent>

MyDialog::MyDialog(QWidget *parent) : QDialog(parent)
{
    this->button = new QPushButton(this);
    button->setText("Return");

    connect(button, &QPushButton::clicked, this, &MyDialog::returnPage);
}

void MyDialog::returnPage(){
    emit Return();
}

void MyDialog::closeEvent(QCloseEvent *event){
    int value = QMessageBox::question(this,"提示", "是否关闭窗口");
    if(QMessageBox::Yes == value){
        QWidget::closeEvent(event);
        emit Return();
    }else{
        event->ignore();
    }
}
