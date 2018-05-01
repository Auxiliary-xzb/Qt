#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private slots:
    void deal_newConnection();
    void deal_readyRead();
    void sendData();

    void on_pushButton_Choose_clicked();

    void on_pushButton_Send_clicked();

private:
    Ui::Server *ui;
    QTcpServer *tcpServer;              //服务器
    QTcpSocket *tcpSocket;              //通信套接字
    QFile *file, *file_send;                 //保存的文件
    bool isHead;                              //头部信息判断标识
    QString file_name, send_file_name;                     //文件名
    qint64 file_size, send_file_size;                      //文件大小
    qint64 receive_size, send_size;                //接收到的长度

};

#endif // SERVER_H
