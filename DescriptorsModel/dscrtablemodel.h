//#ifndef DSCRTABLEMODEL_H
//#define DSCRTABLEMODEL_H

//#include <QAbstractTableModel>
//#include <QVariant>

//#include "obj.h"
//#include "descriptor.h"
//#include "Services/stringservice.h"
//#include "Services/itemsservice.h"

//class DscrTableModel : public QAbstractTableModel
//{
//    Q_OBJECT

//public:
//    explicit DscrTableModel(QObject *parent = nullptr);
//    // Header:
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole);
//    QVariant choseCase(int orientation, const QVariant &horizontalCase, const QVariant &verticalcase);

//    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

//    // Basic functionality:
//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

//    // Editable:
//    bool setData(const QModelIndex &index, const QVariant &value,
//                 int role = Qt::EditRole) override;

//    bool loadData(const QVector<Obj*> &objetsVector);

//    Qt::ItemFlags flags(const QModelIndex& index) const override;

//    // Add data:
//    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
//    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

//    // Load from objects vector or static file;

//  //  bool loadFromFile(const QString &fileName, const QChar &delim = 0);
//    bool loadFromVector(const QVector<Obj*> &data, const QString &format);

//private:
//    QVector<Obj*> m_data;
//};

//#endif // DSCRTABLEMODEL_H
