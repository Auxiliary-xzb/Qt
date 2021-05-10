#include "mywindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QDialog>
#include <QDebug>

MyWindow::MyWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *menubar = menuBar();
    this->setMenuBar(menubar);
    QMenu *menu = menubar->addMenu("File");

    /*
     * ----------------------------------------------------------------------
     *  使用第一种方法，在lambda内部创建临时变量，但是此时
     *  对于非模态对话框的一闪而过的情况则需要使用new。
        */
    QMenu *approach_4 = new QMenu("方案四");
    menu->addMenu(approach_4);
    QAction *modal_4 = approach_4->addAction("模态对话框");
    QAction *umodal_4 = approach_4->addAction("非模态对话框");

    //模态对话框是只能操作当前窗口，其他不行
    connect(modal_4, &QAction::triggered,
            [ = ](){
        QDialog modal;
        modal.setWindowTitle("模态对话框");
        modal.setModal(true);

        QPushButton *Return = new QPushButton(&modal);
        Return->setText("return");

        connect(Return, &QPushButton::clicked,
                [ & ](){
            modal.close();
        });

        modal.exec();
    }
    );

    //非模态对话框是都可以操作
    connect(umodal_4, &QAction::triggered,
            [ = ](){
        //为了防止对话框一闪而过，要将其创建在堆区
        //因为在lambda中执行完了，临时变量就别释放了
        QDialog umodal;
        umodal.setWindowTitle("非模态对话框");
        umodal.setModal(false);

        QPushButton Return(&umodal);
        Return.setText("return");

        connect(&Return, &QPushButton::clicked,
                [ & ](){
            umodal.close();
        });

        umodal.show();
    });

    /*
     * ----------------------------------------------------------------------
        */


    /*
     * ----------------------------------------------------------------------
     *  改进第一种方法，在模态和非模态时都在lambda函数中
     *  new一个对话框。这样就不会一闪而过了。但是带来是
     *  内存泄露的问题。
        */
    QMenu *approach = new QMenu("方案一");
    menu->addMenu(approach);
    QAction *modal_1 = approach->addAction("模态对话框");
    QAction *umodal_1= approach->addAction("非模态对话框");

    //模态对话框是只能操作当前窗口，其他不行
    connect(modal_1, &QAction::triggered,
            [ = ](){
        //为了防止对话框一闪而过，要将其创建在堆区
        //因为在lambda中执行完了，临时变量就别释放了
        QDialog *modal= new QDialog(this);
        modal->setWindowTitle("模态对话框");
        modal->setModal(true);

        QPushButton *Return = new QPushButton(modal);
        Return->setText("return");

        connect(Return, &QPushButton::clicked,
                [ = ](){
            modal->close();
        });

        modal->exec();
    }
    );

    //非模态对话框是都可以操作
    connect(umodal_1, &QAction::triggered,
            [ = ](){
        //为了防止对话框一闪而过，要将其创建在堆区
        //因为在lambda中执行完了，临时变量就别释放了
        QDialog *umodal = new QDialog(this);
        umodal->setWindowTitle("非模态对话框");
        umodal->setModal(false);

        QPushButton *Return = new QPushButton(umodal);
        Return->setText("return");

        connect(Return, &QPushButton::clicked,
                [ = ](){
            umodal->close();
        });

        umodal->show();
    });

    /*
     * ----------------------------------------------------------------------
        */

    /*
     * 以上方案存在问题：
     *      1.在每次点击时都会分配空间，但没有释放空间
     *          存在内存泄漏问题。
     *
     * 解决方案：
     *      1.将对话框对象作为主窗口的成员变量，由主窗口控制它的
     *          释放。
     *      2.仍然在使用时创建对话框对象，但是设置其属性为关闭对
     *          话框时释放对象。
        */


    /*
     * ----------------------------------------------------------------------
     * 解决方案一：将对话框做为主窗口的对象让其控制其释放。
        */
    QMenu *approach_2 = new QMenu("方案二");
    menu->addMenu(approach_2);
    QAction *modal_2 = new QAction("模态对话框", approach_2);
    QAction *umodal_2 = new QAction("非模态对话框", approach_2);
    approach_2->addAction(modal_2);
    approach_2->addAction(umodal_2);

    connect(modal_2, &QAction::triggered,
            [ & ](){
        /*
             * 将对话框作为类的成员变量，那么dialog的生命周期和
             * 该类对象相同，在windows对象的被释放时一起释放。
            */
        this->modal.setWindowTitle("模态对话框");
        this-> modal.setModal(true);

        QPushButton *Return = new  QPushButton(&this->modal);
        Return->setText("return");

        connect(Return, &QPushButton::clicked,
                [ & ](){
            this->modal.close();
        });

        this->modal.show();
    });

    connect(umodal_2, &QAction::triggered,
            [ & ](){
        /*
             * 将对话框作为类的成员变量，那么dialog的生命周期和
             * 该类对象相同，在windows对象的被释放时一起释放。
            */
        this->umodal.setWindowTitle("非模态对话框");
        this->umodal.setModal(false);

        QPushButton *Return = new  QPushButton(&this->umodal);
        Return->setText("return");

        connect(Return, &QPushButton::clicked,
                [ & ](){
            this->umodal.close();
        });

        this->umodal.show();
    });

    /*
     * ----------------------------------------------------------------------
        */


    /*
     * ----------------------------------------------------------------------
     * 解决方案二：设置对话框的属性值为关闭时释放。
        */
    QMenu *approach_3 = new QMenu("方案三");
    menu->addMenu(approach_3);
    QAction *modal_3 = approach_3->addAction("模态对话框");
    QAction *umodal_3 = approach_3->addAction("非模态对话框");

    connect(modal_3, &QAction::triggered,
            [ = ](){
        /*
             * 在方案一中，因为没有在对话框关闭后释放空间，
             * 所以带来内存泄漏的隐患，因此可以设置在每次
             * 关闭窗口时释放它的内存。
            */
        QDialog *modal = new QDialog(this);
        modal->setWindowTitle("模态对话框");
          //设置属性，在对话框关闭时就释放其空间
        modal->setAttribute(Qt::WA_DeleteOnClose);
        modal->setModal(true);

        QPushButton *Return = new QPushButton(modal);
        Return->setText("return");

        connect(Return, &QPushButton::clicked,
                [ = ](){
            modal->close();
        });

        modal->show();
    });

    connect(umodal_3, &QAction::triggered,
            [ = ](){
        /*
             * 在方案一中，因为没有在对话框关闭后释放空间，
             * 所以带来内存泄漏的隐患，因此可以设置在每次
             * 关闭窗口时释放它的内存。
            */
        QDialog *umodal = new QDialog(this);
        umodal->setWindowTitle("非模态对话框");
        //设置属性，在对话框关闭时就释放其空间
        umodal->setAttribute(Qt::WA_DeleteOnClose);
        umodal->setModal(false);

        QPushButton *Return = new QPushButton(umodal);
        Return->setText("return");

        connect(Return, &QPushButton::clicked,
                [ = ](){
            umodal->close();
        });

        umodal->show();
    });

    /*
     * ----------------------------------------------------------------------
        */
}


MyWindow::~MyWindow()
{

}
