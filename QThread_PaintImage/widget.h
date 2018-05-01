#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include <QImage>
#include <QPainter>
#include "mythread.h"

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

signals:
    void wakePaint();

private slots:
    void dealImage(QImage *image);
    void dealClose();

    void on_pushButton_DrawImage_clicked();

private:
    Ui::Widget *ui;
    QThread *thread;
    MyThread *mythread;
    QPainter *painter;
    QImage *receive_image;
};

#endif // WIDGET_H
