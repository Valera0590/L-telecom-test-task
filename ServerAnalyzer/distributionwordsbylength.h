#ifndef DISTRIBUTIONWORDSBYLENGTH_H
#define DISTRIBUTIONWORDSBYLENGTH_H
#include "algorithms.h"


    //класс алгоритма распределения слов по их длинам
class DistributionWordsByLength: public Algorithm
{

public:
    qint64 fileSize;
    explicit DistributionWordsByLength();
    ~DistributionWordsByLength() override;
    QVariant analyzeText(QString filepath) override;
};

#endif // DISTRIBUTIONWORDSBYLENGTH_H
