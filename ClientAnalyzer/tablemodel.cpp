#include "tablemodel.h"

TableModel::TableModel(QObject *parent):QAbstractTableModel(parent)
{
    _modelData.clear();
    //_modelData.append({"Пусто1", "Пусто2"});
    //qDebug() << "Constructor(empty)";
}

int TableModel::rowCount(const QModelIndex &) const
{
    return _modelData.size();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return _modelData.at(0).size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    // Определяем номер колонки, адрес так сказать, по номеру роли
    int columnId = role - Qt::UserRole - 1;
    //QString column = QString("%1").arg(columnId);
    //qDebug() << "data() + col: " + column;
    switch (role) {
    case Key:
    {
        //qDebug() <<"Key ("<< index.row() <<";"<<column<<") = "<< _modelData.at(index.row()).at(columnId);
        return _modelData.at(index.row()).at(columnId);
    }
    case Value:
    {
        //qDebug() <<"Value ("<< index.row() <<";"<<column<<") = "<< _modelData.at(index.row()).at(columnId);
        return _modelData.at(index.row()).at(columnId);
    }
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    //qDebug() << "roleNames()";
    QHash<int, QByteArray> roles;
    roles[Key] = "Key";
    roles[Value] = "Value";
    return roles;
}


void TableModel::updateModelValueRepeat(QStringList tb)
{
    qDebug() << "Udpating ModelRep";

    beginResetModel();
    _modelData.clear();
    int i=0;
    while (i<tb.length())
    {
        _modelData.append({tb.value(i),tb.value(i+1)});
        i+=2;
    }
    endResetModel();
}

void TableModel::updateModelWordsByLength(QStringList tb)
{
    qDebug() << "Udpating ModelDLen";

    beginResetModel();
    _modelData.clear();
    int i=0;
    while (i<tb.length())
    {
        _modelData.append({tb.value(i),tb.value(i+1)});
        i+=2;
    }
    endResetModel();
}

