#ifndef CHECKBOXHEADERVIEW_H
#define CHECKBOXHEADERVIEW_H

#include <QObject>
#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>
#include "static.h"

class CheckBoxHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    CheckBoxHeaderView(Qt::Orientation, QWidget* parent = nullptr);

    bool isChecked() const { return isChecked_; }
    void setIsChecked(bool val);

signals:
    void checkBoxClicked(bool state);

protected:
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const;

    void mousePressEvent(QMouseEvent* event);
private:
    bool isChecked_;

    void redrawCheckBox();
};

#endif // CHECKBOXHEADERVIEW_H
