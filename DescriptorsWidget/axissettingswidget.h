#ifndef AXISSETTINGSWIDGET_H
#define AXISSETTINGSWIDGET_H

#include <QWidget>
#include <QColorDialog>
#include "DescriptorsModel/obj.h"

namespace Ui {
class AxisSettingsWidget;
}

enum class AxisType
{
    AxisX,
    AxisY,
    ErrorX,
    ErrorY
};
class AxisSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AxisSettingsWidget(QWidget *parent = nullptr);
    ~AxisSettingsWidget();

    bool checkableState() const
    {
        return checkableState_;
    }
    void setCheckableState(bool cState);

    QString tittle() const
    {
        return tittle_;
    }
    void setTittle(const QString &tittle);

    void setObjectsVector(const QVector<Obj *> &objctsVctr);

    int selectedIndex() const
    {
        return selectedIndex_;
    }
    void setSelectedIndex(int selectedIndex);

    QColor color() const
    {
        return color_;
    }
    void setColor(const QColor &color);

    int cnt() const
    {
        return cnt_;
    }
    void setCnt(int cnt);

    double min() const
    {
        return min_;
    }
    void setMin(double min);

    double max() const
    {
        return max_;
    }
    void setMax(double max);

    double avr() const
    {
        return avr_;
    }
    void setAvr(double avr);

    bool checked() const
    {
        return checked_;
    }
    void setChecked(bool chSt);

    int rangeMax() const
    {
        return rangeMax_;
    }
    void setRangeMax(int rangeMax);
    void setType(AxisType t);

signals:
    void checkableStateChenged(bool state);
    void checkedChenged(bool state);
    void tittleChenged(QString newTittle);
    void vectorLoaded(QVector<Obj*> newVector);
    void colorChenged(QColor newColor);
    void rangeMaxChenged(int newMax);
    void selectedIndexCHenged(int newIndex);
    void cntChenged(int newCnt);
    void minChenged(double newMin);
    void maxChenged(double newMax);
    void avrChenged(double newAvr);

public slots:
    void setModel(QAbstractItemModel *model);

private slots:
    void on_valCB_currentIndexChanged(int index);
    void on_colorBtn_clicked();

private:
    Ui::AxisSettingsWidget *ui;
    bool checkableState_;
    bool checked_;
    QString tittle_;

    QVector<Obj *> objects_;
    QStringList descrNamesList_;
    int selectedIndex_;
    QVector<double> values_;

    int rangeMax_;

    QColor color_;
    int cnt_;
    double min_;
    double max_;
    double avr_;

    double calcMax(QVector<double> v);
    double calcMin(QVector<double> v);
    double calcAv(QVector<double> v);

    void applyConnection();
};

#endif // AXISSETTINGSWIDGET_H
