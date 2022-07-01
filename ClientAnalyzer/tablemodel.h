#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QObject>
#include <QAbstractTableModel>
#include <QDebug>


class TableModel: public QAbstractTableModel
{
    Q_OBJECT
    enum Roles {
        Key = Qt::UserRole + 1,      // уникальный ключ (символ или число)
        Value                     // значение
        /*TableData = Qt::UserRole + 1,      // уникальный ключ (символ или число)
        TableHeader                     // значение*/
    };
public:
    explicit TableModel(QObject *parent = nullptr);
    // Данные, эти три должны быть реализованы
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    /*void updateModelRep(QMap<QChar,int> tb);
    void updateModelDLen(QMap<int,int> tb);*/
    void updateModelRep(QStringList tb);
    void updateModelDLen(QStringList tb);

private:

         // Данные
    QVector<QVector<QString>> _modelData;
};

#endif // TABLEMODEL_H
