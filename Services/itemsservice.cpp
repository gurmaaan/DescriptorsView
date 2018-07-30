#include "itemsservice.h"

ItemsService::ItemsService(QObject *parent) : QObject(parent)
{

}

void ItemsService::makeAllItemsTextColor(QAbstractItemModel *model, QRgb colorCode)
{
    for(int c = 0; c < model->columnCount(); c++)
        for(int r = 0; r < model->rowCount(); r++)
            model->setData(model->index(r, c), QColor(colorCode), Qt::TextColorRole);
}

void ItemsService::makeFontBold(QStandardItem *item)
{
    item->setFont(QFont(item->font().family(), item->font().pointSize(), QFont::Bold));
}

QSize ItemsService::sizeOfOneSymb(QStandardItem *anyItem)
{
    QFont itemFont(anyItem->font().family(), anyItem->font().pointSize());
    QFontMetrics fm(itemFont);
    int w = fm.width(SYMB_MAXSIZE_W);
    int h = fm.height();
    return QSize(w,h);
}

QSize ItemsService::sizeCorrection(QStandardItem *item)
{
    QSize newSize = sizeOfOneSymb(item);
    newSize.setWidth( newSize.width() * static_cast<int>(item->text().length() * 0.75) );
    newSize.setHeight( newSize.height() * 4) ;
    item->setSizeHint(newSize);
    return newSize;
}

void ItemsService::alignText(QStandardItem *item, Qt::AlignmentFlag flag)
{
    item->setTextAlignment(Qt::Alignment(flag));
    item->setData(flag, Qt::TextAlignmentRole);
}

void ItemsService::changeTextColor(QStandardItem *item, QColor color)
{
    item->setData(QBrush(color, Qt::SolidPattern), Qt::ForegroundRole);
}

void ItemsService::changeTextColor(QStandardItem *item, QRgb colorCode)
{
    item->setData(QBrush(QColor(colorCode), Qt::SolidPattern), Qt::ForegroundRole);
}

void ItemsService::changeBgColor(QStandardItem *item, QColor color)
{
    QBrush brush(color, Qt::Dense5Pattern);
    item->setBackground(brush);
}
void ItemsService::changeBgColor(QStandardItem *item, QRgb colorCode)
{
    QBrush brush(QColor(colorCode), Qt::Dense7Pattern);
    item->setBackground(brush);
}

void ItemsService::makeCheckable(QStandardItem *item, bool state)
{
    item->setEditable(state);
    item->setSelectable(state);
    item->setCheckable(state);
    Qt::CheckState checkState = state ? Qt::Checked : Qt::Unchecked;
    item->setCheckState(checkState);
}


void ItemsService::addDescription(QStandardItem *item, QString text)
{
    item->setWhatsThis(text);
    item->setStatusTip(text);
}

QString ItemsService::displayingStr(double data)
{
    QString visualData;
    visualData.sprintf("%06.4f", data);
    return visualData;
}

void ItemsService::makeHHeader(QStandardItem *item)
{
    makeFontBold(item);
    makeCheckable(item, true);
    alignText(item, Qt::AlignCenter);
    changeBgColor(item, Qt::lightGray);
    sizeCorrection(item);
}

void ItemsService::makeVHeader(QStandardItem *item)
{
    makeFontBold(item);
    makeCheckable(item, false);
    alignText(item, Qt::AlignRight);
    changeBgColor(item, Qt::gray);
    sizeCorrection(item);
}

void ItemsService::makeHeader(QStandardItem *item, Qt::Orientation orientation)
{
    Qt::AlignmentFlag flag;
    bool direction = (orientation == Qt::Vertical);
    flag =  direction ? Qt::AlignRight : Qt::AlignCenter;
    alignText(item, flag);
    item->setFlags(Qt::ItemIsUserCheckable);
    makeFontBold(item);
    makeCheckable(item, !direction);
    changeBgColor(item, Qt::lightGray);
    sizeCorrection(item);
}

void ItemsService::makeItemTextColor(QAbstractItemModel *model, int r, int c, QRgb colorCode)
{
    model->setData(model->index(r, c), QColor(colorCode), Qt::TextColorRole);
}
