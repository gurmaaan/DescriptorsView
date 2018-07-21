#include "fileservice.h"

FileService::FileService(QObject *parent) : QObject(parent)
{

}

QString FileService::initDialogAndGetOpenedFileName(QString title, FileType fType)
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    title,
                                                    requiredPath(QDir::current(), DATA_PATH),
                                                    getTypeStringByCode(fType));
    return fileName;

}

QString FileService::getTypeStringByCode(FileType fType)
{
    QString fileTypeStr = "*";
    switch (fType) {
    case FileType::Image:
        fileTypeStr = "Изображение PNG(*.png);;Изображение JPG(*.jpg);;Изображение BMP(*.bmp);;";
        break;
    case FileType::CSV:
        fileTypeStr = "Таблица CSV (*.csv)";
        break;
    case FileType::Excel:
        fileTypeStr = "Таблица Excel(*.xls*)";
        break;
    }
    return fileTypeStr;
}

QString FileService::requiredPath(QDir currentDir, const QString &redirect)
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
       qDebug() << tr("Directory ") << currentDir.absolutePath() << " + " <<  redirect << tr("doesn't exist");
       return "";
    }
}

QString FileService::getTextOfFile(QString path)
{
    QFile file(path);
    QString textOfFile;
    if ( !file.open(QFile::ReadOnly | QFile::Text ) )
    {
        qDebug() << tr(DOESNT_EXIST);
        textOfFile = "";
    } else
    {
         QTextStream in(&file);
         in.setCodec(QTextCodec::codecForName(ENCODING));
         textOfFile = in.readAll();
    }
    file.close();
    return textOfFile;
}
