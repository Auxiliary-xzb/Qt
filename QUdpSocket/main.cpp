#include "udpserver.h"
#include "udpclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UdpServer w;
    w.show();

    UdpClient w2;
    w2.show();

    return a.exec();
}
