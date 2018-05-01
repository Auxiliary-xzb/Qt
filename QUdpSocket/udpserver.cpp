#include "udpserver.h"
#include "ui_udpserver.h"
#include <QHostAddress>

UdpServer::UdpServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UdpServer)
{
    //初始化数据
    udpSocket = NULL;
    ui->setupUi(this);
    this->setWindowTitle("端口号为8888");

    //创建QUdpSocket对象
    udpSocket = new QUdpSocket(this);
    //为QUdpSocket对象绑定IP和端口（为了方便直接绑定端口，地址就用测试的IP）
    udpSocket->bind(8888);


    //接收对方的信息。
    //当数据报到达时会发出readyRead()信号，
    //如果不处理该信号，其他的数据报就不会发出信息。
    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpServer::deal_Message);
}

UdpServer::~UdpServer()
{
    delete ui;
}

void UdpServer::on_pushButton_Send_clicked()
{
    //获取对方的IP和address
    client_address = ui->lineEdit_IP->text();
    client_port = ui->lineEdit_Port->text().toInt();
    //获取输入栏数据
    QString text = ui->textEdit_Write->toPlainText();
    //当用户不输入时，不做处理
    if(text == NULL){
        return;
    }
    //当有输入时，将信息传给指定用户的指定端口
    udpSocket->writeDatagram(text.toUtf8(), QHostAddress(client_address), client_port);
    //当数据报被传送到网络时会发出bytesWritten()信号，
    //此时将传输的信息显示到发送取。
    connect(udpSocket, &QUdpSocket::bytesWritten,
            [ = ](){
        ui->textEdit_Read->append(QString("[%1 : %2]: %3")
                                  .arg(client_address)
                                  .arg(client_port)
                                  .arg(QString(text.toUtf8()))
                                  );
    });
}

void UdpServer::deal_Message(){
    //如果没有数据报可用就不做处理
    if(udpSocket->pendingDatagramSize() == -1){
        return;
    }
    //对方的地址
    QHostAddress peerAddress;
    //对方的端口
    quint16 peerPort;
    //对方的数据
    char buf[2048];
    //读取对方的数据内容，放入buf中
    quint64 len = udpSocket->readDatagram(buf, sizeof(buf), &peerAddress, &peerPort);
    if(len > 0){
        //将内容显示
        ui->textEdit_Read->append(QString("[%1 : %2]: %3")
                                  .arg(peerAddress.toString())
                                  .arg(peerPort)
                                  .arg(buf));
    }
}
