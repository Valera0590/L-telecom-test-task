#ifndef VALUEREPEATSYMBOL_H
#define VALUEREPEATSYMBOL_H
#include "algorithms.h"


    //класс алгоритма определения количества повторений каждого символа
class ValueRepeatSymbol: public Algorithm
{

public:

    explicit ValueRepeatSymbol(QString filepath);
    ~ValueRepeatSymbol() override;
    void analyzeText() override;    //анализ текста из файла для вычисления количества повторений каждого символа
    QMap<QChar,int> valueOfRepeat;  //контейнер для вычисления количества повторений каждого символа

private:
};

#endif // VALUEREPEATSYMBOL_H
