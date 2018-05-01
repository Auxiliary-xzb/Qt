#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QString>

class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = 0);

private:
    QPushButton *button;

signals:
    /*
     * 信号必须有signals关键字声明
     * 信号没有返回值，但可以有参数
     * 信号就是函数的声明，只需声明，无需定义
     * 使用:emit MySignal();
     * 信号可以重载，可以带参数。
    */
    void Return_Parent();
    void Return_Parent(int, QString);
public slots:
    void SendSignal();
};

#endif // SUBWIDGET_H
