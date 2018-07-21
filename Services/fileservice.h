#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <QObject>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QTextStream>
#include <QTextCodec>

#include "static.h"

enum class FileType
{
    Image,
    CSV,
    Excel
};

class FileService : public QObject
{
    Q_OBJECT
public:
    explicit FileService(QObject *parent = nullptr);
    QString initDialogAndGetOpenedFileName(QString title, FileType fType);
    static QString getTypeStringByCode(FileType fType);
    static QString getTextOfFile(QString path);
private:
    static QString requiredPath(QDir currentDir, const QString &redirect);
};

#endif // FILESERVICE_H
