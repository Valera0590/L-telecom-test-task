#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QVariant>
#include <QFile>
#include <QFileInfo>
#include <QDebug>


    //базовый абстрактный класс для алгоритма
class Algorithm
{

public:
    qint64 fileSize;
    QVariant Words;
    Algorithm();
    virtual ~Algorithm() = 0;
    virtual QVariant analyzeText(QString filepath);
};



#endif // ALGORITHMS_H
