#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QFile>
#include <QDebug>

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

//读文件，默认只能识别UTF-8编码的文件
void Widget::on_pushButton_ReadFile_clicked()
{
    /*
     * 参数列表：
     *  1.父对象
     *  2.标题
     *  3.路径名
     *  4.指定打开格式    （在Qt中使用不到的参数可以不写）
    */
    //读取文件的路径
    QString path = QFileDialog::getOpenFileName(this, QString("Open File"), "../");

    /*
     * Returns true if the string has no characters; otherwise returns false.
     * 字符串中没有一个字符时返回true，否则返回false。
     *
     * QString("").isEmpty()返回的是true
    */
    //如果路径不为空再操作
    if( !path.isEmpty() ){
        //创建文件对象。
        //当将一个路径传给对象的构造器时就代表该路径与文件关联了。
        QFile file(path);

        /*
         * 打开文件，最少的一个参数为OpenModeFlag，可以在帮组文档中查看
         * 成功打开返回true，否则返回false
        */
        //以只读的方式打开
        bool isOK = file.open(QFile::ReadOnly);
        if( isOK ){
            //读取文件

            //方案一
            /*
             * read()函数为传统的读文件方式，指定一个缓冲区char *
             * 然后指定读取的字节数。
            */
#if 0
            char buffer[2048];
            file.read(buffer, sizeof(buffer));
            qDebug() << buffer;
#endif

            //方案二
            /*
             *      Reads all remaining data from the device, and returns it as a byte array.
             *      This function has no way of reporting errors; returning an empty QByteArray can
             *  mean either that no data was currently available for reading, or that an error occurred.
             *
             * 从设备中读取所有保存的数据，返回一个字节数组
             * 该函数无法报告错误，返回一个空的QByteArray可能意味着现在没有数据可读
             * 或者有错误出现。
              */
#if 0
            QByteArray bytearray = file.readAll();
            qDebug() << bytearray.data();
#endif

            //方案三
            /*
             *      Reads a line from the device, but no more than maxSize characters, and returns the result as a byte array.
             *      This function has no way of reporting errors; returning an empty QByteArray can mean either that no data
             *  was currently available for reading, or that an error occurred.
             *
             * 从设备中读取一行，但是不超过maxSize个字节，返回结果到一个QByteArray中
             * 该函数没有办法报告错误。
                */
            QByteArray arraybyte;
            arraybyte.clear();
            //文件未读取完，则继续读
            while(file.atEnd() == false){
                arraybyte += file.readLine();
            }
            //QString提供了将QByteArray转换为QString的构造器
            ui->textEdit->setText(QString(arraybyte));

            //类似于输入输出流，打开之后就要关闭。
            file.close();
        }
    }
}

void Widget::on_pushButton_WriteFile_clicked()
{
    //保存文件的路径
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), "../", tr("TXT(*.txt)"));

    if(!path.isEmpty()){
        //将QFile对象与该文件关联
        QFile file(path);

        //打开文件,以只写的方式
        bool isOK =file.open(QFile::WriteOnly);
        if( isOK ){
            //获取textEdit的内容
            QString text = ui->textEdit->toPlainText();
            //将QString转换为QByteArray后再传递给文件
            file.write(text.toUtf8());
            //关闭文件
            file.close();   
        }
    }
}
