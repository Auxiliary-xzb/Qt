#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mypiece.h"

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
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::Widget *ui;
    int boxWidth, boxHeight;        //一个方格的高度和宽度
    int locateX, locateY;                //鼠标所在的方格位置
    MyPiece *piece;
};

#endif // WIDGET_H
