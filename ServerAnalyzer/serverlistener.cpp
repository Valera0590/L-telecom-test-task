#include "serverlistener.h"

ServerListener::ServerListener(quint16 port)
{
    filePath.clear();
    fileSize = 0;
    tmpBlock.clear();
    fileCopy = QDir::tempPath()+"/"; // временная замена имени файла
    qDebug() << fileCopy;
    startTcpServerListening(port);
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
                QDateTime time = QDateTime::currentDateTimeUtc();
                qDebug() <<str;
                QString toClientString = ipSender.toString()+";"+time.toString();
                qDebug() << "Message by "+ toClientString;
                toClientString.prepend("database;");
                sendToClients(toClientString);
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

            // Очистка переменных
            tmpBlock.clear();
            isDownloading = false;
            qDebug()<<"";
            qDebug() << "Send to clients info about file "+flNm;
            slotFileReadyForAnalyze();
            sendToClients("fileInfo;"+flNm+";"+QString::number((long)fileSize));
            fileCopy = QDir::tempPath()+"/"; // временная замена имени файла
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
    alg1 = new DistributionWordsByLength(filePath);
    alg1->analyzeText();
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




