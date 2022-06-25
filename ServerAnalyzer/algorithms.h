#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QFile>
#include <QFileInfo>
#include <QDebug>


    //базовый абстрактный класс для алгоритма анализа тектового файла
class Algorithm
{

public:
    Algorithm(QString filepath);
    virtual ~Algorithm() = 0;
    QStringList Words;  //список слов
    QString getFilepath();
    quint64 getFileSize();
    virtual void analyzeText() = 0;


private:
    quint64 _fileSize;
    QString _filepath;
    void decomposeFile();   //алгоритм разбиения текста из файла на слова
};



#endif // ALGORITHMS_H
