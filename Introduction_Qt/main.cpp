#include "widget.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    //有且只有一个应用程序类的对象
    QApplication a(argc, argv);

    /*
     * Widget继承QWidget，QWidget是一个窗口类的基类
     *
     * 每个窗口需要调用show方法才能显示。
    */
    Widget w;
    w.setWindowTitle(QString("黄鑫"));
    w.show();

    /*
     * 如果不指定父对象，对象和对之间（窗口和窗口）就没有关系
     * a指定b为它的父对象，a放在b的上面
     * 指定父对象，有两种方式：
     *          1.setParent
     *          2.通过构造函数传参
     * 指定父对象，只需要父对象显示，上面的子对象就会自动显示。
     */

    QPushButton button;
    button.setText("黄鑫");
    //在未指定父对象前，该button为单独窗口显示
    button.setParent(&w);
    button.show();
    //消息处理
    return a.exec();
}
