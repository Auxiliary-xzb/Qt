#include "mywidget.h"
#include <QSlider>
#include <QHBoxLayout>
#include <QSpinBox>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    QSpinBox *spin = new QSpinBox(this);
    QSlider *slider = new QSlider(Qt::Horizontal, this);

    /*
     * 不指定父对象时，需要自己调用setLayout，
     * 指定时则不需要setLayout，指定的对象的layout会自动设置成该layout
     * 例如：
     *      QHBoxLayout *mainlayout = new QHBoxLayout(this);
     * 表示this的layout已经设置成了mainlayout。
    */
    QHBoxLayout *mainlayout = new QHBoxLayout;
    mainlayout->addWidget(spin);
    mainlayout->addWidget(slider);
    this->setLayout(mainlayout);

   /*
    * 因为valueChanged()这个信号有两种，所以要指明是调用的哪一种
    * 方法一：
    * 使用函数指针的方式指明调用的是参数类型为int的信号。
    *       void (QSpinBox::*func)(int) = &QSpinBox::valueChanged;
    * 方法二：
    * 使用强制类型转换将返回的结果转换为参数为int的类型。
    *       static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged)
    *
    */
    connect(spin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), slider, &QSlider::setValue);

    connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);
}
