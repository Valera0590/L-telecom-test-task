#include "valuerepeatsymbol.h"

ValueRepeatSymbol::ValueRepeatSymbol(QString filepath):Algorithm(filepath){}
ValueRepeatSymbol::~ValueRepeatSymbol(){}
void ValueRepeatSymbol::analyzeText()       //анализ текста из файла для вычисления количества повторений каждого символа
{
    valueOfRepeat.clear();
    foreach (QString word, Words)      //разбор каждого слова на символы и заполнение контейнера с кол-вом символов
    {
        while(!word.isEmpty())
        {
            if(word.at(0).isLetter())
            {
                QChar nextCharacter = word.at(0).toLower();
                if(!valueOfRepeat.empty() && valueOfRepeat.contains(nextCharacter))
                {
                    int countCharacter = valueOfRepeat.value(nextCharacter);
                    valueOfRepeat.insert(nextCharacter, ++countCharacter);
                }
                else
                {
                    valueOfRepeat.insert(nextCharacter,1);
                }
            }
            else
            {
                QChar nextCharacter = word.at(0);

                if(!valueOfRepeat.empty() && valueOfRepeat.contains(nextCharacter))
                {
                    int countCharacter = valueOfRepeat.value(nextCharacter);
                    valueOfRepeat.insert(nextCharacter, ++countCharacter);
                }
                else
                {
                    valueOfRepeat.insert(nextCharacter,1);
                }

            }
            word = word.remove(0,1);
        }
    }
        //вывод в консоль
    QMapIterator<QChar, int> i(valueOfRepeat);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key() << " : " << i.value();
    }

}







