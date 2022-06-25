#include "algorithms.h"

Algorithm:: Algorithm(){}
Algorithm:: ~Algorithm(){}
QVariant Algorithm::analyzeText(QString filepath)
{
    QFile file(filepath);
    if (file.exists() == true)
    {
        QFileInfo fileInfo(file);
        fileSize = fileInfo.size();
        qDebug() << fileSize << "bytes";

    }
    else qDebug() << "File not found!";
    QVariant qv2;
    return qv2;
}





