#include "widget.h"
#include "ui_widget.h"
#include <QBuffer>
#include <QDebug>
#include <QDataStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //该构造器默认创建了一个QByteArray对象
    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);

    //当转换为char *时\n就会当做字符直接显示
    buffer.write("11111111111\n");
    buffer.write("22222222222");

    buffer.close();

    qDebug() << buffer.buffer().data();

    QByteArray array;
    //指定与QBuffer相关的QByteArray。
    QBuffer memFile(&array);
    memFile.open(QBuffer::WriteOnly);
    memFile.write("121212121212\n");
    memFile.write("1212121323232323");
    memFile.close();
    qDebug() << array.data();

    /*
     * QBuffer和QDataStream是结合起来用的，因为在QByteArray
     * 文件中所有的数据都字节的形式存储。QDataStream是以
     * 二进制的形式存储和读取数据。所以两者可以结合起来使用。
     *
     * 将QBuffer和QDataStream结合起来，向QDataStream输入代表
     * 向QBuffer中输入数据，向QDataStream读取代表向QBuffer中
     * 读取数据。
       */
    QBuffer data;
    data.open(QBuffer::WriteOnly);
    QDataStream stream(&data);
    stream << QString("黄鑫是傻子") << 250;
    data.close();
    qDebug() << data.buffer();

    data.open(QBuffer::ReadOnly);
    QDataStream out(&data);
    QString str;
    int i;
    out >> str >> i;
    data.close();

    qDebug() << str << i;
}

Widget::~Widget()
{
    delete ui;
}
