#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDateTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_ReadFile_clicked()
{
    ui->textEdit->clear();
    //获取打开文件的路径
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), "../");
    if(!path.isEmpty()){
        //创建文件对象
        QFile file;
        //指定文件路径
        file.setFileName(path);
        //只读方式打开文件文件
        bool isOK = file.open(QFile::ReadOnly);
        if(isOK){
            //输出文件的大小，路径名，后缀名
            QFileInfo info(file);
            ui->textEdit->append(QString("文件名字：%1").arg(info.fileName().toUtf8().data()));
            ui->textEdit->append(QString("文件大小：%1").arg(info.size()));
            ui->textEdit->append(QString("文件后缀：%1").arg(info.suffix()));
            ui->textEdit->append(QString("文件路径：%1").arg(info.filePath()));
            ui->textEdit->append(QString("文件父目录：%1").arg(info.dir().dirName()));
            //created()返回一个QDateTime对象，调用的该对象的toString()方法来设置显示格式
            //具体的时间显示格式可以在帮助文档中查看
            ui->textEdit->append(QString("文件创建时间：%1").arg(info.birthTime().toString("yyyy-MM-dd hh:mm:ss")));
            //关闭文件
            file.close();
        }
    }
}
