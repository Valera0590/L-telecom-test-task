#include "client.h"

Client::Client()
{
    udpSocket = new QUdpSocket(this);   //coздаëм обьект соkета QUdpSocket
    connect (udpSocket, SIGNAL (readyRead()), this, SLOT (slotReadingUDPData()));  //для получения и отображения данныx соединяем сигнал сокета со слотом
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
        connect(udpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
        clientConnected = true;
        timerConnectUDP = new QTimer(this);
        connect(timerConnectUDP, SIGNAL(timeout()), this, SLOT(slotTimeoutToConnectUDP())); // Подключаем сигнал таймера к нашему слоту
        timerConnectUDP->start(3000);      //если через 3 секунд не будет произведено подключение к серверу, то выдаем ошибку
        udpSocket->writeDatagram(QString("User want connect from out").toUtf8(), QHostAddress::Broadcast, 2222);  //отправляем данные по широковешательному адресу на порт 2222
        portThisClient += udpSocket->localPort();
        udpSocket->abort();
        //udpSocket->close();
        //udpSocket->waitForDisconnected();
        udpSocket->bind(portThisClient); //задаём широковещательный адрес и порт на который сокет будет получать данные

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
    disconnect(timerConnectUDP, SIGNAL(timeout()), this, SLOT(slotTimeoutToConnectUDP()));
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
    //QThread::msleep(500);
    qDebug() << "Try to connect to server by tcp";
    tcpSocket->connectToHost( ipServer, portTcpServer);   //соединяемся с сервером по протоколу Tcp
    const int Timeout = 5 * 1000;
    if (!tcpSocket->waitForConnected(Timeout))
    {
        emit displayError(tcpSocket->error());
        return;
    }
    disconnect(udpSocket, SIGNAL (readyRead()), this, SLOT (slotReadingUDPData()));
    disconnect(udpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
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
        sendFile = new QFile(filePath);
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(slotTimeoutToSendFile())); // Подключаем сигнал таймера к нашему слоту
        timer->start(500);      //ставим задержку в полсекунды перед отправкой серверу файла
    }
    else
    {
        qDebug() << "Не был выбран файл для отправки!";
    }
}

void Client::slotMakeRequestToServer()  //слот-функция для запроса статистики от сервера
{
    qDebug() << "Send to server request";
    QDataStream stream(tcpSocket);
    stream.setVersion(QDataStream::Qt_5_12);

    QString requestMessage="request data";
    stream << requestMessage;
    tcpSocket->waitForBytesWritten();
}

