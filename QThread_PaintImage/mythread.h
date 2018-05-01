#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <QBrush>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);

    void threadDrawImage();

signals:
    void drawDone(QImage *image);

public slots:

public:
    QImage *image;
    QPainter *painter;
    QPen pen;
    QBrush brush;
};

#endif // MYTHREAD_H
