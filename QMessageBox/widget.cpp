#include "widget.h"
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QColorDialog>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QMenuBar *menubar = new QMenuBar(this);
    QMenu *menu = new QMenu("File");
    menubar->addMenu(menu);

    QAction *about = new QAction("关于对话框",this);
    menu->addAction(about);
    connect(about, &QAction::triggered,
            [ = ](){
        QMessageBox::about(this, "关于Qt","这是关于qt的介绍");
    });

    QAction *question = new QAction("问题对话框",this);
    menu->addAction(question);
    connect(question, &QAction::triggered,
            [ = ](){
        QMessageBox::StandardButton ret = QMessageBox::question(this,"问题对话框","信息错误",
                                                                    QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);
        QString str = NULL;
        switch(ret){
        case QMessageBox::Yes:
            str = tr("yes键被按下");
            break;
        case QMessageBox::No:
            str = tr("no键被按下");
            break;
        }
        QMessageBox::about(this,"提示信息",str);
    });

    QAction *warning = new QAction("警告对话框",this);
    menu->addAction(warning);
    connect(warning, &QAction::triggered,
            [ = ](){
        int ret = QMessageBox::warning(this,"警告对话框","信息输入有误");
        QString str = NULL;
        if(QMessageBox::Ok  == ret)
            str = tr("OK被按下");
        QMessageBox::about(this,"提示信息",str);
    });

    QAction *critical = new QAction("严重错误对话框",this);
    menu->addAction(critical);
    connect(critical, &QAction::triggered,
            [ = ](){
            QMessageBox::critical(this,"严重错误对话框","错误内容");
    });

    QAction *information = new QAction("消息对话框", this);
    menu->addAction(information);
    connect(information, &QAction::triggered,
            [ = ](){
            QMessageBox::information(this,"消息对话框","提示的消息");
    });

    //文件对话框
    QAction *filedialog = new QAction("文件对话框", this);
    menu->addAction(filedialog);
    connect(filedialog, &QAction::triggered,
            [ = ](){
        //在文档中显示，该方法是最快的创建一个文件文件对话框的方式
            QFileDialog::getOpenFileName(this, "open", "../", tr("Image Files (*.png *.jpg *.bmp);;source (*.cpp)"));
    });

    //颜色对话框
    QAction *colordialog = new QAction("颜色对话框", this);
    menu->addAction(colordialog);
    connect(colordialog, &QAction::triggered,
            [ = ](){
        //该方法是最快的创建一个颜色对话框的方式
            QColor  color = QColorDialog::getColor(QColor(255, 255, 255, 0));
            qDebug()  <<  "r= " << color.red() << "g= " << color.green() << "b=" << color.blue();
    });

}

Widget::~Widget()
{

}
