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

QString StringService::changeCSSClrProp(QString stylesheetStr, QRgb newPropVal, QString cssPropName)
{
    QString newCSSStr = "";
    QStringList cssPropList = stylesheetStr.split(";");
    foreach (QString prop, cssPropList)
    {
        QStringList propNameValList = prop.split(":");
        QString propName = propNameValList.first().replace(" ", "");
        QString propVal = (propName == cssPropName) ?
                          QColor(newPropVal).name() :
                          propNameValList.last().replace(" ", "");
        newCSSStr += (propName + ":" + propVal + ";");
        qDebug() << newCSSStr;
    }
    return newCSSStr;
}

QRgb StringService::getCSSClrProp(QString stylesheetStr, QString cssPropName)
{
    QRgb clrCode = QColor(255,255,255).rgb();
    QStringList stylePartdsList = stylesheetStr.split(";");
    for(QString clrPart : stylePartdsList)
    {
        QStringList paramWithVal = clrPart.split(":");
        if(paramWithVal.first().replace(" ", "") == cssPropName)
        {
            QString btnClrStr = paramWithVal.last(); // rgb(100, 100, 100)
            btnClrStr.replace(" ", ""); //rgb(100,100,100)
            btnClrStr.replace("rgb(", ""); //100,100,100)
            btnClrStr.replace(")", ""); //100,100,100

            int clrCompnts[3];
            QStringList components = btnClrStr.split(",");
            bool compInt = false;

            if(components.count() == 3)
            {
                for(int i = 0; i < components.count() ; i++)
                    clrCompnts[i] = components.at(i).toInt(&compInt);
            }
            QColor btnClr = QColor(clrCompnts[0], clrCompnts[1], clrCompnts[2]).isValid();
            if(compInt && (components.count() == 3) && btnClr.isValid())
            {
                clrCode = btnClr.rgb();
                break;
            }

            else
                clrCode = QColor(Qt::red).rgb();
        }
    }
    return clrCode;
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

QString StringService::multipleLine(QString str, QChar delimetr)
{
    int midUnderScore = str.count(delimetr) / 2 + 1;
    int lastUnderScore = str.count(delimetr );
    int underScoreCounter = 0;
    for(int i = 0; i < str.length(); i++)
    {
        if(str.at(i) == delimetr)
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
