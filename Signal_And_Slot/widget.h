#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QString>
#include "subwidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void DealButton_1();
    void DealButton_2();
    void DealButton_3();
    void DealButton_4();
    void Jump_To_Sub();
    void Deal_Return_Parent();
    //槽函数需要和信号一致（参数，返回值），槽函数和信号一样均可以重载
    void Deal_Return_Parent(int, QString);

private:
    QPushButton *button_1, *button_2, *button_3, *button_4, *button_5;
    QDialog *dialog_1, *dialog_2, *dialog_3, *dialog_4;
    SubWidget sub;
};

#endif // WIDGET_H
