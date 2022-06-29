#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "algorithms.h"
#include "valuerepeatsymbol.h"
#include "distributionwordsbylength.h"
#include "server.h"
#include "serverlistener.h"





int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    //app.setOrganizationName("L-telecom");
    //app.setOrganizationDomain("ltelecom.ru");
    QQmlApplicationEngine engine;


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    if(QFile(QDir::currentPath()+"/" DATABASE_NAME).exists())
        QFile(QDir::currentPath()+"/" DATABASE_NAME).remove();
    Server serv;


    return app.exec();
}


