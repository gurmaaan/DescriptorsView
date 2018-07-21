#ifndef ITEMSSERVICE_H
#define ITEMSSERVICE_H

#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QColor>
#include <QFontMetrics>

#include "static.h"

class ItemsService : public QObject
{
    Q_OBJECT
public:
    explicit ItemsService(QObject *parent = nullptr);

    static void makeFontBold(QStandardItem *item);

    static QSize sizeOfOneSymb(QStandardItem *anyItem);
    static QSize sizeCorrection(QStandardItem *item);
    static void alignText(QStandardItem *item,  Qt::AlignmentFlag flag);

    static void changeTextColor(QStandardItem *item, QColor color);
    static void changeTextColor(QStandardItem *item, QRgb colorCode);

    static void changeBgColor(QStandardItem *item, QColor  color);
    static void changeBgColor(QStandardItem *item, QRgb colorCode);

    static void makeCheckable(QStandardItem  *item, bool state);

    static void addDescription(QStandardItem *item, QString text);

    static QString displayingStr(double data);

    static void makeHHeader(QStandardItem *item);

    void makeItemTextColor(QAbstractItemModel *model, int r, int c, QRgb colorCode);
    void makeAllItemsTextColor(QAbstractItemModel *model, QRgb colorCode);

signals:
    void sendStatusMessage(QString msgTxt);

public slots:
};

#endif // ITEMSSERVICE_H
