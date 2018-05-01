#include "mythread_2.h"
#include <QThread>
#include <QDebug>

MyThread_2::MyThread_2(QObject *parent) : QObject(parent)
{
    /*
     * 该种创建线程的方式有以下几点注意的：
     *  1.必须让该类继承自QObject。
     *  2.必在创建该类是不能指定父对象
     *  3.需要在主线程中创建一个QThread类对象
     *  4.必须调用moveToThread()函数将自己的线程加入到QThread对象中。
     *  5.必须通过调用槽函数的方式去调用线程的操作
    */
    flag = false;
}

void MyThread_2::doWork(){
    while(!flag){
        if(flag){
            break;
        }
        mutex.lock();
        QThread::sleep(1);
        qDebug() << QThread::currentThreadId();
        emit workDone();
        mutex.unlock();
    }
}

void MyThread_2::threadPause(){
    mutex.lock();
    qDebug() << "子线程暂停";
}

void MyThread_2::threadResume(){
    mutex.unlock();
    qDebug() << "子线程重启";
}

void MyThread_2::threadStop(){
    flag = true;
}
