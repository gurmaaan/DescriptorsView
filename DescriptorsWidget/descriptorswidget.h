#ifndef DESCRIPTORSWIDGET_H
#define DESCRIPTORSWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QStandardItemModel>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QXYModelMapper>

#include "Services/stringservice.h"
#include "Services/fileservice.h"
#include "Services/itemsservice.h"

#include "DescriptorsModel/descriptor.h"
#include "DescriptorsModel/obj.h"

#include "axissettingswidget.h"
//#include "DescriptorsModel/dscrtablemodel.h"

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
    QVector<Obj*> convertFileIntoObjectsVector(QString filePath);

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

    void on_pointsBtn_clicked();

    void on_buildBtn_clicked();

    void on_maximizeGraphBtn_clicked();

private:
    Ui::DescriptorsWidget *ui;
    StringService *ss_;
    FileService *fs_;
    ItemsService *is_;

    QStringList descrNameList_;

    QVector<Obj*> *dm_;
    QStandardItemModel *model_;
    //DscrTableModel *model_;
    QChart *chart_;
    QChartView *chartView_;

    AxisSettingsWidget *aswX_;
    AxisSettingsWidget *aswY_;
    AxisSettingsWidget *asEX_;
    AxisSettingsWidget *asEY_;

    void initChart();
    void initAisWidgets();
    void initTable();
};

#endif // DESCRIPTORSWIDGET_H
