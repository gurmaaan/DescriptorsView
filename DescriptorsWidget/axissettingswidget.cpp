#include "axissettingswidget.h"
#include "ui_axissettingswidget.h"

AxisSettingsWidget::AxisSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AxisSettingsWidget)
{
    checkableState_ = false;
    checked_ = false;
   //////// ui->groupBox->setEnabled(false);
//    tittle_ = "";

    applyConnection();
    ui->setupUi(this);
}

AxisSettingsWidget::~AxisSettingsWidget()
{
    delete ui;
}

void AxisSettingsWidget::on_valCB_currentIndexChanged(int index)
{
    if(index != selectedIndex())
        setSelectedIndex(index);
}

void AxisSettingsWidget::setCnt(int cnt)
{
    if (cnt != cnt_)
    {
        cnt_ = cnt;
        emit cntChenged(cnt);
    }
}

void AxisSettingsWidget::setMin(double min)
{
    emit minChenged(min);
    min_ = min;
}

void AxisSettingsWidget::setMax(double max)
{
    emit maxChenged(max);
    max_ = max;
}

void AxisSettingsWidget::setAvr(double avr)
{
    avr_ = avr;
}

void AxisSettingsWidget::setColor(const QColor &clr)
{
    if( clr != color() )
    {
        color_ = clr;
        //QString prevStyleSheet = ui->colorBtn->styleSheet();
        QString styleString = "border: 1px solid black; background-color: " + clr.name() + ";";
        ui->colorBtn->setStyleSheet(styleString);
        qDebug() << styleString;
        emit colorChenged(clr);
    }
}

void AxisSettingsWidget::setSelectedIndex(int selectedIndex)
{
    if(selectedIndex != selectedIndex_)
    {
        selectedIndex_ = selectedIndex;
        for(auto desc : objects_.at(selectedIndex)->descriptors())
        {
            values_ << desc->data();
        }

        calcMin(values_);
        calcMax(values_);
        calcAv(values_);
        emit selectedIndexCHenged(selectedIndex);
    }
}

void AxisSettingsWidget::setObjectsVector(const QVector<Obj *> &objctsVctr)
{
    int objctsCnt = objctsVctr.count();

    ui->rangeMaxSB->setMaximum(objctsCnt);
    ui->rangeMaxSB->setValue(objctsCnt);

    if( objctsCnt !=0)
    {
        objects_ = objctsVctr;
        for ( auto dscr : objctsVctr[0]->descriptors() )
            descrNamesList_ << dscr->name();

        setRangeMax( descrNamesList_.count() );
        ui->valCB->addItems(descrNamesList_);

    }
}

void AxisSettingsWidget::setTittle(const QString &t)
{
    if(t != tittle())
    {
        tittle_ = t;
        emit tittleChenged(t);
    }
}

void AxisSettingsWidget::setCheckableState(bool cState)
{
    if (cState != checkableState())
    {
        checkableState_ = cState;
        ui->groupBox->setEnabled(true);
        emit checkableStateChenged(cState);
    }
}

void AxisSettingsWidget::on_colorBtn_clicked()
{
    QColor axisColor = QColorDialog::getColor(color_, parentWidget());
    if(axisColor != color_ )
        setColor(axisColor);
}

double AxisSettingsWidget::calcMax(QVector<double> v)
{
    max_ = 0;
    for(double item : v)
    {
        if (item > max_)
            max_ = item;
    }
    emit maxChenged(max_);
    return max_;
}

double AxisSettingsWidget::calcMin(QVector<double> v)
{
    min_ = 0;
    for(double item : v)
    {
        if (item < min_)
            min_ = item;
    }
    emit minChenged(min_);
    return min_;
}

double AxisSettingsWidget::calcAv(QVector<double> v)
{
    avr_ = (min_ + max_) / 2;
    emit avrChenged(avr_);
    return avr_;
}

void AxisSettingsWidget::setRangeMax(int rangeMax)
{
    if (rangeMax_ != rangeMax)
    {
        rangeMax_ = rangeMax;
        emit rangeMaxChenged(rangeMax);
    }
}

void AxisSettingsWidget::setType(AxisType t)
{
    switch (t) {
    case AxisType::AxisX:
        setTittle("Axis X");
        setCheckableState(false);
        setChecked(false);
        break;
    case AxisType::AxisY:
        setTittle("Axis Y");
        setCheckableState(false);
        setChecked(false);
        break;
    case AxisType::ErrorX:
        setTittle("X error ");
        setCheckableState(true);
        break;
    case AxisType::ErrorY:
        setTittle("Y error");
        setCheckableState(true);
        break;
    default:
        setTittle("");
        break;
    }
}

void AxisSettingsWidget::setModel(QAbstractItemModel *model)
{

}

void AxisSettingsWidget::setChecked(bool chSt)
{
    if(chSt != checked_)
    {
        checked_ = chSt;
        ui->groupBox->setEnabled(true);
        emit checkedChenged(chSt);
    }
}

void AxisSettingsWidget::applyConnection()
{
    connect(this, &AxisSettingsWidget::checkableStateChenged,
            ui->groupBox, &QGroupBox::setCheckable);
    connect(this, &AxisSettingsWidget::checkedChenged,
            ui->groupBox, &QGroupBox::setChecked);
    connect(this, &AxisSettingsWidget::tittleChenged,
            ui->groupBox, &QGroupBox::setTitle);

//    connect(this, &AxisSettingsWidget::cntChenged,
//            ui->cntSB, &QSpinBox::setMaximum);
//    connect(this, &AxisSettingsWidget::cntChenged,
//            ui->cntSB, &QSpinBox::setValue);
//    connect(this, &AxisSettingsWidget::maxChenged,
//            ui->maxLE, &QLineEdit::setText);
//    connect(this, &AxisSettingsWidget::maxChenged,
//            ui->maxLE, &QLineEdit::setValue);
//    connect(this, &AxisSettingsWidget::minChenged,
//            ui->minLE, &QLineEdit::setText);
//    connect(this, &AxisSettingsWidget::minChenged,
//            ui->minLE, &QLineEdit::setValue);
//    connect(this, &AxisSettingsWidget::avrChenged,
//            ui->avrLE, &QLineEdit::setText);
//    connect(this, &AxisSettingsWidget::avrChenged,
//            ui->avrLbl, &QLineEdit::setValue);

//    connect(this, &AxisSettingsWidget::rangeMaxChenged,
//            ui->rangeMaxSB, &QSpinBox::setMaximum);
//    connect(this, &AxisSettingsWidget::rangeMaxChenged,
//            ui->rangeMaxSB, &QSpinBox::setValue);
//    connect(this, &AxisSettingsWidget::rangeMaxChenged,
//            ui->rangeCurrentSB, &QSpinBox::setMaximum);
//    connect(this, &AxisSettingsWidget::selectedIndexCHenged,
//            ui->rangeCurrentSB, &QSpinBox::setValue);
}
