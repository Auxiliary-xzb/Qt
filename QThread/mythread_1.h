#ifndef MYTHREAD_1_H
#define MYTHREAD_1_H

#include <QThread>
#include <QMutex>

class MyThread_1 : public QThread
{
    Q_OBJECT
public:
    explicit MyThread_1(QObject *parent = 0);

    void run();
    void threadPause();
    void threadResume();
    void threadStop();
    void threadStart();
    void setFlag(bool value);

signals:
    void threadDone();

public slots:

public:
    QMutex mutex;
    bool flag;
};

#endif // MYTHREAD_1_H
