#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QIcon>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置toolButton的图片，并且只让按钮显示图片
    //然后将其设置为背景透明，触摸凸起。
    ui->toolButton->setIcon(QIcon(":/src/50.png"));
    ui->toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    ui->toolButton->setAutoRaise(true);

    //设置radioButton的默认值
    //同一时间一组中的radioButto只有一个课被选中，多次
    //设置也是最后一个生效
    ui->radioButton_1 ->setChecked(true);
    ui->radioButton_2 ->setChecked(true);
    ui->radioButton_3 ->setChecked(true);
    ui->radioButton_4 ->setChecked(true);

    //将一个checkbutton设置为三态的，在它所属的widget中其他的checkbutton
    //没有被选中时它为空，选中一个时它为实心，全选它就为勾。
    ui->all_checkBox->setTristate();
    this->selected = 0;
    connect(ui->checkBox_1, &QCheckBox::stateChanged, this, &MainWindow::changeCheckAll);
    connect(ui->checkBox_2, &QCheckBox::stateChanged, this, &MainWindow::changeCheckAll);
    connect(ui->checkBox_3, &QCheckBox::stateChanged, this, &MainWindow::changeCheckAll);
    connect(ui->checkBox_4, &QCheckBox::stateChanged, this, &MainWindow::changeCheckAll);
    connect(ui->checkBox_5, &QCheckBox::stateChanged, this, &MainWindow::changeCheckAll);

    connect(this, &MainWindow::canChanged, this,  &MainWindow::doChange);
}

//当checkbox的状态修改时就更新被选中的数量
//然后将选中的数量作为参数引发信号。
void MainWindow::changeCheckAll(int state) {
    switch(state) {
    case Qt::Unchecked: {
        selected--;
        qDebug() << "decrease selected   " << selected ;
        if (selected == 0) {
            emit canChanged(0);
        } else {
            emit canChanged(selected);
        }
        break;
    }
    case Qt::Checked: {
        selected++;
         qDebug() << "increase selected   " << selected ;
         if (selected == 5) {
             emit canChanged(5);
         } else {
             emit canChanged(selected);
         }
         break;
    }
    }
}

//根据信号传递来的参数判断是否需要修改allcheckbox的状态。
void MainWindow::doChange(int checkedNum) {
    if  (checkedNum == 0) {
        this->ui->all_checkBox->setCheckState(Qt::Unchecked);
    } else if (checkedNum == 5) {
        this->ui->all_checkBox->setCheckState(Qt::Checked);
    }else {
        this->ui->all_checkBox->setCheckState(Qt::PartiallyChecked);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
