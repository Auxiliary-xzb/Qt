#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "jumppage.h"

//Widget继承了QWidget这个类
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void DealSolts();
    void DealSignals();

private:
    QPushButton close_button;
    QPushButton jump_button;

    JumpPage SubPage;
};

#endif // WIDGET_H
