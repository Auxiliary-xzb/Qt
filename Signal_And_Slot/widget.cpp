#include "widget.h"
#include <QBoxLayout>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    button_1 = new QPushButton("button_1", this);
    button_2 = new QPushButton("button_2", this);
    button_3 = new QPushButton("button_3", this);
    button_4 = new QPushButton("跳转到子窗口", this);
    button_5 = new QPushButton("Lambda表达式", this);
    layout->addWidget(button_1);
    layout->addWidget(button_2);
    layout->addWidget(button_3);
    layout->addWidget(button_4);
    layout->addWidget(button_5);
    this->setLayout(layout);
    this->setWindowTitle("父窗口");


    /*
     * 为了验证是否像文档中所说槽函数是按顺序来的执行的，在此设置了两个槽函数与button_1相关联，
     *大概该语句在前是，那么先出现了窗口四，后出现了窗口一
     * 那么可以说槽函数的执行是根据设置前的顺序来执行的。
    */
    //connect(button_1, &QPushButton::clicked, this, &Widget::DealButton_4);

    /*
     * 此方法为Qt4的信号与槽的实现方式
     *在使用这种方法时需要注意几点：
     *      1.在使用SIGNAL宏时，不能添加作用域，不然不能运行
     *      2.在使用SLOT宏时，也不能添加作用域，不然也无法运行
     *      3.在自己实现槽函数时，必须添加slots关键字修饰槽函数。
     *      4.sender需要为指针，receiver需要为指针
     *      5.SIGNAL,SLOT将函数名字转换为字符串，并且不进行错误检查
     *      6.由于是将函数名字转换为字符串，所以你加了作用域也不会报错。
     */
    /*[static] QMetaObject::Connection QObject::connect(const QObject *sender, const char *signal, const QObject *receiver, const char *method,
                                                                                                Qt::ConnectionType type = Qt::AutoConnection)
     * sender：接受者指针
     * signal：由SIGNAL宏包裹的信号
     * receiver：接受者指针
     * method： 由SLOT宏包裹的槽
    */
    //button_1按下回有反应，但是button_2没有反应
    //connect(button_1, SIGNAL(clicked(bool)), this, SLOT(DealButton_1()));
    //connect(button_2, SIGNAL(clicked(bool)), this, SLOT(Widget::DealButton_2()));

    /*
    * 在Qt5中提供的信号与槽的实现方式
    * 在使用这种方法时需要注意几点：
    *       1.在定义信号时，需要添加作用域，要使用信号的指针
    *       2.在定义槽时，需要添加作用域，要使用槽的指针
    *       3.sender需要为指针，receiver需要为指针
    *
    */
    /*
     *[static] QMetaObject::Connection QObject::connect(const QObject *sender, PointerToMemberFunction signal, const QObject *receiver,
     *                                                                              PointerToMemberFunction method, Qt::ConnectionType type = Qt::AutoConnection)
     *
     * sender：发送者指针
     * signale：成员函数指针，&发送者类名::信号名字
     * receiver：接收者指针
     * method：成员函数指针，&接受者类名::槽函数名字
    */
    connect(button_3, &QPushButton::clicked, this, &Widget::DealButton_3);

    //当语句在窗口一后时，出现的结果为先出现了窗口一再出现的窗口四。
    connect(button_1, &QPushButton::clicked, this, &Widget::DealButton_4);

    //当按下按钮四时，显示子窗口，父窗口关闭
    connect(button_4, &QPushButton::clicked, this, &Widget::Jump_To_Sub);

    //定义一个函数指针，funSignal是其指向无参数的Return_Parent，但记住，该指针需要加上作用域
    void (SubWidget::*funSignal)() = &SubWidget::Return_Parent;
    //定义一个函数指针，funSignal是其指向无参数的Deal_Return_Parent，但记住，该指针需要加上作用域
    void (Widget::*slot_1)() = &Widget::Deal_Return_Parent;
    //接收Return_Parent信号，并使用Deal_Return_Parent槽函数处理
    connect(&sub, funSignal, this, slot_1);

    void (SubWidget::*testSignal)(int, QString) = &SubWidget::Return_Parent;
    void (Widget::*slot_2)(int, QString) = &Widget::Deal_Return_Parent;
    connect(&sub, testSignal, this, slot_2);
}

void Widget::DealButton_1(){
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    dialog_1 = new QDialog();
    dialog_1->setWindowTitle("一号处理页面");
    dialog_1->setLayout(layout);
    QPushButton *Return =  new QPushButton("ok",this);
    layout->addWidget(Return);
    connect(Return, SIGNAL(clicked(bool)), dialog_1, SLOT(close()));
    dialog_1->show();
}

void Widget::DealButton_2(){
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    dialog_2 = new QDialog();
    dialog_2->setWindowTitle("二号处理页面");
    dialog_2->setLayout(layout);
    QPushButton *Return =  new QPushButton("OK",this);
    layout->addWidget(Return);
    connect(Return, SIGNAL(clicked(bool)), dialog_2, SLOT(close()));
    dialog_2->show();
}

void Widget::DealButton_3(){
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    dialog_3 = new QDialog();
    dialog_3->setWindowTitle("三号处理页面");
    dialog_3->setLayout(layout);
    QPushButton *Return = new QPushButton("ok",this);
    layout->addWidget(Return);
    connect(Return , &QPushButton::clicked, dialog_3, &QDialog::close);
    dialog_3->show();
}

void Widget::DealButton_4(){
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    dialog_4 = new QDialog();
    dialog_4->setWindowTitle("四号处理页面");
    dialog_4->setLayout(layout);
    QPushButton *Return = new QPushButton("ok",this);
    layout->addWidget(Return);
    connect(Return , &QPushButton::clicked, dialog_4, &QDialog::close);
    dialog_4->show();
}

void Widget::Jump_To_Sub(){
    //本窗口隐藏
    this->hide();
    //子窗口显示
    sub.show();
}

void Widget::Deal_Return_Parent(){
    //子串口关闭
    sub.close();
    //父窗口显示
    this->show();
}

void Widget::Deal_Return_Parent(int value, QString text){
    //toUtf8()将QString类转换为QByteArray，data()将QByteArray转换为char *即字符串
    //QString输出时会将""一起输出
    qDebug()<<value<<text.toUtf8().data();
}

Widget::~Widget()
{

}
