#include "valuerepeatsymbol.h"

ValueRepeatSymbol::ValueRepeatSymbol():Algorithm(){}
ValueRepeatSymbol::~ValueRepeatSymbol(){}
QVariant ValueRepeatSymbol::analyzeText(Algorithm *alg, QFile file)
{
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
            //читаем строку
            QString str = file.readLine();
            //Делим строку на слова разделенные пробелом
            QStringList lst = str.split(" ");
              // выводим первых три слова
            qDebug() << lst.at(0) << lst.at(1)<< lst.at(2);
        }
    }
    else
    {
        qDebug()<< "don't open file";
    }
    QVariant qv1;
    return qv1;
}







