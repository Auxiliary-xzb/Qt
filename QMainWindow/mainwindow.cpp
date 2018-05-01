#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
        //菜单栏
        QMenuBar *menubar = this->menuBar();

        //添加菜单
         QMenu *pFile = menubar->addMenu("文件");

         //添加菜单项，添加动作
         QAction *action = pFile->addAction("新建");

         /*
          * 在文档中有如下描述
          * The receiver will be notifed whenever the item is triggered().
          * In addition, QMenu provides two signals, activated() and highlighted(), which signal the QAction that was triggered from the menu.
          *接受者将被唤醒，当接收到triggered信号，另外QMenu提供两个信号，activated和highlighted
            */
         connect(action, &QAction::triggered,
                 [ = ](){
                            qDebug()<< "新建被按下";
                 }
                 );

         //添加分割线
         pFile->addSeparator();
         QAction *action_2 = pFile->addAction("保存");

         //工具栏,就是菜单项的快捷方式,设置的名字不会显示，仅仅只是一个标签而已
        QToolBar *toolbar = this->addToolBar("toolbar");

        //工具栏添加快捷键,因为快捷键，所以直接把action的指针拿来就行
        toolbar->addAction(action);
        toolbar->addSeparator();
        toolbar->addAction(action_2);
        toolbar->addSeparator();

        //设置添加方式，垂直方向添加还是水平方向上添加
        toolbar->setOrientation(Qt::Horizontal);

        //工具栏添加控件
        QPushButton *button = new QPushButton(this);
        button->setText("shit");
        toolbar->addWidget(button);

        connect(button, &QPushButton::clicked,
                [ = ](){
                button->setText("123");
        });

        //状态栏
        QStatusBar *statusbar = statusBar();
        QLabel *label = new QLabel(this);
        label->setText("shit");

        //addWidget默认是从左往右添加
        statusbar->addWidget(label);
        statusbar->addWidget(new QLabel("2", this));

        //QToolBar使用addPermanentWidget来从右至左添加
        statusbar->addPermanentWidget(new QLabel("baga",this));

        //核心控件
        QTextEdit *edit = new QTextEdit(this);
        this->setCentralWidget(edit);
       /*
         * QTextEdit为多行文本
         * QLineEdit为单行文本
         */

        //浮动窗口
        QDockWidget *dockwidget = new QDockWidget(this);
        this->addDockWidget(Qt::BottomDockWidgetArea, dockwidget);
        QLineEdit *line = new QLineEdit(edit);
        dockwidget->setWidget(line);
}

MainWindow::~MainWindow()
{

}
