#include "server.h"


Server::Server()
{
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

QString Server::cutToRigthFilepath(QString fp)
{
    QString rightFilepath = fp.remove(0,6);
    qDebug() << rightFilepath;
    setFilepath(rightFilepath);
    return rightFilepath;
}

void Server::slotFilepathChange(QString str)
{
    qDebug() << "slotFilepathChange " << str;
    cutToRigthFilepath(str);

}

void Server::slotFileReadyForAnalyze()
{
    Algorithm* alg1 = new ValueRepeatSymbol;
    QVariant result1 = alg1->analyzeText(getFilepath());
    alg1 = new DistributionWordsByLength;
    QVariant result2 = alg1->analyzeText(getFilepath());
}


