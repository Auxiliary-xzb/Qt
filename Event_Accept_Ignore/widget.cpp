#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    /*
     * 只有在调用的QPushButton类的mousePressEvent事件时，
     * 才会发出clicked信号。
    */
    connect(ui->pushButton, &MyButton::clicked,
            [ = ](){
            qDebug() << "按钮被按下";
    });

     mydialog = new MyDialog(this);
    mydialog->setVisible(false);
    connect(ui->pushButton_2, &QPushButton::clicked,
            [ = ](){
            mydialog->show();
            this->hide();
    });

    connect(mydialog, &MyDialog::Return,
            [ = ](){
            this->show();
            mydialog->hide();
    });
}

void Widget::mousePressEvent(QMouseEvent *event){
    qDebug() << "父组件接收到了事件，做出的响应。";
}

void Widget::closeEvent(QCloseEvent *event){
    int button = QMessageBox::question(this,"提示","是否关闭窗口");
    if(QMessageBox::Yes == button){
        //当点击的是yes按钮时，就直接将事件交由QWidget处理，然后不然消息继续发送。
        QWidget::closeEvent(event);
        event->accept();
    }else{
        //忽略消息。
        event->ignore();
    }
}
Widget::~Widget()
{
    delete ui;
}
