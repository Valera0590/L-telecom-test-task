#ifndef ALGORITHM_H
#define ALGORITHM_H
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
    void decomposeFileByWords();   //метод разбиения текста из файла на слова
    QString fileFix(QString oneStringOfFile);   //метод исправления строки файла для дальнейшего разбиения
};
#endif // ALGORITHM_H
