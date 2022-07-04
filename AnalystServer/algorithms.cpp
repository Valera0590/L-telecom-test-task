#include "algorithms.h"

Algorithm:: Algorithm(QString filepath)
{
    _filepath = filepath;
    QFile file(filepath);

    if (file.exists() == true)  //получение информации о файле
    {
        QFileInfo fileInfo(file);
        _fileSize = fileInfo.size();
        qDebug() <<"Size of analyzing file: "<< getFileSize() << "bytes";
        decomposeFileByWords();     //разбиение текста файла на отдельные слова
    }
    else qDebug() << "File not found!";
}
Algorithm:: ~Algorithm(){}

void Algorithm::decomposeFileByWords()  //алгоритм разбиения текста из файла на слова
{
    QFile file(getFilepath());
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList allLinesFile;
        allLinesFile.clear();
        while(!file.atEnd())
        {
            //читаем строку
            QString strLineFile = file.readLine();
            strLineFile = fileFix(strLineFile);
            //Делим строку на слова разделенные пробелом
            QStringList lst = strLineFile.split(" ");
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
        qDebug()<< "Don't open file";
    }
}

QString Algorithm::fileFix(QString oneStringOfFile)     //метод исправления строку файла для дальнейшего разбиения
{
    int i = 0;
        //исключаем варианты строки, когда после/перед некоторого символа(скобки и знаки препинания) не пробел
    while (i<oneStringOfFile.length()-1)
    {
        QChar character = oneStringOfFile.at(i);
        if (character == "(")
        {
                //если перед открывающей скобкой нет пробела
            if(i!=0 && oneStringOfFile.at(i - 1) != " ")
            {
                oneStringOfFile.insert(i," ");
                i+=2;
            }
            else ++i;
        }
        else if(character == ")" || character == "." || character == "," || character == "!"
                || character == "?" || character == ":" || character == ";")
        {
                //если после закрывающей скобки или знака препинания нет пробела
            if(i+1 < oneStringOfFile.length() && oneStringOfFile.at(i+1) != "\n" && oneStringOfFile.at(i + 1) != " ")
            {
                oneStringOfFile.insert(i+1," ");
                i+=2;
            }
            else ++i;
        }
        else ++i;


    }
    return oneStringOfFile;
}

QString Algorithm::getFilepath()
{
    return _filepath;
}

quint64 Algorithm::getFileSize()
{
    return _fileSize;
}






