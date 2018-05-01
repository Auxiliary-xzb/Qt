#include "widget.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QDebug>

/*
 * 在QGridLayout中行与列有相同的性质。
*/
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *label[12];
    for(int i = 0 ; i < 12 ; i++){
           label[i] = new QLabel("test", this);
           label[i]->setStyleSheet("border:2px solid red");
    }
    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->setDirection(QBoxLayout::BottomToTop);
    /*
     * 本列说明了，列的宽度最小值是在该列的所有部件的宽度最小值集
     * 合和使用了setColumnMinimumWidth()设置的值，这些值中找到最大
     * 的一个作为最终该列的最小宽度。
     * 由于行和列拥有相同的性质，所以行的高度也是如此。
    */
    QGroupBox *group_gridlayout = new QGroupBox("Column Width", this);
    QGridLayout *gridlayout = new QGridLayout(this);
    label[0]->setText("该列最小宽度设置为50");
    label[0]->setMinimumWidth(80);
    label[1]->setText(tr("本Label(Widget)最小宽度为100"));
    label[1]->setMinimumWidth(100);
    gridlayout->addWidget(label[0],0,0);
    gridlayout->addWidget(label[1],1,0);
    gridlayout->setColumnMinimumWidth(0, 50);
    qDebug()<<gridlayout->columnMinimumWidth(0) <<label[1]->minimumWidth();

    /*
     * 在QGridLayout的帮助文档中有如下语句：
     *      Do not use this function to add child layouts or child widget items.
     * 在QLayout的帮助文档中有如下语句：
     *      This function is not usually called in application code.
     *
     * 所以就不要这个了。
       */
    QGroupBox *additem = new QGroupBox("addItem", this);
    QGridLayout *lay = new QGridLayout(this);
    label[2]->setText("帮助文档说不要使用该函数去添加东西，所以就不写了");
    //记住，wrap在计算机中就是换行的意思
    label[2]->setWordWrap(true);
    lay->addWidget(label[2],0,0);
    additem->setLayout(lay);

    /*
     * 添加跨行的部件时需要注意，跨度的最小值为1，表示该部件跨越一列，
     * 即填充该列。
    */
    QGroupBox *multiple_cell = new QGroupBox("跨越多个cell", this);
    QGridLayout *out = new QGridLayout(this);
    out->addWidget(label[3], 0, 0);
    out->addWidget(label[4], 1, 0, 1, 1);
    out->addWidget(label[5], 1, 1);
    out->addWidget(label[6], 1, 2);
    out->addWidget(label[7], 2, 1, 1, 3);
    label[8]->setText(tr("跨越三行"));
    out->addWidget(label[8], 3, 0, 3, 1);
    out->addWidget(label[11], 3, 1);
    out->addWidget(label[9], 4, 1);
    out->addWidget(label[10], 5, 1);
    multiple_cell->setLayout(out);

    group_gridlayout->setLayout(gridlayout);
    mainlayout->addWidget(group_gridlayout);
    mainlayout->addWidget(additem);
    mainlayout->addWidget(multiple_cell);
    this->setLayout(mainlayout);
}

Widget::~Widget()
{

}
