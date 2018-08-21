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
    int getAxisColumnID(AxisType t);

    QVector<QString> getObjNameVector() const;
    inline QStringList getObjNameList() const { return objNameList_; }

    int getDescColCnt() const;
    QAbstractItemModel *getModel() const;
    QStandardItemModel *getAndPushToViewModel(int colX, int colY) const;

    inline AxisSettingsWidget *getXWid() const { return aswX_; }
    inline AxisSettingsWidget *getYWid() const { return aswY_; }
    inline AxisSettingsWidget *getErXWid() const { return asEX_; }
    inline AxisSettingsWidget *getErYWid() const { return asEY_; }

public slots:
    void loadModelFromCSVFile(QString filePath);
    void setPointsModel(QStandardItemModel *points);
    void scrollToCol(int colNum);
    void setColumnColor(int colNum, QColor colColor);

signals:
    void fileNameChanged(QString newFileName);
    void cornerRowChanged(QString newCornerRow);
    void colCountinModelChanged(int newColCount);
    void colCountInFileChanged(int newColCount);
    void rowCountInModelChanged(int newRowCount);
    void rowCountInFileChanged(int newRowCount);
    void sendStatusMessage(QString messageText);
    void selectedModelChanged(QStandardItemModel *m);

private:
    Ui::DescriptorsWidget *ui;
    StringService *ss_;
    FileService *fs_;
    ItemsService *is_;

    QStringList descrNameList_;
    QStringList objNameList_;

    QVector<Obj*> *dm_;
    QStandardItemModel *model_;
    QStandardItemModel *pointsModel_;
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
