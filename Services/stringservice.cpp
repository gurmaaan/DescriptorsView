#include "stringservice.h"

StringService::StringService(QObject *parent) :
    QObject(parent)
{
}

QString StringService::getCornerString(QString fileText)
{
    return getFirstCol(getFirstRow(fileText));
}

QString StringService::getTimeMessage(QTime t1, QTime t2, QString blockName)
{
    int tms1 = t1.second() * 1000 + t1.msec();
    int tms2 = t2.second() * 1000 + t2.msec();
    QString msgTxt = tr("Block \"") + blockName + tr("\" finished in ") + QString::number(tms2 - tms1) + tr(" milliseconds");
    return msgTxt;
}

//FIXME : некорректный парсинг строки стиля
QString StringService::replaceBGC(QString WS, QColor NC, QString BGCS)
{
    //LO=lenghtOf,IO=IindexOf,S=String,W=Word,BGC=background-color,CN=ColorName
    int LOWS = WS.length();
    qInfo() << "Current StyleSheet string: " << WS << "(" << LOWS << " symbols)";
    int IOBGCS = WS.indexOf(BGCS);
    int LOBGCS = BGCS.length();
    QString nCNS = NC.name();
    qInfo() << BGCS << "position " << IOBGCS << "(" << LOBGCS << " symbols)";
    //WS.replace(" ", "");
    QString startS = WS.left(IOBGCS);
    QString endWithCN = WS.right(LOWS - IOBGCS - LOBGCS);
    //o=Old, n=New
    QString oCNS = endWithCN.split(';').first();
    int LOoCNS = oCNS.length();
    QString end = WS.right(LOWS - IOBGCS - LOoCNS);
    qInfo() << "Old colorName" << oCNS << "(" << LOoCNS << " symbols)";
    qInfo() << "End :" << end;
    QString nWS = startS + BGCS + QString(":") + nCNS + QString(";") + end;
    qInfo() << "New StyleSheet string: "<< nWS;
    return nWS;
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

int StringService::maximumLen(QStringList list)
{
    int max = 0;
    foreach(QString str, list)
    {
        if(str.length() > max)
            max = str.length();
    }
    return max;
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

QStringList StringService::splitBySemicolon(QString str)
{
    return str.split(";");
}

QString StringService::getFirstCol(QString str)
{
    return str.split(";").first();
}

QString StringService::getFirstRow(QString str)
{
    return str.split("\n").first();
}

QString StringService::multipleLine(QString str)
{
    int midUnderScore = str.count("_") / 2 + 1;
    int lastUnderScore = str.count("_");
    int underScoreCounter = 0;
    for(int i = 0; i < str.length(); i++)
    {
        if(str.at(i) == "_")
        {
            underScoreCounter++;
            if(underScoreCounter == midUnderScore || underScoreCounter == lastUnderScore)
                str.replace(i, 1, "\n");

        }
    }
    return str;
}

QString StringService::singleLine(QString str)
{
    for(int i = 0; i < str.length(); i++)
    {
        if(str.at(i) == "\n")
            str.replace(i, 1, " ");
    }

    return str;
}
