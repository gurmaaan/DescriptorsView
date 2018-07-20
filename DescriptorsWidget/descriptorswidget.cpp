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

void DescriptorsWidget::loadModelFromCSVFile(QString filePath)
{
    emit fileNameChanged(filePath);
    QString wholeFileText = fs_->getTextOfFile(filePath);

    emit cornerRowChanged(StringService::getCornerString(wholeFileText));

    for(QString hHItemText : ss_->splitAndRemoveFirstColOfFirstRow(wholeFileText) )
    {
        if( StringService::notEmpty(hHItemText) )
            descrNameList_.append(hHItemText);
    }
    emit colCountChanged(descrNameList_.count());

    QStringList rowsList = ss_->splitAndRemoveFirstRow(wholeFileText);
    emit rowCountInFileChanged(rowsList.count());

    QVector<Obj*> *objInFileVector = new QVector<Obj*>;
    for(auto rowString : rowsList)
    {
        if( StringService::notEmpty(rowString) )
        {
            int r = rowsList.indexOf(rowString);
            emit rowCountInModelChanged(r);
            Obj* objAtRowR = new Obj(r, StringService::cutFilePath(ss_->getFirstCol(rowString)) );
            QStringList itemsOfRowStringList = ss_->splitAndRemoveFirstColOfFirstRow(rowString);
            foreach (QString itemString, itemsOfRowStringList)
            {
                int c = itemsOfRowStringList.indexOf(itemString);
                StringService::replaceForDouble(itemString);
                Descriptor *descriptorAtRC = new Descriptor(r, c, descrNameList_.at(c), itemString.toDouble());
                objAtRowR->apendDescriptor(descriptorAtRC);
            }
            objInFileVector->push_back(objAtRowR);
        }
    }

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
