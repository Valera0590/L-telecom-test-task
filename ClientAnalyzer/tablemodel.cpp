#include "tablemodel.h"

TableModel::TableModel(QObject *parent):QAbstractTableModel(parent)
{
    _modelData.clear();
    //_modelData.append({"Header 1", "Header 2"});
    _modelData.append({"Пусто1", "Пусто2"});
    qDebug() << "Constructor(empty)";
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
    QString column = QString("%1").arg(columnId);
    qDebug() << "data() + col: " + column;
    switch (role) {
    //case Qt::DisplayRole:
        //return _modelData.at(index.row()).at(index.column());
    case Key:
    {
        qDebug() <<"Key ("<< index.row() <<";"<<column<<") = "<< _modelData.at(index.row()).at(columnId);
        return _modelData.at(index.row()).at(columnId);
    }
    case Value:
    {
        qDebug() <<"Value ("<< index.row() <<";"<<column<<") = "<< _modelData.at(index.row()).at(columnId);
        return _modelData.at(index.row()).at(columnId);
    }
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    qDebug() << "roleNames()";
    QHash<int, QByteArray> roles;
    roles[Key] = "Key";
    roles[Value] = "Value";
    return roles;
    /*QHash<int, QByteArray> roles;
    roles[TableData] = "tabledata";
    roles[TableHeader] = "header";
    return roles;*/
    //return { {Qt::DisplayRole, "display"} };
}


void TableModel::updateModelRep(QStringList tb)
{
    qDebug() << "Udpating ModelRep";

    //this->removeRows(0,rowCount(index),index);

    beginResetModel();
    _modelData.clear();

    //вывод в консоль

    //_modelData.append({"Header 1", "Header 2"});
    int i=0;
    while (i<tb.length())
    {
        //qDebug() << tb.value(i) <<":"<<tb.value(i+1);
        //QModelIndex ind;
        //this->data(ind,Qt::DisplayRole);
        //beginInsertRows(index(rowCount(),0), rowCount(), rowCount()+ 1);
            // тут вставляете данные
        _modelData.append({tb.value(i),tb.value(i+1)});
        //endInsertRows();
        i+=2;
    }
    endResetModel();
    //qDebug() << QString("%1, %2").arg(this->rowCount()-1).arg(this->columnCount()-1);
    //this->removeRows(0,rowCount(index),index);
    //emit dataChanged(this->index(0,0),this->index(this->rowCount()-1,this->columnCount()-1));
}

void TableModel::updateModelDLen(QStringList tb)
{
    qDebug() << "Udpating ModelDLen";

    beginResetModel();
    _modelData.clear();

        //_modelData.append({"Header 1", "Header 2"});
    int i=0;
    while (i<tb.length())
    {
        //_modelData.append({tb.value(i),tb.value(i+1)});
        //beginInsertRows(index(rowCount(),0), rowCount(), rowCount()+ 1);
            // тут вставляете данные

        _modelData.append({tb.value(i),tb.value(i+1)});
        //endInsertRows();
        //qDebug() << tb.value(i) <<":"<<tb.value(i+1);
        i+=2;
    }
    endResetModel();
}

