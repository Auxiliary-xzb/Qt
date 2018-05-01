#include "mainwindow.h"
#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*
     * Closes all top-level windows.This function is particularly useful for applications
     *  with many top-level windows. It could, for example, be connected to a Exit entry in the File menu.
     *
     * 关闭所有的顶层窗口，这个函数在应用程序由很多顶层窗口时很有效，
     * 它可以和File菜单下的Exit实体相链接。
    */
    QObject::connect(&w, SIGNAL(Exit()), &a, SLOT(closeAllWindows()));

    QObject::connect(&w, &MainWindow::Restart,
                     [ & ]{
        a.closeAllWindows();
        /*
             * Starts the program program with the arguments arguments in a new process,
             * and detaches from it. Returns true on success; otherwise returns false.
             *  If the calling process exits, the detached process will continue to run unaffected.
             * Argument handling is identical to the respective start() overload.
             *
             *
             * 开启由program和argument指定的新进程，并且分离它（父子进程无关系）
             * 成功则返回true，否则返回false。如果需要启动的进程存在，则分离的进程
             * 将不受影响的继续运行。重载start()方法各个参数的处理时一致的。
             *
             *
             *
             * 所以重启的方式可以是先将该进程关闭，然后开启一个新的进程，
             * 新进程即为该进程的名字。
            */
        QProcess::startDetached(a.applicationFilePath(), QStringList());
    });
    return a.exec();
}
