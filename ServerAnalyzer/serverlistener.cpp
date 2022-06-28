#include "serverlistener.h"

ServerListener::ServerListener(quint16 port)
{
    filePath.clear();
    fileSize = 0;
    tmpBlock.clear();
    fileCopy = QDir::currentPath()+"/"; // временная замена имени файла
    qDebug() << fileCopy;
    startTcpServerListening(port);
    if(QFile(QDir::currentPath()+"/" DATABASE_NAME).exists())
        QFile(QDir::currentPath()+"/" DATABASE_NAME).remove();
    database.connectToDataBase();
}

ServerListener::~ServerListener(){}


void ServerListener::incomingConnection(qintptr socketDescriptor)
{
    tcpSocket = new QTcpSocket(this);
    tcpSocket->setSocketDescriptor(socketDescriptor);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(slotReadyReadTcp()));   //связь события получения сообщения с обработчиком
    //Sockets.push_back(tcpSocket);
    qDebug()<<"";
    qDebug()<<"Client connected by tcp with socket descriptor: " << socketDescriptor;
    sendToClients("You were connecting");
    qDebug() << "Send client message about successfully connection";
}

void ServerListener::startTcpServerListening(quint16 port)
{
    if(this->listen(QHostAddress::Any, port))  //задаем TcpSocket прослушивать сообщения с любого адреса по порту 2225
    {
        qDebug() << "\nServer start listening tcp socket with port: "<<port;
    }
    else
    {
        qDebug() << "\nError listening tcp socket with port: "<<port;
    }
}

void ServerListener::slotReadyReadTcp()
{
    tcpSocket = (QTcpSocket*) QObject::sender();    //получение сокета, по которому пришло сообщение
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    if(in.status() == QDataStream::Ok)
    {

        if (!isDownloading) //если файл ещё не скачивается
        {
            qDebug()<<"";
            qDebug() << "read...........";
            QString str;
            in.startTransaction();
            in >> str;
            if (!in.commitTransaction()) {
                qDebug() << "SERVER: Str - FAIL commitTransaction";
                return;
            }
            QStringList strList = str.split(";");
            if(strList.value(0) == "request data")
            {
                QHostAddress ipSender = tcpSocket->localAddress();
                QDate date = QDate::currentDate();
                QTime time = QTime::currentTime();
                qDebug() <<str;
                QString toClientString = "database;"+ipSender.toString()+";"+QString("%1").arg(date.day())+QString(".%1").arg(date.month())+QString(".%1").arg(date.year()) +"/"+time.toString();
                qDebug() << "Message to client "+ toClientString;
                //toClientString.prepend("database;");
                sendToClients(toClientString);

                sendFile = new QFile(QDir::currentPath()+"/"+DATABASE_NAME);
                timer = new QTimer(this);
                connect(timer, SIGNAL(timeout()), this, SLOT(timeoutToSendFile())); // Подключаем сигнал таймера к нашему слоту
                timer->start(500);      //ставим задержку в полсекунды перед отправкой клиенту базы данных
            }
            else if(strList.value(0) == "file to analyze") //запрос на анализ файла на сервер от клиента
            {
                //====================================================
                    // Получение filePath и fileSize
                    isDownloading = true;
                    fileSize = 0;
                    QHostAddress ipSender = tcpSocket->peerAddress();
                    QString tmpFlpth = strList.value(1);
                    QStringList tmpFlNm = tmpFlpth.split("/");
                    if(!tmpFlNm.isEmpty())  flNm = tmpFlNm.last();
                    else return;
                    filePath = fileCopy + flNm;

                    if (QFile::exists(filePath))
                        if (!QFile::remove(filePath))
                            qFatal("File not remove!");
                    qDebug() << "Server was starting get file: "+filePath+" from client "+ipSender.toString();
            }
        }
        else
        {
            //====================================================
            // Получение файла
            in.startTransaction();
            in >> tmpBlock;
            if (!in.commitTransaction())    //ждём полной передачи файла через сокет
                return;

            QFile file(filePath);
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
            qDebug() << "SERVER: END - bytesAvailable:" << tcpSocket->bytesAvailable();
            QFileInfo fileInfo(file);
            fileSize = fileInfo.size();
            QHostAddress ipSender = tcpSocket->peerAddress();
            QStringList strIP = ipSender.toString().split(":");
            QString ips = strIP.last();         //ip адрес отправителя
            QDate date = QDate::currentDate();
            QTime time = QTime::currentTime();
            QString DT = QString("%1").arg(date.day())+QString(".%1").arg(date.month())+QString(".%1").arg(date.year()) +"/"+time.toString();
            database.inserIntoTable(DT,ips,QString::number((long)fileSize));

            // Очистка переменных
            tmpBlock.clear();
            isDownloading = false;
            qDebug()<<"";
            qDebug() << "Send to clients info about file "+flNm;
            slotFileReadyForAnalyze();
            sendToClients("fileInfo;"+flNm+";"+QString::number((long)fileSize));
            timer = new QTimer(this);
            connect(timer,SIGNAL(timeout()),this,SLOT(sendToClients()));
            timer->start(100);
            fileCopy = QDir::currentPath()+"/"; // временная замена имени файла
            filePath.clear();
        }
    }
    else
    {
        qDebug() << "\nDataStream error";
    }

}

void ServerListener::slotFileReadyForAnalyze()      //слот-функция для начала анализа файла
{
    Algorithm* alg1 = new ValueRepeatSymbol(filePath);
    alg1->analyzeText();
    ValueRepeatSymbol* vl = dynamic_cast< ValueRepeatSymbol* >(alg1);
    valueofrepeat = vl->valueOfRepeat;
    alg1 = new DistributionWordsByLength(filePath);
    alg1->analyzeText();
    DistributionWordsByLength* dslen = dynamic_cast< DistributionWordsByLength* >(alg1);
    distbylength = dslen->distByLengthWords;
}
void ServerListener::sendToClients(QString str)
{
    QDataStream stream(tcpSocket);
    stream.setVersion(QDataStream::Qt_5_12);

    stream << str;
    tcpSocket->waitForBytesWritten();
    /*Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << str;
    tcpSocket->write(Data);*/

}
void ServerListener::sendToClients()
{
    QDataStream stream(tcpSocket);
    stream.setVersion(QDataStream::Qt_5_12);

    stream << valueofrepeat;
    stream << distbylength;
    tcpSocket->waitForBytesWritten();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(sendToClients()));
}

void ServerListener::sendFullFile()
{
    QDataStream stream(tcpSocket);
    stream.setVersion(QDataStream::Qt_5_12);

    if(sendFile->open(QFile::ReadOnly))
    {
        QByteArray dataS = sendFile->readAll();
        stream << dataS;
        tcpSocket->waitForBytesWritten();
        qDebug() << "_SERVER: File end!";
        sendFile->close();
        sendFile = NULL;
        qDebug() << "_SERVER: File send FINISH!";
    } else {
        qFatal("_SERVER: File not open!");
    }

}

void ServerListener::timeoutToSendFile()
{
    sendFullFile();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(timeoutToSendFile()));
}


