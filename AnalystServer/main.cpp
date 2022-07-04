#include <QCoreApplication>
#include "algorithms.h"
#include "valuerepeatsymbol.h"
#include "distributionwordsbylength.h"
#include "server.h"
#include "serverlistener.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


        //удаляем файл с базой данных, если он уже был создан в текщей директории
    if(QFile(QDir::currentPath()+"/" DATABASE_NAME).exists())
        QFile(QDir::currentPath()+"/" DATABASE_NAME).remove();
    Server serv;


    return a.exec();
}
