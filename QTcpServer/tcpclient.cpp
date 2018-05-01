#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QHostAddress>

TcpClient::TcpClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpClient)
{
    this->setWindowTitle("客户端");
    //初始化数据
    tcpSocket = NULL;
    ui->setupUi(this);

    //创建QTcpSocket对象
    tcpSocket = new QTcpSocket(this);

    //获取链接的端口号和连接的服务器IP
    server_address = ui->lineEdit_IP->text();
    server_port = ui->lineEdit_Port->text().toInt();

    //当链接到服务器后会发出connected()信号。
    connect(tcpSocket, &QTcpSocket::connected,
            [ = ](){
        //显示提示信息
        ui->textEdit_Read->setText(tr("已经与服务器链接!"));
        //显示服务器信息
        ui->textEdit_Read->append(QString("服务器的IP为:[%1] 端口为:[%2]").arg(server_address).arg(server_port));

        //当IODevice有新的数据可以读取的时候，readyRead()信号就会发出
        connect(tcpSocket, &QTcpSocket::readyRead,
                [ = ](){
            //获取信息
            QByteArray text = tcpSocket->readAll();
            //显示信息
            ui->textEdit_Read->append(QString(text));
        });
    });
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::on_pushButton_Connection_clicked()
{
    //链接到服务器
    tcpSocket->connectToHost(QHostAddress(server_address), server_port);
}

void TcpClient::on_pushButton_Send_clicked()
{
    if( tcpSocket == NULL ){
        return;
    }
    //获取需要传输的信息
    QString text = ui->textEdit_Write->toPlainText();
    //将信息写入QTcpSocket对象中
    tcpSocket->write(text.toUtf8().data());
}

void TcpClient::on_pushButton_Disconnection_clicked()
{
    //当链接未断开是，先断开链接
    if(tcpSocket != NULL){
        connect(tcpSocket, &QTcpSocket::disconnected,
                [ = ](){
            ui->textEdit_Read->append("已经与服务器断开");
        });
        tcpSocket->disconnectFromHost();
    }
}
