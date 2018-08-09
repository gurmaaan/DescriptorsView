#include "descriptorswidget.h"
#include "ui_descriptorswidget.h"

DescriptorsWidget::DescriptorsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DescriptorsWidget)
{
    ui->setupUi(this);
    fs_ = new FileService();
    ss_ = new StringService();
    is_ = new ItemsService();

    model_ = new QStandardItemModel();
    initTable();
    initChart();
    initAisWidgets();
}

DescriptorsWidget::~DescriptorsWidget()
{
    delete ui;
}

QStandardItemModel *DescriptorsWidget::convertintoStandardModel(QVector<Obj *> objectsVector)
{
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount( descrNameList_.count() );

    int curC = 0;
    for (QString& descrNameStr : descrNameList_) {
        QStandardItem *hHeaderItem = new QStandardItem();
        hHeaderItem->setData(descrNameStr, Qt::EditRole);
        hHeaderItem->setData(StringService::multipleLine(descrNameStr), Qt::DisplayRole);
        ItemsService::addDescription(hHeaderItem, descrNameStr);
        ItemsService::makeHeader(hHeaderItem, Qt::Horizontal);
        model->setHorizontalHeaderItem(curC, hHeaderItem);
        curC++;
    }

    for (Obj *ob : objectsVector)
    {
        model->appendRow(ob->modelRow());
        model->setVerticalHeaderItem(model->rowCount() - 1, ob->rowVerticalHeader());
    }

    return model;
}

QVector<Obj *> DescriptorsWidget::convertFileIntoObjectsVector(QString filePath)
{
    QString wholeFileText = fs_->getTextOfFile(filePath);
    emit colCountInFileChanged( ss_->splitAndRemoveFirstColOfFirstRow(wholeFileText).count() + 1 );
    emit cornerRowChanged(StringService::getCornerString(wholeFileText));

    for(QString hHItemText : ss_->splitAndRemoveFirstColOfFirstRow(wholeFileText) )
    {
        if( StringService::notEmpty(hHItemText) )
            descrNameList_.append(hHItemText);
    }
    int descrCnt = descrNameList_.count();
    emit colCountinModelChanged(descrCnt);

    QStringList rowsList = ss_->splitAndRemoveFirstRow(wholeFileText);
    int rowsInFCnt = rowsList.count();
    emit rowCountInFileChanged(rowsInFCnt);

    QVector<Obj*> objInFileVector;
    for(int r = 0; r < rowsInFCnt; r++)
    {
        QString rowString = rowsList.at(r);
        if( StringService::notEmpty(rowString) )
        {
            emit rowCountInModelChanged(r);
            Obj* objAtRowR = new Obj( r, ss_->getFirstCol(rowString) );
            QStringList itemsOfRowStringList = ss_->splitAndRemoveFirstColOfFirstRow(rowString);
            for(int c = 0; c < descrCnt; c++)
            {
                QString itemString = itemsOfRowStringList.at(c);
                StringService::replaceForDouble(itemString);
                Descriptor *descriptorAtRC = new Descriptor(r, c, descrNameList_.at(c), itemString.toDouble());
                objAtRowR->apendDescriptor(descriptorAtRC);
            }
            objInFileVector << objAtRowR;
        }
    }
    return objInFileVector;
}

int DescriptorsWidget::getAxisColumnID(AxisType t)
{
    int result = 0;
    switch (t)
    {
        case AxisType::AxisX:
            result = ui->xWid->selectedIndex();
        break;
        case AxisType::AxisY:
            result = ui->yWid->selectedIndex();
        break;
        case AxisType::ErrorX:
            result = ui->xErrorWid->selectedIndex();
        break;
        case AxisType::ErrorY:
            result = ui->yErrorWid->selectedIndex();
        break;
        case AxisType::Default:
            result = -1;
        break;
    }

    return result;
}

