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

private:
    QMap<int,int> DistByLengthWords;    //контейнер для распрделения слов по длинам
};

#endif // DISTRIBUTIONWORDSBYLENGTH_H
