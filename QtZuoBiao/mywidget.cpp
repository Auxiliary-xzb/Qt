#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    /*
     * 主窗口的坐标是相对于整个屏幕的，也就是说主窗口的父对象为整个屏幕
     *原点：屏幕的左上角的坐标为（0，0）
     * x轴：从左至右，依次递增
     * y轴：从上至下，依次递增
    */
    this->move(100, 100);

    /*
     *      由于子窗口在未指定父对象时是独立的窗口，当其指定父对象后，会在父对
     * 象中显示。所以子窗口的坐标是相对于父窗口的。
     * 原点：相对于窗口空白区域左上角（不包括边框）
     *x轴：从左至右，依次递增
     * y轴：从上至下，依次递增
    */
    button_1 = new QPushButton(this);
    button_1->setText("shit");
    button_1->move(100, 100);
    button_1->resize(200, 200);

    button_2 = new QPushButton(button_1);
    button_2->setText("fuck");
    button_2->move(50, 100);
}

MyWidget::~MyWidget()
{

}
