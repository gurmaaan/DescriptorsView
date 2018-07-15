#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    chartInit();
    showMaximized();
    connectAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFileButton_clicked()
{
    ui->openFileAction->trigger();

}

void MainWindow::connectAll()
{
    connect(&fm, &FileManager::rowCountChanged,
            ui->modelRowSpin, &QSpinBox::setValue);
    connect(&fm, &FileManager::colCountChanged,
            ui->modelColSpin, &QSpinBox::setValue);

    connect(&fm, &FileManager::firstRowColChanged,
            ui->firstRowCOlLineEdit, &QLineEdit::setText);

}
void MainWindow::chartInit()
{
    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);
    QLineSeries *series = new QLineSeries;
    chart->addSeries(series);
    QChartView *chartView = new QChartView;
    chartView->setChart(chart);

    ui->splitter->insertWidget(1, chartView);
//    QXYModelMapper *mapper = new QXYModelMapper(this);
//    mapper->(0);
//    mapper->setYSection(1);
//    mapper->setSeries(series);
   // mapper->setModel(ui->tableView->selectionModel());

}

void MainWindow::makeAllItemsTextColor(QAbstractItemModel *model, int colorCode)
{
    for(int c = 0; c < model->columnCount(); c++)
        for(int r = 0; r < model->rowCount(); r++)
            model->setData(model->index(r, c), QColor(colorCode), Qt::TextColorRole);
}

void MainWindow::setFontBold(QStandardItem *item)
{
    item->setFont(QFont(item->font().family(), item->font().pointSize(), QFont::Bold));
}

void MainWindow::makeItemTextColor(QStandardItem *item, int colorCode)
{
    item->setData(QColor(colorCode), Qt::TextColorRole);
}

void MainWindow::makeItemTextColor(QAbstractItemModel *model, int r, int c, int colorCode)
{
    model->setData(model->index(r, c), QColor(colorCode), Qt::TextColorRole);
}

void MainWindow::on_openFileAction_triggered()
{
    QString path = fm.getOpenedFilePath();
    ui->pathLineEdit->setText(path);

    ui->tableView->setModel(fm.getCsvModel(path));
    ui->fileRowSpin->setValue( ui->modelRowSpin->value() + 1);
    ui->fileColSpin->setValue( ui->modelColSpin->value() + 1);
    ui->tableView->setTextElideMode(Qt::ElideMiddle);
    ui->tableView->horizontalHeader()->resizeSections(QHeaderView::Interactive);
    ui->tableView->verticalHeader()->resizeSections(QHeaderView::Interactive);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QStandardItemModel *selectionModel = new QStandardItemModel;
    QAbstractItemModel *tm = ui->tableView->model();
    //FixMe:: при первом клике сильно тупит
    //makeAllItemsTextColor(tm, Qt::black);
    makeItemTextColor(tm, index.row(), index.column(), Qt::red);
    QList<QStandardItem*> selectedItemsList;
    for(int i = 0; i < tm->columnCount(); i++)
    {
        QString selectedRowTextAtI = tm->index(index.row(), i).data().toString();
        QStandardItem *itemAtI = new QStandardItem(selectedRowTextAtI);
        if(i == index.column())
            itemAtI->setData(QColor(Qt::red), Qt::TextColorRole);
        selectedItemsList << itemAtI;
    }
    selectionModel->insertColumn(0, selectedItemsList);

    for(int i = 0; i < tm->columnCount(); i++)
    {
        QStandardItem *vHItemAtI = new QStandardItem;
        QString hHTextAtI = tm->headerData(i, Qt::Horizontal).toString();
        vHItemAtI->setData(hHTextAtI, Qt::DisplayRole);
        setFontBold(vHItemAtI);
        if(i == index.column())
            vHItemAtI->setData(QColor(Qt::red), Qt::TextColorRole);
        selectionModel->setVerticalHeaderItem(i, vHItemAtI);
    }

    QStandardItem *selectedvHItem = new QStandardItem;
    QString hHeaderSelectedRowText = tm->headerData(index.row(), Qt::Vertical).toString();
    selectedvHItem->setData(hHeaderSelectedRowText, Qt::DisplayRole);
    setFontBold(selectedvHItem);
    selectionModel->setHorizontalHeaderItem(0, selectedvHItem);

    ui->selectionTableView->setModel(selectionModel);
    QAbstractItemModel *sm = ui->selectionTableView->model();
    ui->selectionTableView->scrollTo( sm->index(index.column(), 0));
}

void MainWindow::on_originalTextButton_clicked()
{
    ui->originalTextAction->trigger();
}

void MainWindow::on_originalTextAction_triggered()
{
    if (! (ui->textView->document()->toPlainText().length() >= 1))
    {
        ui->textView->setText(fm.getTextOfFile(ui->pathLineEdit->text()));
        ui->tabWidget->setTabEnabled(1, true);
        ui->textTab->setEnabled(true);
        ui->textTab->setVisible(true);
        ui->tabWidget->setCurrentIndex(1);
    }
}

void MainWindow::on_selectionTableView_clicked(const QModelIndex &index)
{
    QAbstractItemModel *tm = ui->tableView->model();
    QAbstractItemModel *sm = ui->selectionTableView->model();

    for(int r = 0; r < sm->rowCount(); r++)
        sm->setHeaderData(r, Qt::Vertical, QColor(Qt::black), Qt::TextColorRole);

    if(sm->columnCount() >= 1)
    {
        makeAllItemsTextColor(sm, Qt::black);
        makeAllItemsTextColor(tm, Qt::black);
        QString sHHtext = sm->headerData(index.column(), Qt::Horizontal).toString();
        int rowN = 0;
        for(int r = 0; r < tm->rowCount(); r++)
        {
            if( tm->headerData(r, Qt::Vertical).toString() == sHHtext)
                rowN = r;
        }
        makeItemTextColor(tm, rowN, index.row(), Qt::red);
        ui->tableView->scrollTo(tm->index(rowN, index.row()));
    }
}
