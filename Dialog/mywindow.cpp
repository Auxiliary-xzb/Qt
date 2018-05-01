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
    QMenu *approach = new QMenu("方案一");
    menu->addMenu(approach);
    QAction *Modal = approach->addAction("模态对话框");
    QAction *UModal = approach->addAction("非模态对话框");

    //模态对话框是只能操作当前窗口，其他不行
    connect(Modal, &QAction::triggered,
            [ = ](){
        QDialog *modal= new QDialog(this);
        QPushButton *Return = new QPushButton(modal);
        Return->setText("return");
        modal->setWindowTitle("模态对话框");
        modal->setModal(true);
        modal->show();
        connect(Return, &QPushButton::clicked,
                [ = ](){
            modal->close();
        });
    }
    );

    //非模态对话框是都可以操作
    connect(UModal, &QAction::triggered,
            [ = ](){
        QDialog *umodal = new QDialog(this);
        QPushButton *Return = new QPushButton(umodal);
        Return->setText("return");
        umodal->setWindowTitle("非模态对话框");
        umodal->setModal(false);
        umodal->show();
        connect(Return, &QPushButton::clicked,
                [ = ](){
            umodal->close();
        });
    });

    /*
     * 以上方案存在问题：
     *      1.两种对话框都是动态分配空间，在动态创建时指定了父对象，
     *          那么只有在父对象被释放时，它才会释放。
     *      2.在每次点击时都会分配空间，那么就存在内存泄漏问题
     *
     * 解决方案：
     *      1.由于上述是指定了父对象，所以将对话框做为其成员变量，
     *          那么只有在父对象消失后，成员变量才会消失。
     *      2.在每次分配完空间后，当对话框被关闭时就释放其空间。
        */
    QMenu *approach_2 = new QMenu("方案二");
    menu->addMenu(approach_2);
    QAction *modal_2 = new QAction("模态对话框", approach_2);
    QAction *umodal_2 = new QAction("非模态对话框", approach_2);
    approach_2->addAction(modal_2);
    approach_2->addAction(umodal_2);

    connect(modal_2, &QAction::triggered,
            [ = ](){
        QDialog dialog_1;
        QPushButton *Return = new QPushButton(&dialog_1);
        Return->setText("return");
        dialog_1.setWindowTitle("模态对话框");
        connect(Return, &QPushButton::clicked,
                [ & ](){
            dialog_1.close();
        });
        //只有在关闭了之后才会显示下面的字符串
        dialog_1.exec();
        qDebug() <<"1111";
    });

    connect(umodal_2, &QAction::triggered,
            [ = ](){
        /*
             * 如果使用以下方法，那么在lambda体执行完之后，对话框就不会再显示了
             * 因为这里的QDialog只是一个函数内的变量，函数体执行完后该对象就被
             * 释放了。
             * 所以为了解决以上问题，就应该讲QDialog作为该类的成员函数。
            */
        dialog.setWindowTitle("非模态对话框");
        QPushButton *Return = new QPushButton(&dialog);
        Return->setText("return");
        connect(Return, &QPushButton::clicked,
                [ = ](){
            dialog.close();
        });
        //它会在出现时就显示222
        dialog.show();
        qDebug() << "222";
    });

    QMenu *approach_3 = new QMenu("方案三");
    menu->addMenu(approach_3);
    QAction *modal_3 = approach_3->addAction("模态对话框");
    QAction *umodal_3 = approach_3->addAction("非模态对话框");

    connect(modal_3, &QAction::triggered,
            [ = ](){
        QDialog dialog_1;
        QPushButton *Return = new QPushButton(&dialog_1);
        Return->setText("return");
        dialog_1.setWindowTitle("模态对话框");
        connect(Return, &QPushButton::clicked,
                [ & ](){
            dialog_1.close();
        });
        //只有在关闭了之后才会显示下面的字符串
        dialog_1.exec();
        qDebug() <<"1111";
    });

    connect(umodal_3, &QAction::triggered,
            [ = ](){
        /*
             * 在方案一中，因为没有在对话框关闭后释放空间，
             * 所以带来内存泄漏的隐患，所以在每次创建完空间
             * 后就需要在关闭时释放。
            */
        QDialog *mydialog = new QDialog(this);
        mydialog->setWindowTitle("非模态对话框");
        //设置属性，在对话框关闭时就释放其空间
        mydialog->setAttribute(Qt::WA_DeleteOnClose);

        //在这个位子写这句话后面的按钮就显示不了了    mydialog->show();
        qDebug() << "123123";
        QPushButton *Return = new QPushButton(mydialog );
        Return->setText("return");
        connect(Return, &QPushButton::clicked,
                [ = ](){
            mydialog->close();
        });
        mydialog->show();
    });


}

MyWindow::~MyWindow()
{

}
