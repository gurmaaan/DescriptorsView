#include "filemanager.h"
#include <QString>

FileManager::FileManager(QObject *parent) :
    QObject(parent)
{
}

QString FileManager::getOpenedFilePath()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    tr("Select Attributes file"),
                                                    requiredPath(QDir::current(), DATA_PATH),
                                                    FILE_TYPE);
    return  fileName;
}

QStandardItemModel *FileManager::getCsvModel(QString filePath)
{
    QStandardItemModel *csvModel = new QStandardItemModel();
    QFile file(filePath);

    if ( !file.open(QFile::ReadOnly | QFile::Text ) )
    {
        qDebug() << tr("File not exists");
        csvModel->setColumnCount(1);
        return csvModel;
    } else
    {
         QTextStream in(&file);
#ifdef Q_OS_MAC
         in.setCodec(QTextCodec::codecForName(ENCODING));
#endif
         int rowCnt = 0, colCnt = 0;

         QString firstLine = in.readLine();
         emit firstRowColChanged( getFirst(firstLine));

         QStringList hHStrList = cutAndSplit(firstLine);
         colCnt = hHStrList.size();
         emit colCountChanged(colCnt);
         csvModel->setColumnCount(colCnt);

        for (int i = 0; i < colCnt; i++)
        {
            QStandardItem *hHeaderItem = new QStandardItem(hHStrList.at(i));
            hHeaderItem->setData(hHStrList.at(i) );
            hHeaderItem->setTextAlignment(Qt::AlignCenter);
            hHeaderItem->setEditable(false);
            hHeaderItem->setFont(QFont(hHeaderItem->font().family(), 13, QFont::Bold));
            hHeaderItem->setSizeHint(QSize(100, 30));
            hHeaderItem->setBackground(QBrush(QColor(Qt::gray)));
            csvModel->setHorizontalHeaderItem(i, hHeaderItem);
        }

         while (!in.atEnd())
         {
             QString line = in.readLine() ;
             emit rowCountChanged(rowCnt++);

             QString vHStr = getFirst(line);
             QStandardItem* vHItem = new QStandardItem(vHStr);
             vHItem->setData(vHStr, Qt::EditRole);
             vHItem->setData(cutOnset(vHStr), Qt::DisplayRole);
             vHItem->setTextAlignment(Qt::AlignRight);
             vHItem->setTextAlignment(Qt::AlignVCenter);
             vHItem->setFont(QFont(vHItem->font().family(), 13, QFont::Bold));
             vHItem->setEditable(false);

             QStringList itemsStrList = cutAndSplit(line);
             QList<QStandardItem *> standardItemsList;

             for (QString itemStr : itemsStrList)
             {
                 QStandardItem *item = new QStandardItem(itemStr);
                 item->setData(itemStr.toDouble(), Qt::EditRole);
                 item->setData(itemStr, Qt::DisplayRole);
                 item->setTextAlignment(Qt::AlignCenter);
                 standardItemsList.append(item);

             }
             csvModel->insertRow(csvModel->rowCount(), standardItemsList);
             csvModel->setVerticalHeaderItem(csvModel->rowCount() - 1, vHItem);
             //csvModel->verticalHeaderItem(csvModel->rowCount())->setFont(headerVFont);
             //csvModel->verticalHeaderItem(csvModel->rowCount()-1)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
             //csvModel->setHeaderData(csvModel->rowCount() - 1, Qt::Vertical, headerVFont, Qt::FontRole);
             //csvModel->setHeaderData(csvModel->rowCount() - 1, Qt::Vertical, Qt::AlignRight, Qt::TextAlignmentRole);
             //csvModel->setHeaderData(csvModel->rowCount() - 1, Qt::Vertical, newVerticalLabel);
             //csvModel->horizontalHeaderItem(csvModel->rowCount() - 1)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

         }
         file.close();
         return csvModel;
    }
}

QString FileManager::requiredPath(QDir currentDir, const QString &redirect)
{

#ifdef Q_OS_MAC
    currentDir.cdUp();
    currentDir.cdUp();
    currentDir.cdUp();
#endif

    currentDir.cdUp();
    currentDir.cd(redirect);
    QString path = (currentDir.exists()) ?  currentDir.absolutePath() : QString(QStandardPaths::PicturesLocation);

    if(currentDir.exists())
    {
        return path;
    } else
    {
       qDebug() << "Directory " << currentDir.absolutePath() << " + " <<  redirect << "doesn't exist";
       return "";
    }
}

QString FileManager::cutOnset(QString longString)
{
    QStringList partsList = longString.split("\\");
    return partsList.last();
}

QStringList FileManager::cutAndSplit(QString str)
{
    QStringList listWithFirst = str.split(";");
    listWithFirst.removeFirst();
    return listWithFirst;
}

QString FileManager::getFirst(QString str)
{
    return str.split(";").first();
}
