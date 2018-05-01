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
    int count, click_times, click_times_2, id, count_2,timer_id;

private:
    Ui::Widget *ui;
    QTimer *timer;
};

#endif // WIDGET_H
