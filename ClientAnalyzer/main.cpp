#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "client.h"
#include <QtQuickControls2>
#include <QQmlComponent>
#include <QQmlProperty>
#include <QQmlContext>
#include "database.h"
#include "listmodel.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    app.setOrganizationName("L-telecom");
    app.setOrganizationDomain("ltelecom.ru");
    QQmlApplicationEngine engine;

    qmlRegisterType<Client>("CPP.MyComponents",2,0,"Client");
    // Подключаемся к базе данных
    DataBase database;
    if(QFile(QDir::currentPath()+"/" DATABASE_NAME).exists())
        QFile(QDir::currentPath()+"/" DATABASE_NAME).remove();
    database.connectToDataBase();

    // Объявляем и инициализируем модель данных
    ListModel* model = new ListModel();
    Client client;
    // Обеспечиваем доступ к модели и классу для работы с базой данных из QML
    engine.rootContext()->setContextProperty("myModel", model);
    engine.rootContext()->setContextProperty("database", &database);
    engine.rootContext()->setContextProperty("client", &client);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);



    return app.exec();
}
