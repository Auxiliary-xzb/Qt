#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::Widget *ui;
    int isLeftButtonPressed;
    QPoint beginMousePosition, currentMousePosition;    //初始鼠标坐标，当前鼠标坐标
    QPoint beginTopLefCorner, currentTopLeftCorner;    //初始左上角坐标，当前左上角坐标
};

#endif // WIDGET_H
