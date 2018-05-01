#include "widget.h"
#include <QBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QStackedLayout>
#include <QGroupBox>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *test[11];
    for(int i = 0; i < 11; i++){
        test[i] = new QLabel("Test", this);
        test[i]->setStyleSheet("border:2px solid red");
    }

    QGroupBox *group_formlayout = new QGroupBox("FormLayout", this);
    //表格布局，以一行一行的方式添加，列数以其中组件数最大的一列为准,列的最大宽度以最大的为准。
    QFormLayout *formlayout = new QFormLayout(this);
    group_formlayout->setLayout(formlayout);

    QGroupBox *group_boxlayout_v = new QGroupBox("BoxLayout",this);
    //盒子布局，有垂直盒和水平盒两种，每种都有两种放入主键的方式。
    QBoxLayout *boxlayout_v = new QBoxLayout(QBoxLayout::TopToBottom, this);
    boxlayout_v->addWidget(test[1]);
    boxlayout_v->addWidget(test[2]);
    group_boxlayout_v->setLayout(boxlayout_v);

    QGroupBox *group_boxlayout_h = new QGroupBox("BoxLayout",this);
    QBoxLayout *boxlayout_h = new QBoxLayout(QBoxLayout::LeftToRight, this);
    boxlayout_h->addWidget(test[3]);
    boxlayout_h->addWidget(test[4]);
    group_boxlayout_h->setLayout(boxlayout_h);

    QGroupBox *group_gridlayout = new QGroupBox("GridLayout",this);
    //网格布局，又称栅格布局，可以控制组件的跨度。最小的跨度为1。
    QGridLayout *gridlayout = new QGridLayout(this);
    gridlayout->addWidget(test[5],0,0);
    gridlayout->addWidget(test[6],1,1);
    gridlayout->addWidget(test[7],2,2);
    //最小跨度为1，即组件本身的大小，当任意跨度设置为0时就不会显示该组件。
    gridlayout->addWidget(test[8],3,1,1,0);
    group_gridlayout->setLayout(gridlayout);

    QGroupBox *group_stackedlayout = new QGroupBox("StackedLayout",this);
    QBoxLayout *show =new QBoxLayout(QBoxLayout::BottomToTop,this);
    //每次只能显示一个页面，和combo类似，所以在这里设置了一个按钮用于换页，
    QStackedLayout *stackedlayout = new QStackedLayout(this);
    QPushButton *change = new QPushButton("切换到下一个标签",this);
    //设置要显示的页面，页面显示顺序与插入顺序相同。
    test[9]->setText("first page");
    test[10]->setText("second page");
    test[0]->setText("third page");
    stackedlayout->addWidget(test[9]);
    stackedlayout->addWidget(test[10]);
    stackedlayout->addWidget(test[0]);
    //设置group
    show->addLayout(stackedlayout);
    show->addWidget(change);
    //链接按钮和stackedlayout
    connect(change, &QPushButton::clicked,
            [ = ](){
        //获取页面总数
        int total_count = stackedlayout->count();
       //获取当前页的索引号
        int current_count = stackedlayout->currentIndex();
        current_count++;
        if(current_count >= total_count )
            current_count = 0;
        //更新当前页索引号
        stackedlayout->setCurrentIndex(current_count);
    });
    group_stackedlayout->setLayout(show);

    //向表格中添加行。
    formlayout->addRow(group_boxlayout_v, group_boxlayout_h);
    formlayout->addRow(group_gridlayout, group_stackedlayout);

    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->addWidget(group_formlayout);
    this->setLayout(mainlayout);
}

Widget::~Widget()
{

}
