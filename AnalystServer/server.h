#ifndef SERVER_H
#define SERVER_H
#include "serverlistener.h"
#include <QObject>


class Server: public QObject
{
    Q_OBJECT

public:
    explicit Server();
    ~Server();
    QHostAddress sender;    //agpec
    quint16 senderPort; //nopт отправителя

public slots:
    void slotUDPReadingData();  //обработчик сообщений от клиента

private:
    quint16 portTcpServer = 2225;
    QUdpSocket *udpSocket;  //указатель на объект класса QUdpSocket
    QString message = "";
    QList<ServerListener*> listeners;
};



#endif // SERVER_H
