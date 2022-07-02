#include "serverlistener.h"

ServerListener::ServerListener(quint16 port)
{
    filePath.clear();
    fileSize = 0;
    tmpBlock.clear();
    fileCopy = QDir::currentPath()+"/"; // временная замена имени файла
    qDebug() <<"Директория с местом хранения базы данных и полученных файлов:\n"<< fileCopy;
    startTcpServerListening(port);
    database.connectToDataBase();
}

ServerListener::~ServerListener(){}


void ServerListener::incomingConnection(qintptr socketDescriptor)   //обработчик входящего подключения по TCP сокету
{
    tcpSocket = new QTcpSocket(this);
    tcpSocket->setSocketDescriptor(socketDescriptor);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(slotReadyReadTcp()));   //связь события получения сообщения с обработчиком
    qDebug()<<"";
    qDebug()<<"Client connected by tcp with socket descriptor: " << socketDescriptor;
    sendToClient("You were connecting");
    qDebug() << "Send client message about successfully connection";
}

void ServerListener::startTcpServerListening(quint16 port)  //метод запуска прослушивания TCP сокета
{
    if(this->listen(QHostAddress::Any, port))  //задаем TcpSocket прослушивать сообщения с любого адреса по порту port
    {
        qDebug() << "\nServer start listening tcp socket with port: "<<port;
    }
    else
    {
        qDebug() << "\nError listening tcp socket with port: "<<port;
    }
}

void ServerListener::slotReadyReadTcp()     //метод чтения данных по TCP сокету
{
    tcpSocket = (QTcpSocket*) QObject::sender();    //получение сокета, по которому пришло сообщение
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    if(in.status() == QDataStream::Ok)
    {

        if (!isDownloading) //если файл ещё не скачивается
        {
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
                /*QHostAddress ipSender = tcpSocket->localAddress();
                QDate date = QDate::currentDate();
                QTime time = QTime::currentTime();
                qDebug() <<str;*/
                QString toClientString = "database";/*+ipSender.toString()+";"+QString("%1").arg(date.day())+QString(".%1").arg(date.month())+QString(".%1").arg(date.year()) +"/"+time.toString();*/
                //qDebug() << "Message to client "+ toClientString;
                //toClientString.prepend("database;");
                sendToClient(toClientString);

                sendFile = new QFile(QDir::currentPath()+"/"+DATABASE_NAME);
                timer = new QTimer(this);
                connect(timer, SIGNAL(timeout()), this, SLOT(timeoutToSendDatabase())); // Подключаем сигнал таймера к нашему слоту
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
                    qDebug() << "Server was starting get file: "+flNm+" from client "+ipSender.toString().split(":").last();
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
                //получение информации о файле, клиенте и времени запроса для записи в БД
            QFileInfo fileInfo(file);
            fileSize = fileInfo.size();
            QHostAddress ipSender = tcpSocket->peerAddress();
            QString ips  = ipSender.toString().split(":").last();           //ip адрес отправителя
            QDate date = QDate::currentDate();
            QTime time = QTime::currentTime();
            QString DT = QString("%1").arg(date.day())+QString(".%1").arg(date.month())+QString(".%1").arg(date.year()) +"/"+time.toString();
            database.inserIntoTable(DT,ips,QString::number((long)fileSize));

            // Очистка переменных
            tmpBlock.clear();
            isDownloading = false;
            qDebug()<<"";
            qDebug() << "Send to clients info about file "+flNm;
                //применение методов анализа файла и отправка данных клиенту, который запрашивал анализ
            slotFileReadyForAnalyze();
            sendToClient("fileInfo;"+flNm+";"+QString::number((long)fileSize));
            timer = new QTimer(this);
            connect(timer,SIGNAL(timeout()),this,SLOT(sendToClient()));
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
        //применение алогоритмов анализа
    Algorithm* algtithms = new ValueRepeatSymbol(filePath);
    algtithms->analyzeText();
    ValueRepeatSymbol* valueOfRepeatPointer = dynamic_cast< ValueRepeatSymbol* >(algtithms);   //преобразование с проверкой на корректность такого присваивания
    valueofrepeat = valueOfRepeatPointer->valueOfRepeat;
    algtithms = new DistributionWordsByLength(filePath);
    algtithms->analyzeText();
    DistributionWordsByLength* distWordsByLengthPointer = dynamic_cast< DistributionWordsByLength* >(algtithms);    //преобразование с проверкой на корректность такого присваивания
    distbylength = distWordsByLengthPointer->distByLengthWords;
}
void ServerListener::sendToClient(QString str)     //отправка клиенту сообщения str
{
    QDataStream stream(tcpSocket);
    stream.setVersion(QDataStream::Qt_5_12);

    stream << str;
    tcpSocket->waitForBytesWritten();

}
void ServerListener::sendToClient()        //отправка клиенту результата анализа текста
{
    QDataStream stream(tcpSocket);
    stream.setVersion(QDataStream::Qt_5_12);

    stream << valueofrepeat;
    stream << distbylength;
    tcpSocket->waitForBytesWritten();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(sendToClient()));
}

void ServerListener::sendDatabase()     //отправка клиенту базы данных
{
    QDataStream stream(tcpSocket);
    stream.setVersion(QDataStream::Qt_5_12);

    if(sendFile->open(QFile::ReadOnly))
    {
        QByteArray dataS = sendFile->readAll();
        stream << dataS;
        tcpSocket->waitForBytesWritten();
        sendFile->close();
        sendFile = NULL;
        qDebug() << "_SERVER: File DataBase send FINISH!";
    } else {
        qFatal("_SERVER: File DataBase not open!");
    }

}

void ServerListener::timeoutToSendDatabase()    //обработчик по окончании времени таймера
{
    sendDatabase();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(timeoutToSendDatabase()));
}


