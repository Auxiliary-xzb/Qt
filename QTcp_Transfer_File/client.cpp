#include "client.h"
#include "ui_client.h"
#include <QHostAddress>
#include <QFileDialog>
#include <QMessageBox>
#include <QDataStream>
#include <QTimer>
#include <QFileInfo>
#include <QMetaObject>
#include <QMetaEnum>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    ui->textEdit->setReadOnly(true);
    //创建QTcpSocket对象
    tcpSocket = new QTcpSocket(this);

    //获取服务器端口和IP
    server_address = ui->lineEdit_IP->text();
    server_port = ui->lineEdit_Port->text().toInt();

    //设置两个按钮不能使用，在链接到服务器之间
    ui->pushButton_Choose->setEnabled(false);
    ui->pushButton_Send->setEnabled(false);

    //创建文件对象，因为该对象在链接处理时也要使用，所以就直接创建比较好。
    file = new QFile(this);

    isHead = true;
    receive_size = 0;
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Client::deal_readyRead);
}


/*
 * 可以研究一个开了QDataStream再来读取数据，
 * 里面有个函数没弄动 readBytes()
*/
void Client::sendData(){
    //打开文件
    bool isOK = file->open(QFile::ReadOnly);
    if(!isOK){
        QMessageBox::warning(this, tr("Warning"), tr("Can't get the file!"));
        return;
    }

    //定义读取的数据的缓冲区
    char buf[1024] = {0};
    //本次传输的长度
    qint64 len = 0;
    send_size = 0;
    do{
        //每次放数据前先清空缓冲区
        buf[1024] = {0};
        len = 0;
        //将数据读入到缓冲区对象中
        len = file->read(buf, sizeof(buf));
        //将数据写入QTcpSocket
        len = tcpSocket->write(buf, len);

        /*
         *
         * 在开始的时候写错了，写成了：
         *      len = tcpSocket->write(buf);
         * 在帮助文档中，qint64 QIODevice::write(const char *data)函数的说明如下:
         *      Writes data from a zero-terminated string of 8-bit characters to the device.
         * Returns the number of bytes that were actually written, or -1 if an error occurred.
         *
         *       写一个8位以'\0'结尾的数据到设备中，返回实际写入的字节数，当出
         * 现错误时返回-1。
            */

        send_size += len;
    }while(len > 0);

    if(send_size == file_size){
        ui->textEdit->append("文件发送完毕");
        //关闭文件
        file->close();
    }
}

Client::~Client()
{
    delete ui;
}

void Client::on_pushButton_Connect_clicked()
{
    //链接到服务器
    tcpSocket->connectToHost(QHostAddress(server_address), server_port);
    //如果QTcpSocket的状态为创建好了链接，则设置两个按钮可用
    connect(tcpSocket, &QTcpSocket::connected,
            [ = ](){
        ui->pushButton_Choose->setEnabled(true);
        ui->pushButton_Send->setEnabled(true);

        QString text = QString("与服务器链接成功，服务器地址%1，端口%2")
                .arg(tcpSocket->peerAddress().toString())
                .arg(tcpSocket->peerPort());
        ui->textEdit->append(text);
    });
}

void Client::on_pushButton_Choose_clicked()
{
    //选择文件，获取文件路径
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), tr("../"), tr("Music (*.mp3)"));
    if(filePath.isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("This is a empty path"));
        return;
    }

    //设置文件关联的对象
    file->setFileName(filePath);
    //获取文件信息
    /*
     * 这里存在一个问题：
     *      在QFile中调用的fileName()函数返回的是整个文件的路径，
     * 也就是该文件的绝对路径，那么文件的状态exits()就肯定为true，
     * 那么文件就会覆盖，所以就需要得到文件去掉路径的文件名，
     * 那么此时应该需要QFileInfo的fileName()。
        */
    QFileInfo info(filePath);
    file_size = info.size();
    file_name = info.fileName();
    ui->textEdit->append(file_name);
}

