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
    Algorithm();
    virtual ~Algorithm() = 0;
    virtual QVariant analyzeText(Algorithm* alg, QFile file) = 0;
};



#endif // ALGORITHMS_H
