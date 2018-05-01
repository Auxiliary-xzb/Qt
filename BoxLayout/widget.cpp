#include "widget.h"
#include <QFormLayout>
#include <QLabel>
#include <QGroupBox>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *test[18];
    for(int i = 0 ; i < 18 ; i++){
        test[i] = new QLabel("test", this);
        test[i]->setStyleSheet("border:2px solid red");
    }

    QFormLayout *mainlayout = new QFormLayout(this);
    this->setLayout(mainlayout);

    QGroupBox *boxlayout_v = new QGroupBox("BoxLayout_TopToBottom", this);
    QBoxLayout *layout_v = new QBoxLayout(QBoxLayout::TopToBottom,this);
    layout_v->addWidget(test[0]);
    layout_v->addWidget(test[1]);
    boxlayout_v->setLayout(layout_v);

    QGroupBox *boxlayout_h = new QGroupBox("BoxLayout_LeftToRight", this);
    QBoxLayout *layout_h = new QBoxLayout(QBoxLayout::LeftToRight, this);
    layout_h->addWidget(test[2]);
    layout_h->addWidget(test[3]);
    boxlayout_h->setLayout(layout_h);

    QGroupBox *vboxlayout = new QGroupBox("QVBoxLayout",this);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(test[4]);
    vlayout->addWidget(test[5]);
    vboxlayout->setLayout(vlayout);

    QGroupBox *hboxlayout = new QGroupBox("QHBoxLayout", this);
    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->addWidget(test[6]);
    hlayout->addWidget(test[7]);
    hboxlayout->setLayout(hlayout);

    /*
     * addSpacing是在部件的结尾处添加空白。
    */
    QGroupBox *addspacing = new QGroupBox("addSpacing", this);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addSpacing(100);
    test[8]->setText(tr("左侧有100dip的空白区域"));
    layout->addWidget(test[8]);
    test[9]->setText(tr("右侧有100dip的空白区域"));
    layout->addWidget(test[9]);
    layout->addSpacing(100);
    addspacing->setLayout(layout);

    /*
     * setSpacing是在部件之间添加空白。
    */
    QGroupBox *setspacing = new QGroupBox("setSapcing", this);
    QVBoxLayout *layout_1 = new QVBoxLayout(this);
    QHBoxLayout *layout_2 = new QHBoxLayout(this);
    QHBoxLayout *layout_3 = new QHBoxLayout(this);
    test[10]->setText("在相邻的部件之间添加空白");
    layout_2->addWidget(test[10]);
    layout_2->addWidget(test[11]);
    layout_1->addLayout(layout_2);
    test[12]->setText(tr("在两个layout间也可以添加空白"));
    layout_3->addWidget(test[12]);
    layout_3->addWidget(test[13]);
    layout_1->addLayout(layout_3);
    layout_2->setSpacing(100);
    layout_1->setSpacing(100);
    setspacing->setLayout(layout_1);

    /*
     *addLayout是在最后一个盒子的末尾添加新的layout。
    */
    QGroupBox *addlayout = new QGroupBox("addLayout", this);
    QHBoxLayout *end = new QHBoxLayout(this);
    QVBoxLayout *v_layout = new QVBoxLayout(this);
    v_layout->addWidget(test[14]);
    v_layout->addWidget(test[15]);
    end->addLayout(v_layout);
    QHBoxLayout *h_layout = new QHBoxLayout(this);
    h_layout->addWidget(test[16]);
    h_layout->addWidget(test[17]);
    end->addLayout(h_layout);
    addlayout->setLayout(end);

    QGroupBox *addstretch = new QGroupBox("addStretch", this);
    QVBoxLayout *lay = new QVBoxLayout(this);
    QPushButton *stretch = new QPushButton("addStretch", this);

    add = new AddStretch();
    add->hide();
    connect(stretch, &QPushButton::clicked,
            [ & ](){
        this->hide();
        add->show();
    });

    connect(add, &AddStretch::Return,
            [ = ](){
        this->show();
        add->hide();
    });

    connect(add, &AddStretch::Close,
            [ = ](){
        this->show();
    });
    lay->addWidget(stretch);
    addstretch->setLayout(lay);

    mainlayout->addRow(boxlayout_v, vboxlayout);
    mainlayout->addRow(boxlayout_h, hboxlayout);
    mainlayout->addRow(addspacing);
    mainlayout->addRow(setspacing);
    mainlayout->addRow(addlayout);
    mainlayout->addRow(addstretch);
}

Widget::~Widget()
{

}
