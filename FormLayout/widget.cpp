#include "widget.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    QGroupBox *form = new QGroupBox("FormLayout", this);
    QFormLayout *formlayout = new QFormLayout(this);

    //第一种方式添加方式
    QLabel *label[2];
    QLineEdit *edit[4];
    for(int i = 0 ; i < 2 ; i++){
        label[i] = new QLabel("Test", this);
        label[i]->setStyleSheet("border:2px solid red");
        edit[i] = new QLineEdit(this);
    }
    formlayout->addRow(label[0], edit[0]);
    formlayout->addRow(label[1], edit[1]);

    //第二种方式添加
    edit[2] = new QLineEdit(this);
    edit[3] = new QLineEdit(this);
    edit[2]->setMinimumWidth(150);
    edit[3]->setMinimumWidth(150);
    formlayout->addRow(tr("test"), edit[2]);
    formlayout->addRow(tr("test"), edit[3]);

    formlayout->setHorizontalSpacing(25);
    formlayout->setVerticalSpacing(25);
    //该语句是上述两种语句的结合
    formlayout->setSpacing(25);

    //使label在field之上。
//    formlayout->setRowWrapPolicy(QFormLayout::WrapAllRows);

    /*
     * Fields are always laid out next to their label. This is the default policy for all styles except Qt Extended styles.
     * field经常拜访在label旁边。不会因为空白区域空间不足而换行。
    */
//    formlayout->setRowWrapPolicy(QFormLayout::DontWrapRows);

    /*
     *Labels are given enough horizontal space to fit the widest label, and the rest of the space is given to the fields.
     * If the minimum size of a field pair is wider than the available space, the field is wrapped to the next line.
     * This is the default policy for Qt Extended styles.
     *
     * label被给与足够的水平空间适应最宽的label，剩余的空间给与field。如果field的最小宽度比可用空间
     * 小，field将被移动到下一行。
     */
    formlayout->setRowWrapPolicy(QFormLayout::WrapLongRows);

    form->setLayout(formlayout);
    mainlayout->addWidget(form);
    this->setMaximumWidth(100);
    this->setLayout(mainlayout);
}

Widget::~Widget()
{

}
