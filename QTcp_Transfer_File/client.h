#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>
#include <QMap>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();
private slots:
     void sendData();

private slots:
     void on_pushButton_Connect_clicked();

     void on_pushButton_Choose_clicked();

     void on_pushButton_Send_clicked();

     void deal_readyRead();

private:
    Ui::Client *ui;
    QTcpSocket *tcpSocket;              //传输套接字
    QString server_address;               //服务器地址
    quint16 server_port;                    //服务器端口
    QFile *file, *file_receive;              //文件对象
    QString file_name, receive_file_name;//文件名
    qint64 file_size,receive_file_size;  //文件大小
    qint64 send_size, receive_size;
    bool isHead;                                //判断头部信息
};

#endif // CLIENT_H
