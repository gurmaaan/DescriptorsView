#ifndef AXISSETTINGSWIDGET_H
#define AXISSETTINGSWIDGET_H

#include <QWidget>
#include <QColorDialog>
#include <QAbstractItemModel>
#include <QGroupBox>
#include <QVector>

#include "DescriptorsModel/obj.h"
#include "Services/floatservice.h"

namespace Ui {
class AxisSettingsWidget;
}

enum class AxisType
{
    AxisX,
    AxisY,
    ErrorX,
    ErrorY,
    Default
};
class AxisSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AxisSettingsWidget(QWidget *parent = nullptr);
    AxisSettingsWidget(AxisType t, QWidget *parent = nullptr);
    ~AxisSettingsWidget();

    inline bool checked() const { return checked_; }
    inline QString tittle() const { return tittle_; }
    inline QColor color() const { return color_; }
    inline int rangeMax() const { return rangeMax_; }
    inline int cnt() const { return cnt_; }
    inline int selectedIndex() const { return selectedIndex_; }
    inline double min() const { return min_; }
    inline double max() const { return max_; }
    inline double avr() const { return avr_; }

    static QString axisTittle(AxisType t);
    void setObjectsVector(const QVector<Obj *> &objctsVctr);
    void setSelectedIndex(int selectedIndex);
    void setColor(const QColor &color);
    void setChecked(bool chSt);
    void setRangeMax(int colCnt);

    void setType(AxisType t);

signals:
    void checkedChenged(bool state);
    void tittleChenged(QString newTittle);
    void vectorLoaded(QVector<Obj*> newVector);
    void colorChenged(QColor newColor);
    void rangeMaxChenged(int newMax);
    void selectedIndexChenged(int newIndex);
    void sendStatusMessage(QString msg);
    void cntChenged(int newCnt);
    void minChenged(double newMin);
    void maxChenged(double newMax);
    void avrChenged(double newAvr);

public slots:
    void setModel(QAbstractItemModel *model);

private slots:
    void on_valCB_currentIndexChanged(int index);
    void on_clrBtn_clicked();

private:
    Ui::AxisSettingsWidget *ui;
    bool checked_;
    QString tittle_;
    QAbstractItemModel *model_;
    QStringList dscrNamesListForCB_;
    int selectedIndex_;
    QVector<double> valuesOfCurentInd_;
    int rangeMax_;

    QColor color_;
    int cnt_;
    double min_;
    double max_;
    double avr_;

    void setTittle(const QString &tittle, bool checkBoxExist);
    void setCnt(int cnt);
    void setMin(double min);
    void setMax(double max);
    void setAvr(double avr);
};

#endif // AXISSETTINGSWIDGET_H
