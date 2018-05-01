#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPixmap icon_pixmap = QPixmap(":/new/prefix1/src/1.jpg");
    QIcon icon = QIcon(icon_pixmap);
    this->setWindowIcon(icon);
    ui->setupUi(this);

    //在UI工具中所有的对象都是指针类型
    connect(ui->actionAbout_Qt, &QAction::triggered,
            [ = ](){
        QMessageBox::aboutQt(this);
    });

    connect(ui->actionOpen, &QAction::triggered,
            [ = ](){
        QFileDialog::getOpenFileName(this, "Open", "../", tr("All File (*.*)"));
    });

    connect(ui->actionExit, &QAction::triggered,
            [ = ](){
        emit Exit();
    });

    connect(ui->actionRestart, &QAction::triggered,
            [ = ](){
        emit Restart();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
