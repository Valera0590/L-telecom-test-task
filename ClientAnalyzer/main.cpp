#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "client.h"
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

    qmlRegisterType<Client>("CPP.MyComponents",2,0,"Client");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    Client client;

    return app.exec();
}
