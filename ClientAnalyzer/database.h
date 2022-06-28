#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "StaticticRequestsDataBase"
#define DATABASE_NAME       "StaticticRequests.db"

#define TABLE                   "StaticticRequestsToAnalyze"         // Название таблицы
#define TABLE_DATETIME          "DateTime"         // Вторая колонка
#define TABLE_IP                "IPAdress"         // Третья колонка
#define TABLE_SIZEFILE          "Sizebytes"        // Четвертая колонка

// Первая колонка содержит Autoincrement ID

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
    */
    void connectToDataBase();

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();        // Открытие базы данных
    bool restoreDataBase();     // Восстановление базы данных
    void closeDataBase();       // Закрытие базы данных
    bool createTable();         // Создание базы таблицы в базе данных

public slots:
    bool inserIntoTable(const QVariantList &data);      // Добавление записей в таблицу
    bool inserIntoTable(const QString &fname, const QString &sname, const QString &nik);
    bool removeRecord(const int id); // Удаление записи из таблицы по её id
    void slotCloseOldDB();
    void slotOpenNewDB();
};

#endif // DATABASE_H
