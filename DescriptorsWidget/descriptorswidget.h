#ifndef DESCRIPTORSWIDGET_H
#define DESCRIPTORSWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QStandardItemModel>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>

#include "Services/stringservice.h"
#include "Services/fileservice.h"
#include "Services/itemsservice.h"

#include "checkboxheaderview.h"
#include "DescriptorsModel/descriptor.h"
#include "DescriptorsModel/obj.h"

namespace Ui {
    class DescriptorsWidget;
}

class DescriptorsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DescriptorsWidget(QWidget *parent = nullptr);
    ~DescriptorsWidget();

    QStandardItemModel *convertintoStandardModel(QVector<Obj*> objectsVector);

public slots:
    void loadModelFromCSVFile(QString filePath);
   // slot

signals:
    void fileNameChanged(QString newFileName);
    void cornerRowChanged(QString newCornerRow);
    void colCountinModelChanged(int newColCount);
    void colCountInFileChanged(int newColCount);
    void rowCountInModelChanged(int newRowCount);
    void rowCountInFileChanged(int newRowCount);
    void sendStatusMessage(QString messageText);
    void selectedModelChanged(QStandardItemModel *m);

private slots:
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::DescriptorsWidget *ui;
    StringService *ss_;
    FileService *fs_;
    ItemsService *is_;
    QStringList descrNameList_;
    QVector<Obj*> *dm_;
    QStandardItemModel *model_;
    QChart *chart_;
    QChartView *chartView_;
    QTableView *t_;

    void initChart();
    void setupTableView();
};

#endif // DESCRIPTORSWIDGET_H
