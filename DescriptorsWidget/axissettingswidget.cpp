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
    selectedIndex_ = -1;
    colorCode_ = QColor(Qt::white).rgb();
    //colorCode_ = StringService::getCSSClrProp(ui->clrBtn->styleSheet(), CSSBGCLR);
}

AxisSettingsWidget::AxisSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AxisSettingsWidget)
{
    ui->setupUi(this);
    setType(AxisType::Default);
    ui->clrBtn->setEnabled(true);
    model_ = new QStandardItemModel;
    max_ = 0;
    min_ = 0;
}

AxisSettingsWidget::~AxisSettingsWidget()
{
    delete ui;
}



void AxisSettingsWidget::on_clrBtn_clicked()
{
    QColor axisColor = QColorDialog::getColor(QColor(colorCode_), this);
    setColor(axisColor.rgb());
}



void AxisSettingsWidget::setColor(const QRgb &colorCode)
{
    if( colorCode_ != colorCode )
    {
        colorCode_ = colorCode;
        qDebug() << ui->clrBtn->styleSheet();
        //KOSTYL : конкретный стиль кнопки, т. к.
        //функция автоматической генерации строки стиля из стрингсервиса не работает
//        QString newStyleSheetStr = "border: 1px solid black; background-color: "
//                                 + QColor(colorCode).name()
//                                 + ";";
        ui->clrBtn->setStyleSheet(StringService::changeCSSClrProp( ui->clrBtn->styleSheet(), colorCode, CSSBGCLR));
        emit colorChanged(selectedIndex_, colorCode);
        qDebug() << StringService::changeCSSClrProp( ui->clrBtn->styleSheet(), colorCode, CSSBGCLR);
    }
}


int AxisSettingsWidget::selectedIndex() const
{
    if(this->checked())
        return selectedIndex_;
    else
        return -1;
}

QString AxisSettingsWidget::axisTittle(AxisType t)
{
    QString title = "";
    switch (t) {
    case AxisType::AxisX:
        title = "Axis X";
        break;
    case AxisType::AxisY:
        title = "Axis Y";
        break;
    case AxisType::ErrorX:
        title = "Axis error X";
        break;
    case AxisType::ErrorY:
        title = "Axis error Y";
        break;
    case AxisType::Default:
        title = "Axis";
        break;
    }
    return title;
}

void AxisSettingsWidget::on_valCB_currentIndexChanged(int index)
{
    setSelectedIndex(index);
}

void AxisSettingsWidget::setSelectedIndex(int si)
{
    if (checked())
    {
        min_ = 0;
        max_ = 0;
        avr_ = 0;
        ui->rangeCurrentSB->setValue(si + 1);
        selectedIndex_ = si;

        valuesOfCurentInd_.clear();
        for(int r = 0; r < model_->rowCount(); r++)
            valuesOfCurentInd_ << model_->data(model_->index(r, si)).toDouble();

        setCnt( valuesOfCurentInd_.count() );
        setMax( FloatService::max(valuesOfCurentInd_) );
        setMin( FloatService::min(valuesOfCurentInd_) );
        setAvr( FloatService::avr(valuesOfCurentInd_) );
        emit colorChanged(selectedIndex_, getColor());
    } else
        selectedIndex_ = -1;
    emit selectedIndexChanged(si);

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

void AxisSettingsWidget::setType(const AxisType &t)
{
    switch (t) {
    case AxisType::AxisX:
        setTittle("Axis X", false);
        setChecked(t, true);
        break;
    case AxisType::AxisY:
        setTittle("Axis Y", false);
        setChecked(t, true);
        break;
    case AxisType::ErrorX:
        setTittle("X error", true);
        setChecked(t, false);
        break;
    case AxisType::ErrorY:
        setTittle("Y error", true);
        setChecked(t, false);
        break;
    case AxisType::Default:
        setTittle("Axis", false);
        setChecked(t, true);
        break;
    }
    type_ = t;
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

void AxisSettingsWidget::setChecked(AxisType t, bool chSt)
{
    qDebug() << chSt;
    if( ui->groupBox->isCheckable() )
    {
        if(checked_ != chSt)
        {
            checked_ = chSt;
            ui->groupBox->setChecked(chSt);
            ui->colHLayout->setEnabled(chSt);
            ui->paramsHLayout->setEnabled(chSt);
            ui->clrHLayout->setEnabled(chSt);
            emit checkedChanged(t, chSt);
        }
    }
}


