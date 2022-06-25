#include "distributionwordsbylength.h"

DistributionWordsByLength::DistributionWordsByLength():Algorithm(){}
DistributionWordsByLength::~DistributionWordsByLength(){}
QVariant DistributionWordsByLength::analyzeText(QString filepath)
{
    qDebug() << "DistributionWordsByLength.analyzeText was called.....";
    QFile file(filepath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
            //читаем строку
            QString str = file.readLine();
            //Делим строку на слова разделенные пробелом
            QStringList lst = str.split(" ");
              // выводим первых четыре слова
            qDebug() << lst.at(0) << lst.at(1) << lst.at(2) << lst.at(3);
        }
    }
    else
    {
        qDebug()<< "don't open file";
    }

    QVariant qv;
    return qv;
}
