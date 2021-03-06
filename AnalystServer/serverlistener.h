#ifndef SERVERLISTENER_H
#define SERVERLISTENER_H

#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include <QtNetwork>
#include <QAbstractSocket>
#include <QThread>
#include "distributionwordsbylength.h"
#include "valuerepeatsymbol.h"
#include "algorithms.h"
#include "database.h"
#include <QTime>
#include <QTimer>
#include <QDir>




class ServerListener:public QTcpServer
{
    Q_OBJECT
public:
    ServerListener(quint16 port);
    ~ServerListener();
    QTcpSocket *tcpSocket;
    bool isClientConnected = false;

public slots:
    void incomingConnection(qintptr socketDescriptor);  //слот для подключения клиента
    void startTcpServerListening(quint16 port); //запуск слушателя сервера TcpSocket
    void slotReadyReadTcp();   //обработчик полученных сообщений от клиента
    void slotFileReadyForAnalyze();     //слот-функция для начала анализа файла

private:
    //QByteArray Data;
    QString flNm = "";
    QString fileCopy; // Путь файла для сохранение
    QString filePath;
    qint64 fileSize;
    QByteArray tmpBlock;
    bool isDownloading = false;
    QMap<QChar,int> valueofrepeat;
    QMap<int,int> distbylength;
    QTimer* timer;
    DataBase database;
    QFile *sendFile;

private:
    void sendToClient(QString str);
    void sendDatabase();
private slots:
    void sendToClient();
    void timeoutToSendDatabase();
};

#endif // SERVERLISTENER_H
