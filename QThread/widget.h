#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QThread>
#include "mythread_1.h"
#include "mythread_2.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void deal_Timer_1();
    void deal_Timer_2();
    void deal_Thread_1();
    void deal_Thread_2();
    void deal_Destroy();

    void on_pushButton_Start_1_clicked();

    void on_pushButton_Start_2_clicked();

    void on_pushButton_Stop_1_clicked();

    void on_pushButton_Stop_2_clicked();

signals:
    void wakeThread();

protected:
//    void closeEvent(QCloseEvent *event);

private:
    Ui::Widget *ui;
    QTimer *timer_1, *timer_2;
    MyThread_1 *mythread_1;
    QThread *thread;
    MyThread_2 *mythread_2;
    bool isFirstTime, isFirstTime_1;
};

#endif // WIDGET_H
