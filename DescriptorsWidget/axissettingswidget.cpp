#include "axissettingswidget.h"
#include "ui_axissettingswidget.h"

AxisSettingsWidget::AxisSettingsWidget(AxisType t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AxisSettingsWidget)
{
    ui->setupUi(this);
    setType(t);
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

void AxisSettingsWidget::setColor(const QColor &clr)
{
    if( color_ != clr )
    {
        color_ = clr;
        //WARNING : testing needed, but not important function
        QString newStyleSheetStr = StringService::replaceBGC(ui->colorBtn->styleSheet(), clr, "background-color");
        ui->colorBtn->setStyleSheet(newStyleSheetStr);
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

void AxisSettingsWidget::setSelectedIndex(int selectedIndex)
{
    min_ = 0;
    max_ = 0;
    avr_ = 0;
    if( selectedIndex_ != selectedIndex )
    {
        ui->rangeCurrentSB->setValue(selectedIndex);

        valuesOfCurentInd_.clear();
        for(int r = 0; r < model_->rowCount(); r++)
            valuesOfCurentInd_ << model_->data(model_->index(r, selectedIndex)).toDouble();

        setCnt( valuesOfCurentInd_.count() );
        setMax( FloatService::max(valuesOfCurentInd_) );
        setMin( FloatService::min(valuesOfCurentInd_) );
        setAvr( FloatService::avr(valuesOfCurentInd_) );
        emit selectedIndexCHenged(selectedIndex);
    }
}

void AxisSettingsWidget::on_colorBtn_clicked()
{
    QColor axisColor = QColorDialog::getColor(color_, parentWidget());
    if(axisColor != color_ )
        setColor(axisColor);
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
        break;
    case AxisType::AxisY:
        setTittle("Axis Y", false);
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
        //WARNING : хз проверить
        ui->groupBox->setEnabled( !ui->groupBox->isCheckable() );

        dscrNamesListForCB_.clear();
        ui->valCB->clear();

        for(int i = 0; i < model_->columnCount(); i++)
            dscrNamesListForCB_ << model_->headerData(i, Qt::Horizontal).toString();

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
        ui->groupBox->setEnabled(chSt);
    }
}
