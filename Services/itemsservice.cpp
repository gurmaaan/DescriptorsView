#include "itemsservice.h"

ItemsService::ItemsService(QObject *parent) : QObject(parent)
{

}

void ItemsService::makeAllItemsTextColor(QAbstractItemModel *model, int colorCode)
{
    for(int c = 0; c < model->columnCount(); c++)
        for(int r = 0; r < model->rowCount(); r++)
            model->setData(model->index(r, c), QColor(colorCode), Qt::TextColorRole);
}

void ItemsService::makeFontBold(QStandardItem *item)
{
    item->setFont(QFont(item->font().family(), item->font().pointSize(), QFont::Bold));
}

void ItemsService::alignText(QStandardItem *item, Qt::Alignment flag)
{
    item->setTextAlignment(flag);
}

void ItemsService::changeTextColor(QStandardItem *item, QColor color)
{
    item->setData(color, Qt::TextColorRole);
}

void ItemsService::changeTextColor(QStandardItem *item, int colorCode)
{
    item->setData(QColor(colorCode), Qt::TextColorRole);
}

void ItemsService::changeBgColor(QStandardItem *item, QColor color)
{
    item->setData(color, Qt::BackgroundColorRole);
}

void ItemsService::changeBgColor(QStandardItem *item, int colorCode)
{
    item->setData(QColor(colorCode), Qt::BackgroundColorRole);
}

void ItemsService::makeCheckable(QStandardItem *item, bool state)
{
    item->setEditable(state);
    item->setCheckable(state);
    item->setCheckState(Qt::Unchecked);
}

void ItemsService::addDescription(QStandardItem *item, QString text)
{
    item->setWhatsThis(text);
    item->setStatusTip(text);
}

QString ItemsService::displayingStr(double data)
{
    QString visualData;
    visualData.sprintf("%+06.2f", data);
    return visualData;
}

void ItemsService::makeHHeader(QStandardItem *item)
{
    makeFontBold(item);
    alignText(item, Qt::AlignCenter);
    changeBgColor(item, Qt::gray);
    addDescription(item, item->text());
}

void ItemsService::makeItemTextColor(QAbstractItemModel *model, int r, int c, int colorCode)
{
    model->setData(model->index(r, c), QColor(colorCode), Qt::TextColorRole);
}

//QStandardItemModel *StringService::getCsvModel(QString filePath)
//{
//    QStandardItemModel *csvModel = new QStandardItemModel();
//    QFile file(filePath);

//    if ( !file.open(QFile::ReadOnly | QFile::Text ) )
//    {
//        qDebug() << tr(DOESNT_EXIST);
//        csvModel->setColumnCount(1);
//        return csvModel;
//    } else
//    {
//         QTextStream in(&file);
//#ifdef Q_OS_MAC
//         in.setCodec(QTextCodec::codecForName(ENCODING));
//#endif
//         int rowCnt = 0, colCnt = 0;

//         QString firstLine = in.readLine();
//         emit firstRowColChanged( getFirst(firstLine));

//         QStringList hHStrList = cutAndSplit(firstLine);
//         colCnt = hHStrList.size();
//         emit colCountChanged(colCnt);
//         csvModel->setColumnCount(colCnt);

//        for (int i = 0; i < colCnt; i++)
//        {
//            QString curHStr = hHStrList.at(i);
//            QStandardItem *hHeaderItem = new QStandardItem(curHStr);
//            hHeaderItem->setData(curHStr);
//            hHeaderItem->setStatusTip(curHStr);
//            hHeaderItem->setTextAlignment(Qt::AlignCenter);
//            hHeaderItem->setEditable(false);
//            hHeaderItem->setFont(QFont(hHeaderItem->font().family(), hHeaderItem->font().pointSize(), QFont::Bold));
//           // hHeaderItem->setSizeHint(QSize(100, 30));
//            hHeaderItem->setBackground(QBrush(QColor(Qt::gray)));
//            csvModel->setHorizontalHeaderItem(i, hHeaderItem);

//        }

//         while (!in.atEnd())
//         {
//             QString line = in.readLine() ;
//             emit rowCountChanged(rowCnt++);

//             QString vHStr = getFirst(line);
//             QStandardItem* vHItem = new QStandardItem(vHStr);
//             vHItem->setData(vHStr, Qt::EditRole);
//             vHItem->setData(cutOnset(vHStr), Qt::DisplayRole);
//             vHItem->setData(Qt::Checked, Qt::CheckStateRole);
//             vHItem->setWhatsThis(vHStr);
//             vHItem->setStatusTip(vHStr);
//             vHItem->setTextAlignment(Qt::AlignRight);
//             vHItem->setTextAlignment(Qt::AlignVCenter);
//             vHItem->setFont(QFont(vHItem->font().family(), vHItem->font().pointSize(), QFont::Bold));
//             vHItem->setEditable(false);

//             QStringList itemsStrList = cutAndSplit(line);
//             QList<QStandardItem *> standardItemsList;

//             for (QString itemStr : itemsStrList)
//             {
//                 QStandardItem *item = new QStandardItem(itemStr);

//                 itemStr.replace(",", ".");
//                 double numericValue = itemStr.toDouble();

//                 item->setData(numericValue, Qt::EditRole);
//                 item->setStatusTip(QString::number(numericValue));
//                 item->setWhatsThis(itemStr);

//                 item->setData(itemStr, Qt::DisplayRole);
//                 item->setTextAlignment(Qt::AlignCenter);

//                 standardItemsList.append(item);

//             }
//             csvModel->insertRow(csvModel->rowCount(), standardItemsList);
//             csvModel->setVerticalHeaderItem(csvModel->rowCount() - 1, vHItem);

//         }
//         file.close();
//         return csvModel;
//    }
//}
