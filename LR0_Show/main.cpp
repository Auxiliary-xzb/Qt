#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(QString("构造LR0分析表"));
    MyWidget w;
    w.show();

    return a.exec();
}
