#include "checkboxheaderview.h"

CheckBoxHeaderView::CheckBoxHeaderView(Qt::Orientation orientation, QWidget* parent /*= 0*/)
    : QHeaderView(orientation, parent)
{
    isChecked_ = true;
}

void CheckBoxHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    if(logicalIndex == 0)
    {
        QStyleOptionButton optionBtn;
        optionBtn.rect = QRect(CHECKBOX_RECT);
        optionBtn.state = QStyle::State_Enabled | QStyle::State_Active;

        optionBtn.state |= isChecked_ ? QStyle::State_On : QStyle::State_Off;
        //optionBtn.state |= QStyle::State_Off;

        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &optionBtn, painter);
    }
}

void CheckBoxHeaderView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        setIsChecked(!isChecked());
        emit checkBoxClicked(isChecked());
    }
}

void CheckBoxHeaderView::redrawCheckBox()
{
    viewport()->update();
}

void CheckBoxHeaderView::setIsChecked(bool val)
{
    if(isChecked_ != val)
    {
        isChecked_ = val;
        redrawCheckBox();
    }
}



