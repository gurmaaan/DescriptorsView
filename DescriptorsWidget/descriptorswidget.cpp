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
    pointsModel_ = new QStandardItemModel();
    initAxisWidgets();
    initTable();
    initChart();
}

DescriptorsWidget::~DescriptorsWidget()
{
    delete ui;
}

QVector<Obj *> DescriptorsWidget::convertFileIntoObjectsVector(QString filePath)
{
    QString wholeFileText = fs_->getTextOfFile(filePath);
    emit colCountInFileChanged( ss_->splitAndRemoveFirstColOfFirstRow(wholeFileText).count() + 1 );
    emit cornerRowChanged( StringService::multipleLine(StringService::getCornerString(wholeFileText), ' ') );

    for(QString hHItemText : ss_->splitAndRemoveFirstColOfFirstRow(wholeFileText) )
    {
        if( StringService::notEmpty(hHItemText) )
            descrNameList_.append(hHItemText);
        else
        {
            int ret = QMessageBox::information(this, tr("Warning"),
                                                     tr(EMPTY_CELLS_MSG),
                                                     QMessageBox::Ok | QMessageBox::Cancel);
            if(ret == static_cast<int>(QMessageBox::Ok))
                break;
            else
            {
                qDebug() << ret;
                //TODO::Действие закрытия файла
            }
        }
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

            QString objectName = ss_->getFirstCol(rowString);
            objNameList_ << objectName;
            Obj* objAtRowR = new Obj( r,  objectName);
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
        emit objectProccessed(r);
    }
    return objInFileVector;
}

QStandardItemModel *DescriptorsWidget::convertintoStandardModel(QVector<Obj *> objectsVector)
{
    //FIXME:: блок работает очень долго
    QStandardItemModel *model = new QStandardItemModel();
   // model->setColumnCount( descrNameList_.count() );

    for (Obj *ob : objectsVector)
    {
        int rowCnt = model->rowCount();
        model->appendRow(ob->modelRow());
        model->setVerticalHeaderItem(rowCnt, ob->rowVerticalHeader());
        emit objectProccessed(rowCnt * 2);
    }

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


    return model;
}

int DescriptorsWidget::getColNum(AxisType t)
{
    int result = 0;
    for(auto a : axWidgets_)
    {
        if(a->getType() == t)
            result = a->selectedIndex();
    }
    return result;
}

int DescriptorsWidget::getPointsColNum(AxisType t)
{
    // If eror doesn't exist:
//     -------------------------
//     |     X     |     Y     |
//     -------------------------
// IF error exist:
//     -------------------------
//     |  X  | erX |  Y  | erY |
//     -------------------------
    bool checkedAt[4];
    for(int i = 0; i <4; i++)
        checkedAt[i] = getAxisWidget( getAxTypes().at(i) );
    int colNum = -1;

    switch (t)
    {
        case AxisType::AxisX:
            colNum = checkedAt[0] ? 0 : -1;
            break;
        case AxisType::AxisY:
        {
            if(checkedAt[1])
                colNum = ( checkedAt[2] || checkedAt[3] ) ? 2 : 1;
            else
                colNum = -1;
            break;
        }
        case AxisType::ErrorX:
            colNum = checkedAt[2] ? 1 : -1;
            break;
        case AxisType::ErrorY:
            colNum = checkedAt[0] ? 3 : -1;
            break;
        case AxisType::Default:
            colNum = -1;
            break;
    }

    return  colNum;
}

void DescriptorsWidget::setPointsModel(QStandardItemModel *points)
{
    if(!(points->columnCount() == 0))
    {
        pointsModel_ = points;
        ui->tableViewPoints->setModel(points);
    }
}

void DescriptorsWidget::setObjColClr(int colNum, QRgb colorCode)
{
    scrollToCol(colNum);

    ItemsService::makeAllItemBGColorDefault(model_);
    for(int r = 0; r < model_->rowCount(); r++)
    {
        QColor hItClr = QColor(colorCode).darker();
        qDebug() << "Original : " << colorCode << " Custom : " << hItClr;
        ItemsService::makeItemBGColor(model_->item(r, colNum), colorCode);
        ItemsService::makeItemBGColor( model_->horizontalHeaderItem(colNum), hItClr.rgb() );
    }
    pointsModel_->clear();
    ui->tableViewPoints->setModel(createPointsModel());
}

void DescriptorsWidget::setColBgClr(QList<QStandardItem *> colList, QRgb colorCode)
{
    for(int r = 0; r < colList.count(); r++)
        ItemsService::makeItemBGColor( colList.at(r), colorCode );
}

void DescriptorsWidget::updatePointsTable(AxisType t, bool state)
{
    int pMColCnt = pointsModel_->columnCount();
    QList<QStandardItem*> newCol = getColItemsList(t);
    for(int r = 0; r < newCol.count(); r++)
        ItemsService::makeItemBGColor( newCol.at(r), getAxisWidget(t)->getColor() );

    //int curCol = getColNum(t);
    int curPCol = getPointsColNum(t);
    switch (pMColCnt) {
    case 0:
    {
        if( curPCol != -1)
        {
            QStandardItemModel *model = new QStandardItemModel();
            model->appendColumn(newCol);
            setPointsModel(model);
        }
        break;
    }

    case 2:
    {
        if(t == AxisType::ErrorX || t == AxisType::ErrorY)
        {
            pointsModel_->appendColumn(newCol);
        }
        else
        {
            pointsModel_->clear();
            createPointsModel(false);
        }
        break;
    }
    case 4:
    {
        pointsModel_->clear();
        createPointsModel(true);
        break;
    }
    default:
        break;
    }
}

