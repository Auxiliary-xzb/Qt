#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class TcpClient;
}

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = 0);
    ~TcpClient();

private slots:
    void on_pushButton_Connection_clicked();
    void on_pushButton_Send_clicked();
    void on_pushButton_Disconnection_clicked();

private:
    Ui::TcpClient *ui;
    QTcpSocket *tcpSocket;
    QString server_address;
    quint16 server_port;
};

#endif // TCPCLIENT_H
