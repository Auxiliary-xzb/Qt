#include "udpclient.h"
#include "ui_udpclient.h"
#include <QHostAddress>

UdpClient::UdpClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UdpClient)
{
    //初始化数据
    udpSocket = NULL;
    ui->setupUi(this);
    this->setWindowTitle("端口号为9999");

    //创建QUdpSocket对象
    udpSocket = new QUdpSocket(this);
    //绑定端口
    udpSocket->bind(9999);

    //处理传送来的数据
    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpClient::deal_Message);
}

UdpClient::~UdpClient()
{
    delete ui;
}

void UdpClient::on_pushButton_Send_clicked()
{
    //获取对方的IP和address
    server_address = ui->lineEdit_IP->text();
    server_port = ui->lineEdit_Port->text().toInt();
    //获取输入栏数据
    QString text = ui->textEdit_Write->toPlainText();
    //当用户不输入时，不做处理
    if(text == NULL){
        return;
    }
    //当有输入时，将信息传给指定用户的指定端口
    udpSocket->writeDatagram(text.toUtf8(), QHostAddress(server_address), server_port);
    //当数据报被传送到网络时会发出bytesWritten()信号，
    //此时将传输的信息显示到发送取。
    connect(udpSocket, &QUdpSocket::bytesWritten,
            [ = ](){
        ui->textEdit_Read->append(QString("[%1 : %2]: %3")
                                  .arg(server_address)
                                  .arg(server_port)
                                  .arg(QString(text.toUtf8()))
                                  );
    });

}

void UdpClient::deal_Message(){
    //可用的数据报为0则返回-1
    if(udpSocket->pendingDatagramSize() == -1){
        return;
    }

    //对方的地址
    QHostAddress peer_address;
    //对方的端口
    quint16 peer_port;
    //对方的信息
    char buf[2048];

    //获取对方的信息
    quint64 len = udpSocket->readDatagram(buf, sizeof(buf), &peer_address, &peer_port);
    if( len > 0 ){
        ui->textEdit_Read->append(QString("[%1 : %2]: %3")
                                  .arg(peer_address.toString())
                                  .arg(peer_port)
                                  .arg(QString(buf))
                                  );
    }
}
