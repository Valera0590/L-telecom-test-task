#include "server.h"


Server::Server()
{
    udpSocket = new QUdpSocket(this);   //coздаëм обьект соkета QUdpSocket

    udpSocket->bind(QHostAddress::Broadcast, 2222); //задаём широковещательный адрес и порт на который сокет будет получать данные
    connect (udpSocket, SIGNAL (readyRead()), this, SLOT (slotUDPReadingData()));  //для получения и отображения данныx соединяем сигнал сокета со слотом

    qDebug() << "Server start listening udp socket with port 2222";
}
Server::~Server()
{
    delete udpSocket;
    listeners.clear();
}

void Server::slotUDPReadingData()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());  //узнаем размер ждущей обработки "датаграммы"
        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort); //читаем данные
        message = datagram.data();
    }
    qDebug()<<"";
    qDebug() <<"Client connected with server by udp - "<<message<<".\nSend to clientserver's ip on new port: " << quint16(senderPort)+1;
    QThread::msleep(200);   //пауза для завершения установки порта прослушивания в клиентском приложении

    ServerListener* srv = new ServerListener(portTcpServer);    //запускаем нового слушателя на сервере для сокета очередного подключенного клиента
    listeners.append(srv);

    QString st = QString("%1").arg(portTcpServer);  //подготавливаем новый порт для следующего подключенного клиента
    portTcpServer++;

    udpSocket->writeDatagram(st.toUtf8(), QHostAddress::Broadcast, int(senderPort)+1);  //отправляем данные по широковешательному адресу на порт 2222
}




