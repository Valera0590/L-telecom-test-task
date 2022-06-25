#ifndef SERVER_H
#define SERVER_H
#include "algorithms.h"
#include "valuerepeatsymbol.h"
#include "distributionwordsbylength.h"
#include <QObject>


class Server: public QObject
{
    Q_OBJECT
        //свойство связывающее
    Q_PROPERTY(QString filepath READ getFilepath WRITE setFilepath NOTIFY filepathChanged)

public:
    explicit Server();
    ~Server();
    QString getFilepath();
    void setFilepath(const QString &filepath);
    QString cutToRigthFilepath(QString fp);     //убирает лишние символы перед действительным путем до файла

signals:
    void filepathChanged();     //сигнал при изменении пути к файлу в коде

public slots:
         // функция публичного слота доступна в QML
    void slotFilepathChange(QString str);   //слот-функция при изменении пути из-под интерфейса
    void slotFileReadyForAnalyze();     //слот-функция для начала анализа файла

private:
    QString _filepath;
};

#endif // SERVER_H
