#ifndef DESCRIPTORSWIDGET_H
#define DESCRIPTORSWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QStandardItemModel>
#include <QStringList>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QXYModelMapper>
#include <QMessageBox>

#include "Services/stringservice.h"
#include "Services/fileservice.h"
#include "Services/itemsservice.h"
#include "DescriptorsModel/descriptor.h"
#include "DescriptorsModel/obj.h"
#include "static.h"
#include "DescriptorsWidget/axissettingswidget.h"
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

    QStringList getObjNamesList() const;
    inline QStringList getObjNameList() const { return objNameList_; }
    inline int getDescColCnt() const { return  model_->columnCount(); }
    QAbstractItemModel *getModel() const;
    QAbstractItemModel *createPointsModel(bool fourColms = false);
    AxisSettingsWidget *getAxisWidget(AxisType t) const;
    QList<AxisType> getAxTypes() const;
    QList<AxisSettingsWidget *> getAxWidgets() const;

public slots:
    void loadModelFromCSVFile(QString filePath);
    void setPointsModel(QStandardItemModel *points);
    void scrollToCol(int colNum);
    void setObjColClr(int colNum, QRgb colorCode);
    void updatePointsTable(AxisType t, bool state);

    int  getColNum(AxisType t);
    int  getPointsColNum(AxisType t);

    QList<QStandardItem *> getColItemsList(int col);
    QList<QStandardItem *> getColItemsList(AxisType t);

signals:
    void fileNameChanged(QString newFileName);
    void cornerRowChanged(QString newCornerRow);
    void colCountinModelChanged(int newColCount);
    void colCountInFileChanged(int newColCount);
    void rowCountInFileChanged(int newRowCount);
    void objectProccessed(int curObjNum);
    void sendStatusMessage(QString messageText);
    void selectedModelChanged(QStandardItemModel *m);

private:
    Ui::DescriptorsWidget *ui;
    StringService *ss_;
    FileService *fs_;
    ItemsService *is_;

    QList<AxisSettingsWidget *> axWidgets_;
    QList<AxisType> axTypes_;

    QStringList descrNameList_;
    QStringList objNameList_;
    QVector<Obj*> *dm_;

    QStandardItemModel *model_;
    QStandardItemModel *pointsModel_;
    //DscrTableModel *model_;

    QChart *chart_;
    QChartView *chartView_;

    void initChart();
    void initAxisWidgets();
    void initTable();
};

#endif // DESCRIPTORSWIDGET_H
