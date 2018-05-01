#include "widget.h"
#include <QStackedLayout>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QComboBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *label[6];
    for(int i = 0 ; i < 6 ; i++){
        label[i] = new QLabel("test", this);
        label[i]->setStyleSheet("border:2px solid red");
    }

    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->setDirection(QVBoxLayout::BottomToTop);

    /*
     * 使用button来实现QStackedLayout的变化。
    */
    QGroupBox *stacked = new QGroupBox("QStackedLayout的Button变换", this);
    QVBoxLayout *out = new QVBoxLayout(this);
    out->setDirection(QVBoxLayout::TopToBottom);
    QPushButton *button = new QPushButton("Next", this);
    QWidget *widget = new QWidget(this);
    QStackedLayout *lay = new QStackedLayout(this);
    label[0]->setText("Page One");
    label[1]->setText("Page Two");
    label[2]->setText("Page Three");
    lay->addWidget(label[0]);
    lay->addWidget(label[1]);
    lay->addWidget(label[2]);
    widget->setLayout(lay);
    out->addWidget(widget);
    out->addWidget(button);
    stacked->setLayout(out);
    connect(button, &QPushButton::clicked,
            [ = ](){
        int count_index = lay->count();
        int current_index = lay->currentIndex();
        //点击后，页面的索引加1，即到下一张。
        current_index++;
        //如果索引加了后超过了最大的索引总值，则显示第一页，即索引为0的页。
        if(current_index >= count_index )
            current_index = 0;
        lay->setCurrentIndex(current_index);
    });

    /*
     * 结合combo box的QStackedLayout变换
    */
    QGroupBox *combo = new QGroupBox("QStackedLayout的Combo Box的变换", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QWidget *w = new QWidget(this);
    QStackedLayout *mystacked = new QStackedLayout;
    QComboBox *box = new QComboBox(this);
    box->addItem(tr("One"));
    box->addItem(tr("Two"));
    box->addItem(tr("Three"));
    label[3]->setText(tr("Page One"));
    label[4]->setText(tr("Page Two"));
    label[5]->setText(tr("Page Three"));
    mystacked->addWidget(label[3]);
    mystacked->addWidget(label[4]);
    mystacked->addWidget(label[5]);
    /*
     * This signal is sent when the user chooses an item in the combobox.
     * The item's index is passed. Note that this signal is sent even when the
     *  choice is not changed. If you need to know when the choice actually
     *  changes, use signal currentIndexChanged().
     *
     * 当用户选择了combobox中的一个项目时信号发出。项目的索引值被刷新。
     *注意信号甚至会在选择为改变时发出，如果你必须知道什么选择在某时
     * 是否改变，使用currentIndexChanged()信号。
      */
    void (QComboBox::*func)(int) = &QComboBox::activated;
    connect(box, func, mystacked, &QStackedLayout::setCurrentIndex);
    w->setLayout(mystacked);
    layout->addWidget(w);
    layout->addWidget(box);
    combo->setLayout(layout);

    mainlayout->addWidget(stacked);
    mainlayout->addWidget(combo);
    this->setLayout(mainlayout);
}

Widget::~Widget()
{

}
