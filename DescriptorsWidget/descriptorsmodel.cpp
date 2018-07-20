#include "descriptorsmodel.h"

DescriptorsModel::DescriptorsModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant DescriptorsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role) {
        case Qt::TextAlignmentRole:
        {
            if (orientation == Qt::Vertical)
                return Qt::AlignRight;
        }
            break;
//        case Qt::DisplayRole:
//        {
//            return StringService::cutFilePath(objectsVector.at(section)->name());
//        }
        default:
        {
            return QVariant();
        }
    }

    return QVariant();
}

//bool DescriptorsModel::setHeaderData(int index, Qt::Orientation orient, int role)
//{
//    if(orient == Qt::Horizontal)
//    {
//        return QAbstractTableModel::setHeaderData(index, orient, role);

//    }else if (orient == Qt::Vertical)
//    {

//    }
//}

int DescriptorsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return objectsVector.count();
}

int DescriptorsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return objectsVector.at(0)->descriptors().count();
}

QVariant DescriptorsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int rI = index.row();
    int cJ = index.column();

    switch (role) {
    case Qt::DisplayRole:
    {
        QString visualData;
        visualData.sprintf("%+06.2f", objectsVector.at(rI)->descriptors().at(cJ)->data());
        return visualData;
    }
    case Qt::EditRole:
        return objectsVector.at(rI)->descriptors().at(cJ)->data();
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
    default:
        return QVariant();
    }
}

bool DescriptorsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int rER = index.row();
    int cER = index.column();

    if(role == Qt::EditRole)
    {
        objectsVector.at(rER)->descriptors().at(cER)->setData(value.toDouble());
        return true;
    } else if (role == Qt::DisplayRole)
    {
        objectsVector.at(rER)->descriptors().at(cER)->setData(value.toDouble());
        return true;
    } else
        return false;

}
