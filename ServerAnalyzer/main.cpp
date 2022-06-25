#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "algorithms.h"
#include "valuerepeatsymbol.h"
#include "distributionwordsbylength.h"
#include "server.h"
#include <QtQuickControls2>
#include <QQmlComponent>
#include <QQmlProperty>
#include <QQmlContext>





int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("L-telecom");
    app.setOrganizationDomain("ltelecom.ru");
    QQmlApplicationEngine engine;

    qmlRegisterType<Server>("CPP.MyComponents",1,0,"Server");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    Server serv;


    return app.exec();
}