void Client::on_pushButton_Send_clicked()
{
    //发送文件头部信息
    QString head = QString("%1##%2").arg(file_name).arg(file_size);

    //向服务器传送文件信息
    qint64 len = tcpSocket->write(head.toUtf8().data());
    if(len > 0){
        //延迟一段时间再发送文件主体数据，防止粘包文件
        QTimer timer;
        /*
         * This static function calls a slot after a given time interval.
         * 该静态函数在给定的时间之后调用一个slot函数
            */
        timer.singleShot(20, this, &Client::sendData);
        /*
         * This property holds whether the timer is a single-shot timer.
         * A single-shot timer fires only once, non-single-shot timers fire every interval milliseconds.
         *The default value for this property is false.
         *
         * 该属性表示定时器是否为单次触发定时器，一个单次触发定时器值响应一次
         * 非单次触发定时器每隔interval毫秒响应一次，该值默认为false。
            */
        timer.setSingleShot(true);
    }else {
        /*
         * const QMetaObject QObject::staticMetaObject
         *
         *      This variable stores the meta-object for the class.
         * A meta-object contains information about a class that inherits QObject, e.g. class name,
         * superclass name, properties, signals and slots. Every class that contains the Q_OBJECT
         *  macro will also have a meta-object.
         *      The meta-object information is required by the signal/slot connection mechanism and
         *  the property system. The inherits() function also makes use of the meta-object.
         *      If you have a pointer to an object, you can use metaObject() to retrieve the meta-object
         *  associated with that object.
         *
         * 该变量存储了该类的元数据对象。一个元数据包含一个继承自QObject对象的信息。‘
         * 例如，类名，父类名，属性，信号，槽。每个包含Q_OBJECT宏的类都有一个元数
         * 据对象。
         * 元数据对象在存储信号和槽的链接机制和属性系统是十分必须的。inherits()函数也
         * 适应元数据对象。
         * 如果有一个对象的指针，可以调用metaObject()检索关联该对象的元数据对象。
         *
         *
         *
         *  QPushButton::staticMetaObject.className();  // returns "QPushButton"
         *
         *  QObject *obj = new QPushButton;
         *  obj->metaObject()->className();             // returns "QPushButton"
        */
        QMetaObject meta = QTcpSocket::staticMetaObject;
        /*
         * int QMetaObject::indexOfEnumerator(const char *name) const
         *      Finds enumerator name and returns its index; otherwise returns -1.
         *
         * 寻找名为name的枚举器，返回它的索引，否则返回-1。
            */
        int index = meta.indexOfEnumerator(QString("SocketState").toUtf8().data());
        /*
         * QMetaEnum QMetaObject::enumerator(int index) const
         *       Returns the meta-data for the enumerator with the given index.
         *
         * 根据给定的索引返回枚举器的元数据。
            */
        QMetaEnum socketStatusEnum = meta.enumerator(index);
        /*
         * const char *QMetaEnum::valueToKey(int value) const
         *      Returns the string that is used as the name of the given enumeration value,
         * or 0 if value is not defined.
         *
         * 返回指定的枚举值所对应的字符串，如果值没有定义就返回0。
            */
        QString text = socketStatusEnum.valueToKey(tcpSocket->state());
        QMessageBox::warning(this, tr("Warning"), text);
        return;
    }
}

void Client::deal_readyRead(){
    if(tcpSocket != NULL){
        //获取信息
        QByteArray array = tcpSocket->readAll();
        //检测是否为头部信息
        if(isHead == true){
            isHead = false;
            //分解头部信息，得到文件信息
            receive_file_name = QString(array).section("##", 0, 0);
            receive_file_size = QString(array).section("##", 1, 1).toInt();

            //创建一个文件对象
            file_receive = new QFile(receive_file_name);
            bool isOK = file_receive->open(QFile::WriteOnly);
            if(!isOK){
                QMessageBox::warning(this, tr("Warning"), tr("Can't open the file!"));
                return;
            }
        }else{
            qint64 len = file_receive->write(array);
            receive_size += len;

            if(receive_size == receive_file_size){
                file_receive->close();
                QMessageBox::information(this, tr("Hint"), tr("File had received!"));
                tcpSocket->disconnectFromHost();
                tcpSocket->close();
            }
        }
    }
}
