#include "distributionwordsbylength.h"

//DistributionWordsByLength::DistributionWordsByLength():Algorithm(){}
DistributionWordsByLength::DistributionWordsByLength(QString filepath):Algorithm(filepath){}
DistributionWordsByLength::~DistributionWordsByLength(){}
void DistributionWordsByLength::analyzeText()   //анализ текста из файла для распрделения слов по длинам
{
    DistByLengthWords.clear();
    //qDebug() << "DistributionWordsByLength.analyzeText was called....." << getFileSize();
    foreach (QString word, Words)
    {
        int i = 0;
        while(i<word.length())   //избавляемся от всех символов в слове, кроме букв
        {
            if(word.at(i).isLetter())   i++;
            else    word = word.remove(i,1);
        }
        int lengthWord = word.length();
        if (lengthWord > 0)
        {
                //заполняем контейнер, распределяя по кол-ву букв в слове
            if(!DistByLengthWords.empty() && DistByLengthWords.contains(lengthWord))
            {
                int countWord = DistByLengthWords.value(lengthWord);    //кол-во слов с такой же длиной, как текущее
                DistByLengthWords.insert(lengthWord, ++countWord);
            }
            else
            {
                DistByLengthWords.insert(lengthWord,1);
            }
        }
    }
        //вывод в консоль
    QMapIterator<int, int> i(DistByLengthWords);
    while (i.hasNext()) {
        i.next();
        qDebug() <<"There are "<< i.key() << " character words : " << i.value();
    }

}
