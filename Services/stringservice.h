#ifndef STRINGSERVICE_H
#define STRINGSERVICE_H

#include <QString>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QObject>
#include <QTime>
#include <QDebug>

#include "static.h"

class StringService : public QObject
{
    Q_OBJECT
public:
    explicit StringService(QObject *parent = nullptr);

    static QString getCornerString(QString fileText);
    static QString getTimeMessage(QTime t1, QTime t2, QString blockName = "");

    static QString changeCSSClrProp(QString stylesheetStr, QRgb newPropVal, QString cssPropName = CSSBGCLR);
    static QRgb getCSSClrProp(QString stylesheetStr, QString cssPropName);
    
    static QString getFirstCol(QString str);
    static QString getFirstRow(QString str);

    static QString multipleLine(QString str, QChar delimetr = '_');
    static QString singleLine(QString str);

    QStringList splitAndRemoveFirstColOfFirstRow(QString fileText);
    QStringList splitAndRemoveFirstRow(QString fileText);
    QStringList splitBySemicolon(QString str);

    static QString cutFilePath(QString longString);

    static QString replaceForDouble(QString &strWithComme);
    static bool notEmpty(QString str);

    static int maximumLen(QStringList list);

private:



};

#endif // STRINGSERVICE_H
