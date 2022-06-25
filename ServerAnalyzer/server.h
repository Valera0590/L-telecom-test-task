#ifndef SERVER_H
#define SERVER_H
#include "algorithms.h"
#include "valuerepeatsymbol.h"
#include "distributionwordsbylength.h"
#include <QObject>


class Server: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString filepath READ getFilepath WRITE setFilepath NOTIFY filepathChanged)

public:
    explicit Server();
    ~Server();
    QString getFilepath();
    void setFilepath(const QString &filepath);
    QString cutToRigthFilepath(QString fp);

signals:
    void filepathChanged();

public slots:
         // функция публичного слота доступна в QML
    void slotFilepathChange(QString str); // Слот-функция без параметров
    void slotFileReadyForAnalyze();

private:
    QString _filepath;
};

#endif // SERVER_H
