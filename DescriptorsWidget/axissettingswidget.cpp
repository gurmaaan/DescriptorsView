#include "axissettingswidget.h"
#include "ui_axissettingswidget.h"

AxisSettingsWidget::AxisSettingsWidget(AxisType t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AxisSettingsWidget)
{
    ui->setupUi(this);
    setType(t);
    ui->clrBtn->setEnabled(true);
    model_ = new QStandardItemModel;
    max_ = 0;
    min_ = 0;
}

AxisSettingsWidget::~AxisSettingsWidget()
{
    delete ui;
}

void AxisSettingsWidget::on_valCB_currentIndexChanged(int index)
{
    setSelectedIndex(index);
}

void AxisSettingsWidget::setSelectedIndex(int si)
{
    min_ = 0;
    max_ = 0;
    avr_ = 0;
    ui->rangeCurrentSB->setValue(si + 1);

    valuesOfCurentInd_.clear();
    for(int r = 0; r < model_->rowCount(); r++)
        valuesOfCurentInd_ << model_->data(model_->index(r, si)).toDouble();

    setCnt( valuesOfCurentInd_.count() );
    setMax( FloatService::max(valuesOfCurentInd_) );
    setMin( FloatService::min(valuesOfCurentInd_) );
    setAvr( FloatService::avr(valuesOfCurentInd_) );

    emit selectedIndexChenged(si);
}

void AxisSettingsWidget::setCnt(int cnt)
{
    if (cnt_ != cnt)
    {
        cnt_ = cnt;
        ui->cntSB->setValue(cnt);
    }
}

void AxisSettingsWidget::setMin(double min)
{
    if ( !FloatService::equal(min_, min) )
    {
        min_ = min;
        ui->minLE->setText(QString::number(min));
    }
}

void AxisSettingsWidget::setMax(double max)
{
    if( !FloatService::equal(max_, max) )
    {
        max_ = max;
        ui->maxLE->setText(QString::number(max));
    }
}

void AxisSettingsWidget::setAvr(double avr)
{
    if( !FloatService::equal(avr_, avr) )
    {
        avr_ = avr;
        ui->avrLE->setText(QString::number(avr));
    }
}

void AxisSettingsWidget::on_clrBtn_clicked()
{
    QColor axisColor = QColorDialog::getColor(color_, this);
    setColor(axisColor);
}

void AxisSettingsWidget::setColor(const QColor &clr)
{
    if( color_ != clr )
    {
        color_ = clr;
        //KOSTYL : конкретный стиль кнопки, т. к.  функция автоматической генерации строки стиля из стрингсервиса не работает
        QString newStyleSheetStr = "border: 1px solid black; background-color: " + clr.name() + ";";
        ui->clrBtn->setStyleSheet(newStyleSheetStr);
        emit colorChenged(clr);
    }
}

void AxisSettingsWidget::setTittle(const QString &t, bool checkBoxExist)
{
    if(tittle_ != t)
    {
        tittle_ = t;
        ui->groupBox->setTitle(tittle_);
        ui->groupBox->setCheckable(checkBoxExist);
    }
}



void AxisSettingsWidget::setRangeMax(int colCnt)
{
    if ((rangeMax_ != colCnt) && (colCnt != 0) )
    {
        rangeMax_ = colCnt;
    }
}

void AxisSettingsWidget::setType(AxisType t)
{
    switch (t) {
    case AxisType::AxisX:
        setTittle("Axis X", false);
        setChecked(true);
        break;
    case AxisType::AxisY:
        setTittle("Axis Y", false);
        setChecked(true);
        break;
    case AxisType::ErrorX:
        setTittle("X error ", true);
        setChecked(false);
        break;
    case AxisType::ErrorY:
        setTittle("Y error", true);
        setChecked(false);
        break;
    }
}

void AxisSettingsWidget::setModel(QAbstractItemModel *model)
{
    if ( (model->rowCount() != 0) && (model->columnCount() != 0) )
    {
        model_ = model;
        ui->groupBox->setEnabled(true);

        if(ui->groupBox->isCheckable())
            ui->groupBox->setChecked(false);

        dscrNamesListForCB_.clear();
        ui->valCB->clear();
        ui->valCB->setMinimumWidth( ui->valCB->width() * 2);
        for(int i = 0; i < model_->columnCount(); i++)
            dscrNamesListForCB_ << model_->headerData(i, Qt::Horizontal, Qt::StatusTipRole).toString();

        ui->valCB->addItems(dscrNamesListForCB_);
        ui->rangeMaxSB->setMaximum( dscrNamesListForCB_.count()*2 );
        ui->rangeCurrentSB->setMaximum(dscrNamesListForCB_.count() * 2);
        ui->rangeMaxSB->setValue(dscrNamesListForCB_.count());
    }
}

void AxisSettingsWidget::setChecked(bool chSt)
{
    if( ui->groupBox->isCheckable() )
    {
        ui->groupBox->setChecked(chSt);
        ui->groupBox->setEnabled(!chSt);
    }
}
