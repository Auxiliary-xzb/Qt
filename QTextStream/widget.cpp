#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>

#define cout qDebug() << "[" <<__FILE__ << ":" << __LINE__ << "]"

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

void Widget::on_pushButton_ReadFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), "../");
    if(!path.isEmpty()){
        QFile file(path);
        bool isOK = file.open(QFile::ReadOnly);
        if(isOK){
            QTextStream in(&file);
            QString text;
            double number_1, number_2;
            int number;
            /*
             *      qSetFieldWidth为设置输出格式
             *      out << "Result: " << qSetFieldWidth(10) << left << 3.14 << 2.7; //writes "Result: 3.14      2.7
             *      in >> text >> number_1 >>number_2;
             *      cout << text << number_1 << number_2;
             *
             * 使用上述方法在读取数据时会出现问题，结果为下：
             *      [ ..\QTextStream\widget.cpp : 34 ] "Result:" 3 0
             *
             *      out << QString("黄鑫是傻子") << 250;
             *      in >> text >> number;
             *      cout << text.toUtf8().data() << number;
             * 使用上诉方法在读取数据时会出现问题，结果如下：
             *      [ ..\QTextStream\widget.cpp : 42 ] 黄鑫是傻子250 0
             *
             * 所以在读取数据时，以上方法都不怎么好，
            */
            //设置编码
            in.setCodec("UTF-8");
            QString string;
            while(in.readLineInto(&string)){
                cout << string.toUtf8().data();
            }
            file.close();
        }
    }
}

void Widget::on_pushButton_WriteFile_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), "../", tr("TXT(*.txt)"));
    if(!path.isEmpty()){
        QFile file(path);
        bool isOK = file.open(QFile::WriteOnly);
        if(isOK){
            QTextStream out(&file);
            //设置编码
            out.setCodec("UTF-8");
            out << QString("黄鑫是傻子") << 250;
            file.close();
        }
    }
}
