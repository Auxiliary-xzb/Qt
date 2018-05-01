#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class UdpClient;
}

class UdpClient : public QWidget
{
    Q_OBJECT

public:
    explicit UdpClient(QWidget *parent = 0);
    ~UdpClient();

private slots:
    void on_pushButton_Send_clicked();
    void deal_Message();

private:
    Ui::UdpClient *ui;
    QUdpSocket *udpSocket;
    QString server_address;
    quint16 server_port;
};

#endif // UDPCLIENT_H