void Client::slotReadingTcpData()   //слот-функция для получения данных по TCP сокету
{
    qDebug() << "reading tcpSocket.";
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    if(in.status() == QDataStream::Ok)
    {
        if(!gettingInfoDB && !gettingInfoFile)
        {
            QString str;
            in >> str;
            QStringList strList = str.split(";");
            if(str == "You were connecting")  //если получено сообщение о подключении клиента
            {
                emit connectSuccess();
            }
            else if(strList.value(0) == "database")   //если пришло сообщение о получении БД
            {
                gettingInfoDB = true;
                qDebug() << "Start getting database";
            }
            else if(strList.value(0) == "fileInfo") //если пришло сообщение о получении анализа загруженного на сервер файла
            {
                gettingInfoFile = true;
                qDebug() << "Get info about analyzing file...";
                qDebug() << str;
            }
        }
        else if(gettingInfoDB)  //получение базы данных
        {
            in.startTransaction();
            in >> tmpBlock;
            if (!in.commitTransaction())    //ждём полной передачи файла через сокет
                return;
                //обновляем файл(удаляем + создаем новый)
            if(QFile(QDir::currentPath()+"/" DATABASE_NAME).exists())
            {
                QFile(QDir::currentPath()+"/" DATABASE_NAME).remove();
                qDebug() << "File had removed!";

            }
            QFile file(QDir::currentPath()+"/" DATABASE_NAME);
                //запись в файл БД
            if(file.open(QIODevice::WriteOnly))
            {
                file.write(tmpBlock);
                qDebug() << "\nData has been written to a file!";
            }
            else
            {
                qDebug() << "\nThe file don't open to write a data!";
                return;
            }
            file.close();
            qDebug() << "Client: END - bytesAvailable:" << tcpSocket->bytesAvailable();
            // Очистка переменных
            tmpBlock.clear();
            emit databaseUpdate();  //вызов обновления модели таблиц
            gettingInfoDB = false;
            emit gotInfoFromServer("Статистика запросов на сервер получена!");   //вызов сигнала об освобождении сокета
        }
        else if(gettingInfoFile)    //получение анализа от сервера загруженного файла
        {
            QMap<QChar, int> valueOfRepeat;
            QMap<int, int> distByLength;
            in >> valueOfRepeat;
            in >> distByLength;
            QStringList listRepeatCharacters;
            listRepeatCharacters.clear();
                //подготовка списка для отображения в первой таблице
            QMapIterator<QChar, int> i(valueOfRepeat);
            while (i.hasNext())
            {
                i.next();
                listRepeatCharacters.append(QString("%1").arg(i.key())) ;
                listRepeatCharacters.append(QString("%1").arg(i.value()));
            }
            emit tableModelValueRepeatUpdate(listRepeatCharacters);
            QStringList listWordsByLength;
            listWordsByLength.clear();
                //подготовка списка для отображения во второй таблице
            QMapIterator<int, int> j(distByLength);
            while (j.hasNext())
            {
                j.next();
                listWordsByLength.append(QString("%1").arg(j.key())) ;
                listWordsByLength.append(QString("%1").arg(j.value()));
            }
            emit tableModelWordsByLengthUpdate(listWordsByLength);
            gettingInfoFile = false;
            emit gotInfoFromServer("Сервер закончил анализ отправленного\nфайла!");   //вызов сигнала об освобождении сокета
        }
    }
    else
    {
        qDebug() << "Read error!";
    }


}

void Client::sendFullFile()     //метод, реализующий отправку файла серверу для анализа
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
        emit sentFileToServer(filePath.split("/").last());
    } else {
        qFatal("_CLIENT: File not open!");
    }

}

void Client::slotTimeoutToSendFile()    //обработчик по окончании времени таймера
{
    sendFullFile();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(slotTimeoutToSendFile()));
}

void Client::slotTimeoutToConnectUDP()
{
    disconnect(timerConnectUDP, SIGNAL(timeout()), this, SLOT(slotTimeoutToConnectUDP()));
    udpSocket->abort();
    disconnect (udpSocket, SIGNAL (readyRead()), this, SLOT (slotReadingUDPData()));
    delete udpSocket;
    portThisClient = 1;
    disconnect (tcpSocket, SIGNAL (readyRead()), this, SLOT (slotReadingTcpData()));
    disconnect (tcpSocket, SIGNAL (disconnected()), this, SLOT (slotSockDisc()));
    disconnect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    delete tcpSocket;
    clientConnected = false;

    udpSocket = new QUdpSocket(this);   //coздаëм обьект соkета QUdpSocket
    connect (udpSocket, SIGNAL (readyRead()), this, SLOT (slotReadingUDPData()));  //для получения и отображения данныx соединяем сигнал сокета со слотом
    emit errorSocket("Возникла ошибка при попытке подключения к серверу.\nПожалуйста проверьте, запущен ли сервер.");
}

void Client::slotSockDisc()     //слот-функция для удаления сокета при закрытии приложения
{
    qDebug() << "Deleting tcpSocket...";
    tcpSocket->deleteLater();
}


void Client::displayError(QAbstractSocket::SocketError socketError) //метод для отображения ошибки сокета в случае возникновения таковой
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            emit errorSocket("The host was not found. Please\ncheck the host name and port settings.");
            qDebug() << "The host was not found. Please check the host name and port settings.";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            emit errorSocket("The connection was refused by the peer.\nMake sure the fortune server is running,\nand check that the host name and port settings are correct.");
            qDebug() << "The connection was refused by the peer.";
            qDebug() << "Make sure the fortune server is running, ";
            qDebug() << "and check that the host name and port settings are correct.";
            break;
        default:
        emit errorSocket("The following error occurred:\n" + QString("%1.").arg(tcpSocket->errorString()));
            qDebug() << "The following error occurred: " + QString("%1.").arg(tcpSocket->errorString());
    }
    exit(socketError + 1);
}




