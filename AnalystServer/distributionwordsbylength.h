#ifndef DISTRIBUTIONWORDSBYLENGTH_H
#define DISTRIBUTIONWORDSBYLENGTH_H

#include "algorithms.h"


    //класс алгоритма распределения слов по их длинам
class DistributionWordsByLength: public Algorithm
{

public:

    explicit DistributionWordsByLength(QString filepath);
    ~DistributionWordsByLength() override;
    void analyzeText() override;    //анализ текста из файла для распрделения слов по длинам
    QMap<int,int> distByLengthWords;    //контейнер для распрделения слов по длинам

private:
};

#endif // DISTRIBUTIONWORDSBYLENGTH_H
