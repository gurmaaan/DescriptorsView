#ifndef ITEMSSERVICE_H
#define ITEMSSERVICE_H

#include <QObject>
#include <QDebug>
#include <QAbstractItemModel>
#include <QStandardItem>
#include <QColor>

class ItemsService : public QObject
{
    Q_OBJECT
public:
    explicit ItemsService(QObject *parent = nullptr);

    static void makeFontBold(QStandardItem *item);
    static void alignText(QStandardItem *item, Qt::Alignment flag);

    static void changeTextColor(QStandardItem *item, QColor color);
    static void changeTextColor(QStandardItem *item, int colorCode);

    static void changeBgColor(QStandardItem *item, QColor  color);
    static void changeBgColor(QStandardItem *item, int colorCode);

    static void makeCheckable(QStandardItem  *item, bool state);

    static void addDescription(QStandardItem *item, QString text);

    static QString displayingStr(double data);

    static void makeHHeader(QStandardItem *item);

    void makeItemTextColor(QAbstractItemModel *model, int r, int c, int colorCode);
    void makeAllItemsTextColor(QAbstractItemModel *model, int colorCode);

signals:

public slots:
};

#endif // ITEMSSERVICE_H
