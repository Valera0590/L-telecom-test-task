#ifndef VALUEREPEATSYMBOL_H
#define VALUEREPEATSYMBOL_H
#include "algorithms.h"


    //класс алгоритма определения количества повторений каждого символа
class ValueRepeatSymbol: public Algorithm
{

public:
    qint64 fileSize;
    explicit ValueRepeatSymbol();
    ~ValueRepeatSymbol() override;
    QVariant analyzeText(QString filepath) override;

};

#endif // VALUEREPEATSYMBOL_H