void DescriptorsWidget::setPointsModel(QStandardItemModel *points)
{
    if(!(points->columnCount() == 0))
    {
        pointsModel_ = points;
        ui->tableViewPoints->setModel(points);
    }
}

void DescriptorsWidget::loadModelFromCSVFile(QString filePath)
{
    emit fileNameChanged(filePath);

    QTime t1 = QTime::currentTime();
    QVector<Obj*> objInFileVector = convertFileIntoObjectsVector(filePath);
    QTime t2 = QTime::currentTime();
    emit sendStatusMessage(StringService::getTimeMessage(t1, t2));

    QTime t3 = QTime::currentTime();
    model_ = convertintoStandardModel(objInFileVector);
    aswX_->setModel(model_);
    aswY_->setModel(model_);
    asEX_->setModel(model_);
    asEY_->setModel(model_);
    QTime t4 = QTime::currentTime();
    emit sendStatusMessage(StringService::getTimeMessage(t3, t4));

    QTime t5 = QTime::currentTime();
    ui->tableViewObjects->setModel(model_);

    QLineSeries *series = new QLineSeries;
    series->setName("Test col");
    QVXYModelMapper *mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setSeries(series);
    mapper->setModel(model_);
    chart_->addSeries(series);

    QTime t6 = QTime::currentTime();
    emit sendStatusMessage(StringService::getTimeMessage(t5, t6));
}

void DescriptorsWidget::scrollTo(Qt::Orientation o, int selectedInd)
{
    swi
}

QAbstractTableModel *DescriptorsWidget::getModel() const
{
 //   return ui->tableViewObjects->model();
}

QVector<QStandardItem *> DescriptorsWidget::getItemsByColumnID() const
{

}

int DescriptorsWidget::getDescColCnt() const
{
    return  model_->columnCount();
}

QVector<QString> DescriptorsWidget::getObjNameList() const
{
    QVector<QString> objNamesVector;
    for(int i = 0; i < model_->rowCount(); i++)
        objNamesVector << model_->headerData(i, Qt::Horizontal).toString();
    return objNamesVector;
}

void DescriptorsWidget::initChart()
{
    chart_ = new QChart();
    chart_->setAnimationOptions(QChart::AllAnimations);
    chartView_ = new QChartView(chart_);

    //ui->splitterTable->insertWidget(1,chartView_);
    //ui->splitterTable->setSizes( QList<int>({INT_MAX, INT_MAX}) );

   // ui->gr
    chart_->createDefaultAxes();
    chartView_->setRenderHint(QPainter::Antialiasing);
    chartView_->setChart(chart_);

    //FIXME : chartView почему то меньше по высоте и выровнен по центру относительно таблицы
}

void DescriptorsWidget::initAisWidgets()
{
    QGridLayout *grid = ui->gridLayout;
    aswX_ = ui->xWid;
    aswX_->setType(AxisType::AxisX);

    asEX_ = ui->xErrorWid;
    asEX_->setType(AxisType::ErrorX);

    aswY_ = ui->yWid;
    aswY_->setType(AxisType::AxisY);

    asEY_ = ui->yErrorWid;
    asEY_->setType(AxisType::ErrorY);

    grid->setColumnStretch(0, 0);
    grid->setColumnStretch(1, 1);

    ui->splitterHB->setSizes( QList<int>({INT_MAX, INT_MAX / 2}) );
}

void DescriptorsWidget::initTable()
{
    QHeaderView *hH = ui->tableViewObjects->horizontalHeader();
    hH->resetDefaultSectionSize();
    hH->setTextElideMode(Qt::ElideNone);
    hH->resizeSections(QHeaderView::ResizeToContents);
    hH->setSectionResizeMode(QHeaderView::Interactive);
    hH->setSortIndicatorShown(false);

    QHeaderView *vH = ui->tableViewObjects->verticalHeader();
    vH->setAlternatingRowColors(true);
    vH->setSectionResizeMode(QHeaderView::Stretch);
    vH->setSectionResizeMode(QHeaderView::Interactive);
}
