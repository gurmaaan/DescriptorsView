//#include "dscrtablemodel.h"

//DscrTableModel::DscrTableModel(QObject *parent)
//    : QAbstractTableModel(parent)
//{
//}

//QVariant DscrTableModel::headerData(int section, Qt::Orientation orientation, int role)
//{
//    if(m_data.count() > 0)
//    {
//        QVariant objectAtSectionFName = QVariant::fromValue(m_data.at(section)->fullName());
//        QVariant objectAtSectionName = QVariant::fromValue(m_data.at(section)->name());
//        QVariant descriptorAtSectionName = m_data.at(0)->descriptors().at(section)->name();

//        switch (role)
//        {
//            case Qt::DisplayRole:
//                return choseCase(orientation, descriptorAtSectionName, objectAtSectionName);
//            case Qt::EditRole:
//                return choseCase(orientation, descriptorAtSectionName, objectAtSectionFName);
//            case Qt::CheckStateRole:
//                return Qt::Unchecked;
//                // TODO: headers resizing
// //            case Qt::SizeHintRole:
// //            {
// //                QSize nsz()
// //            }
//            case Qt::BackgroundRole:
//                return QVariant::fromValue(QBrush(QColor(Qt::lightGray),Qt::Dense7Pattern));
//            case Qt::TextAlignmentRole:
//                return choseCase(orientation, Qt::AlignCenter, Qt::AlignRight + Qt::AlignVCenter);
//            case Qt::FontRole:
//            {
//                QFont bf;
//                bf.setBold(true);
//                return bf;
//            }
//            case Qt::WhatsThisRole:
//                return choseCase(orientation, descriptorAtSectionName, objectAtSectionFName);
//            case Qt::StatusTipRole:
//                return choseCase(orientation, descriptorAtSectionName, objectAtSectionFName);

//        }
//    }
//    return QVariant();
//}

//bool DscrTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    if (value != headerData(section, orientation, role)) {
//        // FIXME: Implement me!
//        emit headerDataChanged(orientation, section, section);
//        return true;
//    }
//    return false;
//}


//int DscrTableModel::rowCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return 0;

//    // FIXME: Implement me!
//}

//int DscrTableModel::columnCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return 0;

//    // FIXME: Implement me!
//}

//QVariant DscrTableModel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    // FIXME: Implement me!
//    return QVariant();
//}

//bool DscrTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (data(index, role) != value) {
//        // FIXME: Implement me!
//        emit dataChanged(index, index, QVector<int>() << role);
//        return true;
//    }
//    return false;
//}

//Qt::ItemFlags DscrTableModel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return Qt::NoItemFlags;

//    return Qt::ItemIsEditable; // FIXME: Implement me!
//}

//bool DscrTableModel::insertRows(int row, int count, const QModelIndex &parent)
//{
//    beginInsertRows(parent, row, row + count - 1);
//    // FIXME: Implement me!
//    endInsertRows();
//}

//bool DscrTableModel::insertColumns(int column, int count, const QModelIndex &parent)
//{
//    beginInsertColumns(parent, column, column + count - 1);
//    // FIXME: Implement me!
//    endInsertColumns();
//}

//QVariant DscrTableModel::choseCase(int orientation, const QVariant &horizontalCase, const QVariant &verticalcase)
//{
//    if (orientation == Qt::Horizontal )
//    {
//        return horizontalCase;
//    } else if ( orientation == Qt::Vertical )
//    {
//        return verticalcase;
//    }
//    return QVariant();
//}
