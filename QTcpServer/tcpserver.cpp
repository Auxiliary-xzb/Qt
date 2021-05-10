#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QHostAddress>

TcpServer::TcpServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServer)
{
    //初始化数据
    tcpServer = NULL;
    tcpSocket = NULL;

    ui->setupUi(this);


    //创建QTcpServer对象
    tcpServer = new QTcpServer(this);
    //指定监听的端口和地址。
    /*
     * Tells the server to listen for incoming connections on address address and port port.
     *  If port is 0, a port is chosen automatically. If address is QHostAddress::Any, the server will listen on all network interfaces.
     *
     *告诉服务器监听来自address的地址和监听端口port。
     * 如果端口为0，端口将被自动选择。如果地址是QHostAddress::Any，服务器将监听所有的网络接口。
        */
    tcpServer->listen(QHostAddress::Any, 8999);
    //处理链接。当有链接到服务器时，会发出QTcpServer对象会newConnection()信号。
    connect(tcpServer, &QTcpServer::newConnection,
            [ = ](){
        //获取通信对象QTcpSocket
        tcpSocket = tcpServer->nextPendingConnection();
        //获取客户端的端口和地址
        QString client_address = tcpSocket->peerAddress().toString();
        quint16 client_port = tcpSocket->peerPort();

        //将获取的信息显示到textedit中。
        ui->textEdit_Read->setText(QString("客户端的IP地址为:[%1], 端口为:[%2]").arg(client_address).arg(client_port));

        //获取了通信对象QTcpSocket后，服务器也要获取客户端传送来的内容
        //对于IODevice只要有新的数据可读时，readyRead()信号就会发出。
        connect(tcpSocket, &QTcpSocket::readyRead,
                [ = ](){
            //获取客户端发来的信息
            QByteArray text = tcpSocket->readAll();
            //将信息追显示
            ui->textEdit_Read->append(QString(text));
        });

        //但接受到与服务器断开链接的信号时，给出提示信息。
        connect(tcpSocket, &QTcpSocket::disconnected,
                [ = ](){
            ui->textEdit_Read->append("已经与客户端断开");
        });
    });
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::on_pushButton_Send_clicked()
{
    //判断QTcpSocket是否为空。
    if(tcpSocket == NULL){
        //无链接则不发生消息
        return;
    }
    QString text = ui->textEdit_Write->toPlainText();
    //将数据写入通信套接字tcpSocket
    tcpSocket->write(text.toUtf8().data());
    ui->textEdit_Write->setText("");
}
