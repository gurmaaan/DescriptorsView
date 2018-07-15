#include "descriptorsmodel.h"

DescriptorsModel::DescriptorsModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant DescriptorsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int DescriptorsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int DescriptorsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant DescriptorsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

bool DescriptorsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}
