#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

protected:
    //重写绘图事件，虚函数
    /*
     * 如果在窗口绘图，必须放在绘图事件里实现
     * 绘图事件在窗口需要重绘的时候，内部自动调用，也可手动刷新
    */
    void paintEvent(QPaintEvent *event);

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    int x;
};

#endif // WIDGET_H
