#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Returns a list of all the available database drivers.
    //返回所有支持的数据库驱动
    QStringList list = QSqlDatabase::drivers();
    for(int i = 0; i < list.count() ; i++){
        ui->textEdit_Show->append(static_cast<QString>(list.at(i)).toUtf8().data());
    }

    //添加数据库
    /*
     * 这里没有链接上因为mariadb是64位的，但是qt是32位的。
     *
     * 链接时需要对应数据库的动态链接库。
     * 将  数据库安装目录/lib/libxxx.dll 文件放入到
     *      {Qt安装目录/5.6.3}/mingw49_32/bin目录下。
        */
    //Adds a database to the list of database connections
    //添加一个数据库到一个数据库链接。
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //链接数据库
    db.setHostName("127.0.0.1");    //数据库服务器IP
    db.setUserName("root");         //数据库进入身份
    db.setPassword("123");          //数据库进入密码
    db.setDatabaseName("mysql");    //选择数据库

    if( !db.open() ){
        QMessageBox::warning(this, tr("Warning"), tr("Can't connect database"));
        return;
    }

    QSqlQuery query;
    query.exec("select * from student");
    while(query.next()){
        qDebug() << query.value(0).toString().toInt()
                 << query.value(1).toString().toUtf8().data()
                 << query.value(2).toString().toInt()
                 << query.value(3).toString().toInt();
    }
}

Widget::~Widget()
{
    delete ui;
}
