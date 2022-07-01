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
//#include <QQmlProperty>
//#include <QQmlContext>
#include "database.h"
//#include "listmodel.h"



class Client: public QObject
{
    Q_OBJECT
        //свойство связывающее события интерфейса QML и кода
    //Q_PROPERTY(QString filepath READ getFilepath WRITE setFilepath NOTIFY filepathChanged)
public:
    Client();
    //Client(QQmlApplicationEngine &engine);
    ~Client();
    QUdpSocket *udpSocket;  //указатель на объект класса QUdpSocket
    QTcpSocket *tcpSocket;  //указатель на объект класса QTcpSocket

signals:
    void databaseUpdate();     //сигнал при изменении пути к файлу в коде
    /*void tableValRepUpdate(QMap<QChar,int> tabl);
    void tableDstLenUpdate(QMap<int,int> tabl);*/
    void tableValRepUpdate(QStringList tabl);
    void tableDstLenUpdate(QStringList tabl);
    void connectSuccess();
    void sentFileToServer(QString strFilename);
    void disconnected(void);

public slots:
    void slotConnectToServer();
    void slotReadingUDPData(); //чтение данных с udpSocket
    void slotReadingTcpData(); //чтение данных с tcpSocket
    void slotSockDisc();    //отключение сокета
    void slotFilepathChange(QString str);
    void slotMakeRequestToServer(); //запрос статистики от сервера
    //ListModel slotGetModelTable();

private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void sendFullFile();
    void timeoutToSendFile();

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
    //DataBase database;
    //ListModel* mymodel;
};

#endif // CLIENT_H
