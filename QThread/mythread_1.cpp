#include "mythread_1.h"
#include <QDebug>

MyThread_1::MyThread_1(QObject *parent) : QThread(parent)
{
    flag = true;
}

void MyThread_1::run(){
    while(flag){
        if(flag == false){
            break;
        }
        mutex.lock();
        //使用该语句描述
        this->sleep(1);
        emit threadDone();
        qDebug() << this->currentThreadId();
        mutex.unlock();
    }
}

/*
 * 其实可以用一个简单的方式退出，不需要QMutex，
 * 只需要设置flag的函数即可，要停止线程就设置为
 * true，否则为false。
 */
void MyThread_1::threadPause(){
    qDebug() << "线程已经停止";
    mutex.lock();
}

void MyThread_1::threadResume(){
    qDebug() << "线程重新启动";
    mutex.unlock();
}

void MyThread_1::threadStart(){
    this->start();
}

void MyThread_1::threadStop(){
    flag = false;
}
