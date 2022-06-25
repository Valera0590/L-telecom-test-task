#include "algorithms.h"

Algorithm:: Algorithm(QString filepath)
{
    _filepath = filepath;
    QFile file(filepath);

    if (file.exists() == true)  //получение информации о файле
    {
        QFileInfo fileInfo(file);
        _fileSize = fileInfo.size();
        qDebug() << getFileSize() << "bytes";
        decomposeFile();
    }
    else qDebug() << "File not found!";
}
Algorithm:: ~Algorithm(){}

void Algorithm::decomposeFile() //алгоритм разбиения текста из файла на слова
{
    QFile file(getFilepath());
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList allLinesFile;
        allLinesFile.clear();
        while(!file.atEnd())
        {
            //читаем строку
            QString str = file.readLine();
            //Делим строку на слова разделенные пробелом
            QStringList lst = str.split(" ");
            allLinesFile += lst;
              // выводим первых четыре слова
            //qDebug() << lst.at(0) << lst.at(1) << lst.at(2) << lst.at(3);
        }
        allLinesFile.removeAll("");
        foreach (QString temp, allLinesFile)
        {
            //QString temp(var);
            if(temp.contains("\n"))
            {
                int i = allLinesFile.indexOf(temp);
                allLinesFile.removeAt(i);
                temp.chop(1);
                allLinesFile.insert(i,temp);
            }
        }
        Words = allLinesFile;
    }
    else
    {
        qDebug()<< "don't open file";
    }
}

QString Algorithm::getFilepath()
{
    return _filepath;
}

quint64 Algorithm::getFileSize()
{
    return _fileSize;
}





