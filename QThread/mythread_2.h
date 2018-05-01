#ifndef MYTHREAD_2_H
#define MYTHREAD_2_H

#include <QObject>
#include <QMutex>

class MyThread_2 : public QObject
{
    Q_OBJECT
public:
    explicit MyThread_2(QObject *parent = 0);

    void doWork();
    void threadStart();
    void threadPause();
    void threadResume();
    void threadStop();

signals:
    void workDone();

public slots:

private:
    bool flag;
    QMutex mutex;
};

#endif // MYTHREAD_2_H
