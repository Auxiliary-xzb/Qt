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
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:
    int count, count_2, click_times, click_times_2, timer_id, timer_id2;

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
