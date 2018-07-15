#ifndef DESCRIPTORSMODEL_H
#define DESCRIPTORSMODEL_H

#include <QAbstractTableModel>
#include "obj.h"
#include "descriptor.h"
#include"filemanager.h"

class DescriptorsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DescriptorsModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    bool loadDataFromFile(QString fileName);

private:
    QVector<Obj *> objectsVector;

};

#endif // DESCRIPTORSMODEL_H
