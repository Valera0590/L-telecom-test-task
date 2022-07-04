#ifndef CLIENT_H
#define CLIENT_H

#include <QAbstractSocket>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QFile>
#include <QDataStream>
#include <QThread>
#include <QTime>
#include <QTimer>
#include "database.h"




class Client: public QObject
{
    Q_OBJECT

public:
    Client();
    ~Client();
    QUdpSocket *udpSocket;  //указатель на объект класса QUdpSocket
    QTcpSocket *tcpSocket;  //указатель на объект класса QTcpSocket

signals:
    void databaseUpdate();     //сигнал при изменении пути к файлу в коде
    void tableModelValueRepeatUpdate(QStringList table);
    void tableModelWordsByLengthUpdate(QStringList table);
    void connectSuccess();
    void sentFileToServer(QString strFilename);
    void disconnected(void);
    void errorSocket(QString strErrorSocket);
    void gotInfoFromServer(QString strInfo);

public slots:
    void slotConnectToServer();
    void slotReadingUDPData(); //чтение данных с udpSocket
    void slotReadingTcpData(); //чтение данных с tcpSocket
    void slotSockDisc();    //отключение сокета
    void slotFilepathChange(QString str);
    void slotMakeRequestToServer(); //запрос статистики от сервера

private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void sendFullFile();
    void slotTimeoutToSendFile();
    void slotTimeoutToConnectUDP();

private:
    QByteArray datagram;
    QHostAddress ipServer;
    quint16 portThisClient = 1;
    quint16 portTcpServer;
    QString filePath = "";
    QFile *sendFile;
    bool clientConnected = false;
    QTimer* timer;
    void cutToRigthFilepath(QString fp);
    bool gettingInfoFile = false;
    bool gettingInfoDB = false;
    QByteArray tmpBlock;
    QTimer* timerConnectUDP;
};

#endif // CLIENT_H
