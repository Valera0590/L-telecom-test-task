#include "server.h"


Server::Server()
{
        //связывание сигнала о новом файле со слотом анализа файла
    connect(this, SIGNAL(filepathChanged()), this, SLOT(slotFileReadyForAnalyze()));
}
Server::~Server(){}

QString Server::getFilepath()
{
    return _filepath;
}

void Server::setFilepath(const QString &filepath)
{
    qDebug() << "Path:  " << filepath;
    _filepath = filepath;
    emit filepathChanged();
}

QString Server::cutToRigthFilepath(QString fp)  //убирает лишние символы перед действительным путем до файла
{
    QString rightFilepath = fp.remove(0,6);
    setFilepath(rightFilepath);
    return rightFilepath;
}

void Server::slotFilepathChange(QString str)    //слот-функция при изменении пути из-под интерфейса
{
    qDebug() << "slotFilepathChange " << str;
    cutToRigthFilepath(str);
}

void Server::slotFileReadyForAnalyze()      //слот-функция для начала анализа файла
{
    QString filepth = getFilepath();
    Algorithm* alg1 = new ValueRepeatSymbol(filepth);
    alg1->analyzeText();
    alg1 = new DistributionWordsByLength(filepth);
    alg1->analyzeText();
}


