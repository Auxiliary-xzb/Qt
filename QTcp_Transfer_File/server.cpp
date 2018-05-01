#include "server.h"
#include "ui_server.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QTimer>
#include <QMetaObject>
#include <QMetaEnum>

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);

    ui->pushButton_Choose->setEnabled(false);
    ui->pushButton_Send->setEnabled(false);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);

    tcpServer = new QTcpServer(this);
    //监听9999端口
    tcpServer->listen(QHostAddress::Any, 9999);

    //第一个开始肯定发的是头部信息
    isHead = true;

    //处理新连接
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::deal_newConnection);
}

void Server::deal_newConnection(){
    //获取新连接的QTcpSocket对象
    tcpSocket = tcpServer->nextPendingConnection();
    //获取客户端地址
    QString client_address = tcpSocket->peerAddress().toString();
    //获取客户端端口
    quint16 client_port = tcpSocket->peerPort();

    QString text = QString("[%1 : %2]链接成功").arg(client_address).arg(client_port);
    ui->textEdit->append(text);
    ui->pushButton_Choose->setEnabled(true);
    ui->pushButton_Send->setEnabled(true);

    //处理前先将数据初始化
    receive_size = 0;
    //处理数据
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Server::deal_readyRead);
}

void Server::deal_readyRead(){
    //取出接收的内容
    QByteArray buf = tcpSocket->readAll();
    //如果是头部信息
    if(isHead){
        isHead = false;
        //解析头部信息
        /*
         * This string is treated as a sequence of fields separated by the character, sep.
         *
         * 该字符串被看做是由字符sep分隔的一个区块序列。
        */
        file_name = QString(buf).section("##", 0, 0);
        file_size = QString(buf).section("##", 1, 1).toInt();

        ui->progressBar->setMaximum(file_size);

        //创建一个新文件
        file = new QFile(this);
        file->setFileName(file_name);
        bool isOK = file->open(QFile::WriteOnly);
        if(!isOK){
            QMessageBox::warning(this, tr("Warning"), tr("Create file failed!"));
            return;
        }
    }else{
        qint64 len = file->write(buf);
        receive_size += len;

        ui->progressBar->setValue(receive_size);

        if(receive_size == file_size){
            file->close();
            QMessageBox::information(this, tr("Hint"), tr("File had received!"));
            tcpSocket->disconnectFromHost();
            tcpSocket->close();
        }
    }
}

Server::~Server()
{
    delete ui;
}

void Server::on_pushButton_Choose_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("File Open"), "../", tr("Music (*.mp3)"));
    if(!filePath.isEmpty()){
        //创建文件
        file_send = new QFile(filePath);
        //获取文件信息
        QFileInfo info(filePath);
        send_file_name = info.fileName();
        send_file_size = info.size();
        ui->textEdit->append(send_file_name);
    }else{
        QMessageBox::warning(this, tr("Warning"), tr("This is a empty path"));
        return;
    }
}

void Server::on_pushButton_Send_clicked()
{
    //头部信息
    QString head = QString("%1##%2").arg(send_file_name).arg(send_file_size);

    //向客户端发消息
    qint64 len = tcpSocket->write(head.toUtf8().data());
    //如果发送成功，则延迟五毫秒再发送内容
    if(len > 0){
        QTimer timer;
        timer.singleShot(5, this, &Server::sendData);
        timer.setSingleShot(true);
    }else{
       QMetaObject meta_2 = QTcpSocket::staticMetaObject;
        int index = meta_2.indexOfEnumerator(QString("SocketState").toUtf8().data());
        QMetaEnum socketStatusEnum = meta_2.enumerator(index);
        QString text = socketStatusEnum.valueToKey(tcpSocket->state());
        QMessageBox::warning(this, tr("Warning"), text);
        return;
    }
}

void Server::sendData(){
    //打开读取的文件
    bool isOK = file_send->open(QFile::ReadOnly);
    if(isOK){
        char buf[1024] = {0};
        qint64 len = 0;
        send_size = 0;
        do{
            buf[1024] = {0};
            len = 0;
            len = file_send->read(buf, sizeof(buf));
            len = tcpSocket->write(buf, len);

            send_size += len;
        }while(len > 0);

        if(send_size == send_file_size){
            ui->textEdit->append("文件发送成功");
            file_send->close();
        }
    }else{
        QMessageBox::warning(this, tr("Warning"), tr("Can't open file!"));
        return;
    }
}
