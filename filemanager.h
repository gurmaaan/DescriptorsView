#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QStandardItemModel>
#include <QObject>
#include <QTextCodec>

#include "static.h"

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);
    QString getOpenedFilePath();

    QStandardItemModel *getCsvModel(QString filePath);

signals:
    void rowCountChanged( int newRowCount);
    void colCountChanged( int newColCount);
    void firstRowColChanged( QString newFirstRowCol);

private:
    static QString requiredPath(QDir currentDir, const QString &redirect);
    QString cutOnset(QString longString);
    QStringList cutAndSplit(QString str);
    QString getFirst(QString str);
};

#endif // FILEMANAGER_H
