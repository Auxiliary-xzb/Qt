#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class UdpServer;
}

class UdpServer : public QWidget
{
    Q_OBJECT

public:
    explicit UdpServer(QWidget *parent = 0);
    ~UdpServer();

private slots:
    void on_pushButton_Send_clicked();
    void deal_Message();

private:
    Ui::UdpServer *ui;
    QUdpSocket *udpSocket;
    QString client_address;
    quint16 client_port;
};

#endif // UDPSERVER_H
