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

    for(auto hHItemText : ss_->splitAndRemoveFirstCol(wholeFileText) )
        descrNameList_.append(hHItemText);
    emit colCountChanged(descrNameList_.count());
    QStringList rowsList = ss_->splitAndRemoveFirstRow(wholeFileText);
    qDebug() << rowsList.count();
    emit rowCountChanged(rowsList.count());

    QVector<Obj*> *objInFileVector = new QVector<Obj*>;
    for(auto rowString : rowsList)
    {
        int r = rowsList.indexOf(rowString);
        Obj* objAtRowR = new Obj(r, ss_->getFirstCol(rowString));
        QStringList itemsOfRowStringList = ss_->splitAndRemoveFirstCol(rowString);
        foreach (auto itemString, itemsOfRowStringList)
        {
            int c = itemsOfRowStringList.indexOf(itemString);
            Descriptor *descriptorAtRC = new Descriptor(r, c,descrNameList_.at(c), itemString.toDouble());
            objAtRowR->apendDescriptor(descriptorAtRC);
        }
        objInFileVector->push_back(objAtRowR);
    }

}

void DescriptorsWidget::initChart()
{
    QChartView *chartView = new QChartView();
    QChart *chart = new QChart();
    QLineSeries *ls = new QLineSeries();
    chartView->setChart(chart);
    ui->splitter->insertWidget(1, chartView);
    ui->spl
}
