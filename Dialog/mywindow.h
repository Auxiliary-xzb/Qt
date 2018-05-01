#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QDialog>

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent = 0);
    ~MyWindow();

private:
    QDialog dialog;
};

#endif // MYWINDOW_H
