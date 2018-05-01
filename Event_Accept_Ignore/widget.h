#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mydialog.h"

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
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    Ui::Widget *ui;
    MyDialog *mydialog;
};

#endif // WIDGET_H
