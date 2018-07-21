#ifndef DESCRIPTORSMODEL_H
#define DESCRIPTORSMODEL_H

#include <QAbstractTableModel>
#include <QStandardItemModel>1
#include <QDebug>
#include <QCheckBox>

#include "DescriptorsWidget/obj.h"
#include "DescriptorsWidget/descriptor.h"
#include "Services/stringservice.h"

class DescriptorsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DescriptorsModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int index, Qt::Orientation orient, int role);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole);
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

private:
    QVector<Obj *> objectsVector;

};

#endif // DESCRIPTORSMODEL_H