QList<QStandardItem *> DescriptorsWidget::getColItemsList(AxisType t)
{
    int colNum = getColNum(t);
    getColItemsList(colNum);
}

QList<AxisSettingsWidget *> DescriptorsWidget::getAxWidgets() const
{
    if(axWidgets_.count() != 0)
        return axWidgets_;
    else
    {
        QList<AxisSettingsWidget *> defW;
        defW << ui->xWid;
        return defW;
    }
}

QList<AxisType> DescriptorsWidget::getAxTypes() const
{
    if(axTypes_.count() != 0)
        return axTypes_;
    else
    {
        QList<AxisType> defT;
        defT << AxisType::Default;
        return defT;
    }
}

QList<QStandardItem *> DescriptorsWidget::getColItemsList(int col)
{
    QList<QStandardItem *> itemsList;
    for(int r = 0; r < model_->rowCount(); r++)
    {
        QStandardItem *old = model_->item(r, col);
        itemsList << ItemsService::fullCopy(old)    ;
    }
    return itemsList;
}

void DescriptorsWidget::loadModelFromCSVFile(QString filePath)
{
    emit fileNameChanged(filePath);

    QTime t1 = QTime::currentTime();
    QVector<Obj*> objInFileVector = convertFileIntoObjectsVector(filePath);
    QTime t2 = QTime::currentTime();
    emit sendStatusMessage(StringService::getTimeMessage(t1, t2, "convertFileIntoObjectsVector"));

    QTime t3 = QTime::currentTime();
    model_ = convertintoStandardModel(objInFileVector);

   // ui->xWid->setModel(model_);
   for(auto axis : axWidgets_)
        axis->setModel(model_);

    QTime t4 = QTime::currentTime();
    emit sendStatusMessage(StringService::getTimeMessage(t3, t4, "convertintoStandardModel"));

    ui->tableViewObjects->setModel(model_);
    QTime t5 = QTime::currentTime();
    emit sendStatusMessage(StringService::getTimeMessage(t4, t5, "setupModelToUI"));
}

void DescriptorsWidget::scrollToCol(int selectedInd)
{
    if(selectedInd != -1)
        ui->tableViewObjects->scrollTo(model_->index(0, selectedInd));
}

QStringList DescriptorsWidget::getObjNamesList() const
{
    QStringList objNamesList;
    for(int i = 0; i < model_->rowCount(); i++)
        objNamesList << model_->headerData(i, Qt::Horizontal).toString();
    return objNamesList;
}

QAbstractItemModel *DescriptorsWidget::getModel() const
{
    //NOTE::почему-то не переносится в хедер
    return ui->tableViewObjects->model();
}

AxisSettingsWidget *DescriptorsWidget::getAxisWidget(AxisType t) const
{
    AxisSettingsWidget *w;
    switch (t) {
    case AxisType::AxisX:
        w = ui->xWid;
        break;
    case AxisType::AxisY:
        w = ui->yWid;
        break;
    case AxisType::ErrorX:
        w = ui->xErWid;
        break;
    case AxisType::ErrorY:
        w = ui->yErWid;
        break;
    case AxisType::Default:
        w = nullptr;
        break;
    }
    return w;
}


QAbstractItemModel *DescriptorsWidget::createPointsModel(bool fourColms)
{
    QStandardItemModel *pointsModel = new QStandardItemModel();
     QList<QStandardItem*> colList;
    for(auto a : axWidgets_)
    {
        AxisType t = a->getType();
        if( !fourColms )
        {
            if(t == AxisType::AxisX || t == AxisType ::AxisY)
            {
                colList = getColItemsList(t);
                setColBgClr(colList, getAxisWidget(t)->getColor());
                pointsModel->appendColumn( colList );
            }
            else
                break;
        }
        else
        {
            colList = getColItemsList(t);
            setColBgClr(colList, getAxisWidget(t)->getColor());
            pointsModel->appendColumn( colList );
        }

    }
    setPointsModel(pointsModel);
    return(pointsModel);
}

void DescriptorsWidget::initChart()
{
    chart_ = new QChart();
    chart_->setAnimationOptions(QChart::AllAnimations);
    chartView_ = new QChartView(chart_);

    //ui->splitterTable->insertWidget(1,chartView_);
    //ui->splitterTable->setSizes( QList<int>({INT_MAX, INT_MAX}) );

    //TODO::вынести в метод initSeries
//    QLineSeries *series = new QLineSeries;
//    series->setName("Test col");
//    QVXYModelMapper *mapper = new QVXYModelMapper(this);
//    mapper->setXColumn(0);
//    mapper->setYColumn(1);
//    mapper->setSeries(series);
//    mapper->setModel(model_);
//    chart_->addSeries(series);
   // ui->gr
    chart_->createDefaultAxes();
    chartView_->setRenderHint(QPainter::Antialiasing);
    chartView_->setChart(chart_);

    //FIXME : chartView почему то меньше по высоте и выровнен по центру относительно таблицы
}

void DescriptorsWidget::initAxisWidgets()
{
    axTypes_ << AxisType::AxisX << AxisType::AxisY << AxisType::ErrorX << AxisType::ErrorY;

    for(auto type : axTypes_)
    {
        AxisSettingsWidget* axis = new AxisSettingsWidget(type);
        axis = getAxisWidget(type);
        axis->setType(type);
        axWidgets_ << axis;
    }

    QGridLayout *grid = ui->gridLayout;
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
