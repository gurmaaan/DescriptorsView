#include "stringservice.h"

StringService::StringService(QObject *parent) :
    QObject(parent)
{
}

QString StringService::getCornerString(QString fileText)
{
    return getFirstCol(getFirstRow(fileText));
}

QString StringService::cutFilePath(QString longString)
{
    QStringList partsList = longString.split("\\");
    return partsList.last();
}

QString StringService::replaceForDouble(QString &strWithComme)
{
    return strWithComme.replace(",", ".");
}

bool StringService::notEmpty(QString str)
{
    if (str == "" || str == " ")
        return false;
    else
        return true;
}

QStringList StringService::splitAndRemoveFirstColOfFirstRow(QString fileText)
{
    QString first = getFirstRow(fileText);
    QStringList list = first.split(";");
    list.removeFirst();
    return list;
}

QStringList StringService::splitAndRemoveFirstRow(QString fileText)
{
    QStringList list = fileText.split("\n");
    list.removeFirst();
    return list;
}

QString StringService::getFirstCol(QString str)
{
    return str.split(";").first();
}

QString StringService::getFirstRow(QString str)
{
    return str.split("\n").first();
}
