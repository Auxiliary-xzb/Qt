#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "addstretch.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void addstretch();

private slots:
private:
    AddStretch *add;

};

#endif // WIDGET_H
