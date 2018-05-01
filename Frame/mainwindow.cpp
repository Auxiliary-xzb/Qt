#include "mainwindow.h"
#include <QDialog>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置菜单栏
    menubar = menuBar();

    //创建和加入菜单项
    menu_1 = new QMenu("File");
    menubar->addMenu(menu_1);

    //为菜单项添加动作
    menu_1->addAction("New");
    action_1 = menu_1->addAction("Model dialog");
    action_2 = menu_1->addAction("Modeless dialog");
    action_3 = menu_1->addAction("Close");

    connect(action_3 , &QAction::triggered , this , &QWidget::close);

    //添加工具栏
    toolbar = new QToolBar(this);
    button_1 = new QPushButton();
    //设置按钮的格式（图片填满按钮）
    button_1->setStyleSheet("border-image:url(://20.jpg)");
    toolbar->addWidget(button_1);
    toolbar->setMinimumHeight(25);
    addToolBar(toolbar);

    //添加消息栏
    statusbar = new QStatusBar(this);
//    label = new QLabel("this is statusbar");
    label_2 = new QLabel("1");
    label_3 = new QLabel("2");

    //从左插入
//    statusbar->addWidget(label);
    //从右插入
    statusbar->addPermanentWidget(label_2);
    statusbar->addPermanentWidget(label_3);

    //插入临时信息,显示十秒钟
    statusbar->showMessage("hello world", 10000);
    setStatusBar(statusbar);

    //模态和非模态对话框
    connect(action_1, &QAction::triggered, this, &MainWindow::dealmodal);
    connect(action_2, &QAction::triggered, this, &MainWindow::dealmodeless);


    //浮动窗口
    dockwidget[0] = new QDockWidget("dockwidget_L");
    this->addDockWidget(Qt::LeftDockWidgetArea, dockwidget[0]);

    dockwidget[1] = new QDockWidget("dockwidget_R");
    this->addDockWidget(Qt::RightDockWidgetArea, dockwidget[1]);

    dockwidget[2] = new QDockWidget("dockwidget_T");
    this->addDockWidget(Qt::TopDockWidgetArea, dockwidget[2]);

    dockwidget[3] = new QDockWidget("dockwidget_B");
    this->addDockWidget(Qt::BottomDockWidgetArea, dockwidget[3]);
/*
    QWidget *widget = new QWidget();
    QVBoxLayout *back = new QVBoxLayout();
    back->addWidget(dockwidget_1);
    back->addWidget(dockwidget_2);
    widget->setLayout(back);
    this->setCentralWidget(widget);
*/
}

MainWindow::~MainWindow()
{

}


void MainWindow::dealmodal(){
    QDialog dialog;
    //模态
    dialog.exec();
    dialog.show();
}


void MainWindow::dealmodeless(){

    /*
     *  一下定义为局部变量，函数结束就没了，所以dialog会一闪而过
    QDialog dialog;
    dialog.show();
    */

    QDialog *dialog = new QDialog();
    dialog->show();
}
