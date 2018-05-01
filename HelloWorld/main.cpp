#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("the first Qt work");

    //所有的窗口默认在创建时都是隐藏的，所以要调用方法显示,在java中也是这样
    //两者相等
    w.show();
    w.setVisible(true);
    w.setFixedSize(500, 500);
    return a.exec();
}
