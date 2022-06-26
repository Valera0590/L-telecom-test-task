#include "client.h"

Client::Client()
{
    udpSocket = new QUdpSocket(this);   //coздаëм обьект соkета QUdpSocket
    connect (udpSocket, SIGNAL (readyRead()), this, SLOT (slotReadingUDPData()));  //для получения и отображения данныx соединяем сигнал сокета со слотом
    //связывание сигнала о новом файле со слотом анализа файла
    //connect(this, SIGNAL(filepathChanged()), this, SLOT(slotFileReadyForAnalyze()));
}

Client::~Client()
{
    delete udpSocket;
    delete tcpSocket;
}

void Client::slotConnectToServer()
{
    if(!clientConnected)
    {

        qDebug() << "Try to connect with server by UDP.";
        clientConnected = true;
        udpSocket->writeDatagram(QString("User want connect from out").toUtf8(), QHostAddress::Broadcast, 2222);  //отправляем данные по широковешательному адресу на порт 2222
        portThisClient += udpSocket->localPort();
        udpSocket->abort();
        udpSocket->bind(QHostAddress::Broadcast, portThisClient); //задаём широковещательный адрес и порт на который сокет будет получать данные

        tcpSocket = new QTcpSocket(this);
        connect (tcpSocket, SIGNAL (readyRead()), this, SLOT (slotReadingTcpData()));  //для получения и отображения данныx соединяем сигнал сокета со слотом
        connect (tcpSocket, SIGNAL (disconnected()), this, SLOT (slotSockDisc()));
        connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    }
    else    qDebug() << "You has active connection with server!\nPlease don't push this button while you are connected.";

}


void Client:: slotReadingUDPData()  //чтение данных
{
    QHostAddress sender;    //agpec
    quint16 senderPort; //nopт отправителя
    while(udpSocket->hasPendingDatagrams())
    {
        datagram.resize(udpSocket->pendingDatagramSize());  //узнаем размер ждущей обработки "датаграммы"
        udpSocket->readDatagram(datagram.data(),datagram.size(), &sender, &senderPort); //читаем данные
        qDebug()<<datagram.data()<<"IP: " + sender.toString()<<"Port: "+QString("%1").arg(senderPort);
        QString st = datagram.data();
        portTcpServer = st.toShort();
    }
    ipServer = sender;
    qDebug()<<"IP: "<<ipServer.toString() + " Port: "+QString("%1").arg(portTcpServer);
    tcpSocket->connectToHost( ipServer, portTcpServer);   //соединяемся с сервером по протоколу Tcp
    const int Timeout = 5 * 1000;
    if (!tcpSocket->waitForConnected(Timeout))
    {
        emit displayError(tcpSocket->error());
        return;
    }
    disconnect(udpSocket, SIGNAL (readyRead()), this, SLOT (slotReadingUDPData()));
    udpSocket->close();
}

void Client::cutToRigthFilepath(QString fp)  //убирает лишние символы перед действительным путем до файла
{
    QString rightFilepath = fp.remove(0,6);
    filePath = rightFilepath;
}

void Client::slotFilepathChange(QString str)    //слот-функция при изменении пути из-под интерфейса
{
    qDebug() << "slotFilepathChange " << str;
    cutToRigthFilepath(str);
    qDebug() << filePath;
    if(filePath != "")
    {
        QDataStream stream(tcpSocket);
        stream.setVersion(QDataStream::Qt_5_12);

        QString infoAboutFileToServer="file to analyze;"+filePath;
        stream << infoAboutFileToServer;
        tcpSocket->waitForBytesWritten();
        //QThread::msleep(200);
        sendFile = new QFile(filePath);
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(timeoutToSendFile())); // Подключаем сигнал таймера к нашему слоту
        timer->start(500);
    }
    else
    {
        qDebug() << "Не был выбран файл для отправки!";
        //QMessageBox::critical(NULL,QObject::tr("Ошибка"),tr("Не был выбран файл для отправки!"));
    }
}

void Client::slotReadingTcpData()
{
    qDebug() << "reading tcpSocket.";
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    if(in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;
        QStringList strList = str.split(";");
        if(str == "You were connecting")  //если получено сообщение о подключении клиента
        {
           qDebug() << str;
        }
        else if(strList.value(0) == "database")   //обработчик базы данных запросов пользователя
        {
            strList.removeFirst();
            while(!strList.isEmpty())
            {
                qDebug() << strList.value(0) << " | " << strList.value(1) << " | " << strList.value(2);
                for(int i=0;i<3;++i)    strList.removeFirst();
            }
        }
        else if(strList.value(0) == "fileInfo") //обработчик загруженного на сервер файла
        {
            qDebug() << "Get info about analyzing file...";
            qDebug() << str;

        }
    }
    else
    {
        qDebug() << "Read error!";
    }


}

void Client::sendFullFile()
{
    QDataStream stream(tcpSocket);
    stream.setVersion(QDataStream::Qt_5_12);

    if(sendFile->open(QFile::ReadOnly))
    {
        QByteArray dataS = sendFile->readAll();
        stream << dataS;
        tcpSocket->waitForBytesWritten();
        qDebug() << "_CLIENT: File end!";
        sendFile->close();
        sendFile = NULL;
        qDebug() << "_CLIENT: File send FINISH!";
    } else {
        qFatal("_CLIENT: File not open!");
    }

}

void Client::timeoutToSendFile()
{
    sendFullFile();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(timeoutToSendFile()));
}

void Client::slotSockDisc()
{
    qDebug() << "Deleting tcpSocket...";
    tcpSocket->deleteLater();
}


void Client::displayError(QAbstractSocket::SocketError socketError) {
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            qDebug() << "The host was not found. Please check the host name and port settings.";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            qDebug() << "The connection was refused by the peer.";
            qDebug() << "Make sure the fortune server is running, ";
            qDebug() << "and check that the host name and port settings are correct.";
            break;
        default:
            qDebug() << "The following error occurred: " + QString("%1.").arg(tcpSocket->errorString());
    }
    exit(socketError + 1);
}



