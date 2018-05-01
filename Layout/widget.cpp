#include "widget.h"
#include <QLayout>
#include <QGridLayout>
#include <QDebug>
#include <QAction>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(200,300);
    /*
        QBoxLayout *bottom = new QBoxLayout(QBoxLayout::BottomToTop,this);

        在这里卡了很久，一开并没有理会下面的警告信息：
        QLayout: Attempting to add QLayout "" to Widget "", which already has a layout

        这个信息是说，此对象已经拥有了一个布局了，因为你是用这个对象去创建的布局，因此后面再用这个此对象
        去创建布局就是错的

        应该让这个布局不属于任何一个父对象，就当成widget这个类的构造函数，那么在new一个wigdet对象时就
        会直接成为他的布局内容
    */

    /*
     *  箱子布局，可以选择箱子的方向
    */
    QBoxLayout *bottom = new QBoxLayout(QBoxLayout::BottomToTop);
    /*
     *  QTextEdit是多行文本框
     *  QLineEdit是单行文本框
    */
    content = new QTextEdit();
    /*
     *  设置多行文本框的内容
    */
    content->setPlainText("hahha");

    bottom->addWidget(content);
    groupbox_1 = new QGroupBox("group box");
    groupbox_1->setLayout(bottom);

    /*
     *  表格布局，就是上到下一行一行的
    */
    QGridLayout *mid = new QGridLayout();
    /*
     *  标签，和java的标签类似
    */
    txt_1 = new QLabel("&line_1:");
    txt_2 = new QLabel("&line_2:");
    txt_3 = new QLabel("&line_3:");
    /*
     *  单行文本框
    */
    line_1 = new QLineEdit(),
    line_2 = new QLineEdit(),
    line_3 = new QLineEdit();

    txt_1->setBuddy(line_1);
    txt_2->setBuddy(line_2);
    txt_3->setBuddy(line_3);
    mid->addWidget(txt_1, 1, 1);
    mid->addWidget(txt_2, 2, 1);
    mid->addWidget(txt_3, 3, 1);
    mid->addWidget(line_1,1, 2);
    mid->addWidget(line_2, 2, 2);
    mid->addWidget(line_3, 3, 2);
    /*
     *  QGroupBox 也是一个widget，所以应该是给它设置布局，
     * 而不是在布局中加入它。最后只需要把整体加入mainwidget的布局就可以了
    */
    groupbox_2 = new QGroupBox("group box");
    groupbox_2->setLayout(mid);

    QBoxLayout *top = new QBoxLayout(QBoxLayout::LeftToRight);
    icon = new QIcon("://20.jpg");
    button_1 = new QPushButton(*icon,"&bottom_1"),
    button_2 = new QPushButton(*icon,"&bottom_2"),
    button_3 = new QPushButton("&bottom_3");
    button_3->setIcon(*icon);
    top->addWidget(button_1);
    top->addWidget(button_2);
    top->addWidget(button_3);
    groupbox_3 = new QGroupBox("group box");
    groupbox_3->setLayout(top);

    QBoxLayout *back = new QBoxLayout(QBoxLayout::BottomToTop);
    back->addWidget(groupbox_1);
    back->addWidget(groupbox_2);
    back->addWidget(groupbox_3);

    setLayout(back);
}

Widget::~Widget()
{

}
