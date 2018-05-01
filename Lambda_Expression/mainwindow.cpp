#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    button_1 = new QPushButton(this);
    button_1->setText("Lambda表达式");
    //调整部件的大小以适应其内容
    button_1->adjustSize();
    int a = 0;
    connect(button_1, &QPushButton::clicked,
               //传值方式会产生一个副本，如果想修改副本需要加入mutable，修改的仅仅是副本，对原始项不修改。
               [ = ](bool Checked) mutable {
                qDebug() << Checked;
                button_1->setText("shit");
                qDebug() << a;

                //传值时且不加mutable的情况下，执行下述操作编译器会报错，提示该字段为只读。
                a++;
    }
    );
}

MainWindow::~MainWindow()
{

}
