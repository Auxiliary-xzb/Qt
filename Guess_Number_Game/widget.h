#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMovie>

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
    void on_pushButtonStart_clicked();
    void on_pushButtonEnd_clicked();
    void on_pushButton_Hint_clicked();
    void deal_Number();
    void on_pushButton_Submit_clicked();
    void whetherRestart();

    void on_pushButton_BackSpace_clicked();

protected:
    void timerEvent(QTimerEvent *event);

private:
    Ui::Widget *ui;

    int time;                                            //用户选择的游戏时间
    int startTimerId;                               //游戏时间定时器
    int overTimerId;                               //失败动画定时器
    int winTimerId;                                //成功动画定时器
    int minNumber;                               //最小数字
    int maxNumber;                              //最大数字
    QString inputNumber, randNumber;   //输入结果数，系统产生的随机数
    QMovie *failMovie, *winMovie;       //失败动画，成功动画
};

#endif // WIDGET_H
