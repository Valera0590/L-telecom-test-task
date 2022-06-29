#include "tablemodel.h"

TableModel::TableModel(QObject *parent):QAbstractTableModel(parent)
{
    _modelData.clear();
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
    qDebug() << "data() + col: " + QString("%1").arg(columnId);
    switch (role) {
    //case Qt::DisplayRole:
        //return _modelData.at(index.row()).at(index.column());
    case Key:
    {
        if(index.column() == 0)
        {
            qDebug() <<"("<< index.row() <<";"<<index.column()<<") = "<< _modelData.at(index.row()).at(index.column());
            return _modelData.at(index.row()).at(index.column());
        }
        else break;
    }
    case Value:
    {
        if(index.column() == 0)
        {
            qDebug() <<"("<< index.row() <<";"<<index.column()+1<<") = "<< _modelData.at(index.row()).at(index.column()+1);
            return _modelData.at(index.row()).at(index.column()+1);
        }
        else break;
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
    //return { {Qt::DisplayRole, "display"} };
}


void TableModel::updateModelRep(QStringList tb)
{
    qDebug() << "Udpating ModelRep";

    this->removeRows(0,rowCount(index),index);
    _modelData.clear();
    beginResetModel();

    endResetModel();
    //вывод в консоль
    /*QMapIterator<QChar, int> i(tb);
    while (i.hasNext())
    {
        i.next();
        _modelData.append({QString("%1").arg(i.key()), QString("%1").arg(i.value())});
        //qDebug() << i.key() << " : " << i.value();
    }*/
    int i=0;
    while (i<tb.length())
    {
        //_modelData.append({tb.value(i),tb.value(i+1)});
        qDebug() << tb.value(i) <<":"<<tb.value(i+1);
        //QModelIndex ind;
        //this->data(ind,Qt::DisplayRole);
        beginInsertRows(index(rowCount(),0), rowCount(), rowCount()+ 1);
            // тут вставляете данные
        _modelData.append({tb.value(i),tb.value(i+1)});
        endInsertRows();
        i+=2;
    }
    //qDebug() << QString("%1, %2").arg(this->rowCount()-1).arg(this->columnCount()-1);
    //this->removeRows(0,rowCount(index),index);
    //emit dataChanged(this->index(0,0),this->index(this->rowCount()-1,this->columnCount()-1));
}

void TableModel::updateModelDLen(QStringList tb)
{
    qDebug() << "Udpating ModelDLen";
    _modelData.clear();
    beginResetModel();

    endResetModel();
    //вывод в консоль
    /*QMapIterator<int, int> j(tb);
    while (j.hasNext())
    {
        j.next();
        _modelData.append({QString("%1").arg(j.key()), QString("%1").arg(j.value())});
        //qDebug() <<"There are "<< j.key() << " character words : " << j.value();
    }*/
    int i=0;
    while (i<tb.length())
    {
        //_modelData.append({tb.value(i),tb.value(i+1)});
        beginInsertRows(index(rowCount(),0), rowCount(), rowCount()+ 1);
            // тут вставляете данные

        _modelData.append({tb.value(i),tb.value(i+1)});
        endInsertRows();
        qDebug() << tb.value(i) <<":"<<tb.value(i+1);
        i+=2;
    }
}
