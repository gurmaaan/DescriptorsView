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

    setupTableView();
    initChart();
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
        QStandardItem *hHeaderItem = new QStandardItem(StringService::multipleLine(descrNameStr));
        ItemsService::addDescription(hHeaderItem, descrNameStr);
        ItemsService::makeHHeader(hHeaderItem);
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

void DescriptorsWidget::loadModelFromCSVFile(QString filePath)
{
    emit fileNameChanged(filePath);
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

    QTime t1 = QTime::currentTime();
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
    QTime t2 = QTime::currentTime();
    emit sendStatusMessage(StringService::getTimeMessage(t1, t2));

    QTime t3 = QTime::currentTime();
    model_ = convertintoStandardModel(objInFileVector);
    QTime t4 = QTime::currentTime();
    emit sendStatusMessage(StringService::getTimeMessage(t3, t4));
    ui->tableView->setModel(model_);
}

void DescriptorsWidget::initChart()
{
    chart_ = new QChart();
    chart_->setAnimationOptions(QChart::AllAnimations);
    chartView_ = new QChartView(chart_);

    ui->splitter->addWidget(chartView_);
    ui->splitter->setSizes( QList<int>({INT_MAX, INT_MAX}) );

}

void DescriptorsWidget::setupTableView()
{
    QHeaderView *hH = ui->tableView->horizontalHeader();
    hH->resetDefaultSectionSize();
    hH->setTextElideMode(Qt::ElideNone);
    hH->resizeSections(QHeaderView::ResizeToContents);
    hH->setSectionResizeMode(QHeaderView::Interactive);
    hH->setSortIndicatorShown(false);

    QHeaderView *vH = ui->tableView->verticalHeader();
    vH->setAlternatingRowColors(true);
    vH->setSectionResizeMode(QHeaderView::Stretch);


}

void DescriptorsWidget::on_tableView_clicked(const QModelIndex &index)
{
    int cN = index.column();
    QAbstractItemModel *baseModel = ui->tableView->model();

    QStandardItemModel *newModel = new QStandardItemModel();
    newModel->setColumnCount(baseModel->rowCount());

    QList<QStandardItem *> itemsAtSelectedC;
    for(int i = 0; i < baseModel->rowCount(); i++)
    {
        itemsAtSelectedC << new QStandardItem(baseModel->data(baseModel->index(i, cN)).toString());
        QStandardItem *hHAtI = new QStandardItem(baseModel->headerData(i, Qt::Vertical).toString());
        ItemsService::makeHeader(hHAtI, Qt::Horizontal);
        newModel->setHorizontalHeaderItem(i, hHAtI);
    }

    QStandardItem *newVertHeader = new QStandardItem( baseModel->headerData(cN, Qt::Horizontal).toString());
    ItemsService::makeHeader(newVertHeader, Qt::Vertical);
    newModel->insertRow(0, itemsAtSelectedC);
    newModel->setVerticalHeaderItem(0, newVertHeader);
    emit selectedModelChanged(newModel);
}
