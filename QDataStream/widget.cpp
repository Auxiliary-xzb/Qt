#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileDialog>
#include <QDataStream>
#include <QDebug>

#define cout  qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_WriteFile_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "Save File", "../", tr("TXT(*.txt)"));
    if(!path.isEmpty()){
        QFile file(path);
        bool isOK= file.open(QFile::WriteOnly);
        if(isOK){
            //创建一个二进制数据流
            //往数据里中输入数据，相当于往文件中写数据
            QDataStream in(&file);
            in << QString("the answer is");
            in << 42;

            file.close();
        }
    }
}

void Widget::on_pushButton_ReadFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Open File", "../");
    if(!path.isEmpty()){
        QFile file(path);
        bool isOK = file.open(QFile::ReadOnly);
        if(isOK){
            QDataStream out(&file);
            QString str;
            int number;
            out >> str >> number;
//            qDebug() << str.toUtf8().data() << number;
            cout << str.toUtf8().data() << number;

            file.close();
        }
    }
}
