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

//    tm_ = new QAbstractTableModel();
//    ui->table->setModel(tm_);

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

    foreach (QString descrNameStr, descrNameList_) {
        QStandardItem *hHeaderItem = new QStandardItem();
        hHeaderItem->setData(descrNameStr, Qt::DisplayRole);
        hHeaderItem->setCheckable(false);
        ItemsService::makeHHeader(hHeaderItem);
        model->setHorizontalHeaderItem(descrNameList_.indexOf(descrNameStr), hHeaderItem);
    }

//    model->setRowCount( objectsVector.count() );
    foreach (Obj *ob, objectsVector) {
        model->setVerticalHeaderItem(objectsVector.indexOf(ob), ob->rowHeader());
        model->appendColumn(ob->modelRow());
    }
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
    qDebug() << t1;
    QVector<Obj*> objInFileVector;
    for(int r = 0; r < rowsInFCnt; r++)
    {
        QString rowString = rowsList.at(r);
        if( StringService::notEmpty(rowString) )
        {
            emit rowCountInModelChanged(r);
            Obj* objAtRowR = new Obj(r, StringService::cutFilePath(ss_->getFirstCol(rowString)) );
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
    qDebug() << t2;
    qDebug() << tr("Converting from file into Object Class model finished at ") << (t2.second() - t1.second()) << tr(" second");
    //model_ = convertintoStandardModel(objInFileVector);
    //ui->table->setModel(model_);

}

void DescriptorsWidget::initChart()
{
    chart_ = new QChart();
    chart_->setAnimationOptions(QChart::AllAnimations);
    chartView_ = new QChartView(chart_);

    ui->splitter->addWidget(chartView_);
    ui->splitter->setSizes( QList<int>({INT_MAX, INT_MAX}) );

    //QLineSeries *ls = new QLineSeries();
    //ls->append()
}
