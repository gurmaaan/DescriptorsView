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
//    if(ui->selectionTableView->model()->columnCount() > 0)
//        ui->selectionTableView->model()->removeColumn(0);

    QStandardItemModel *selectionModel = new QStandardItemModel;
    QAbstractItemModel *tm = ui->tableView->model();

    QList<QStandardItem*> selectedItemsList;
    for(int i = 0; i < tm->columnCount(); i++)
    {
        QString selectedRowTextAtI = tm->index(index.row(), i).data().toString();
        selectedItemsList << new QStandardItem(selectedRowTextAtI);
    }
    selectionModel->insertColumn(0, selectedItemsList);

    QStandardItem *selectedVerticalHeaderItem = new QStandardItem;
    QString hHeaderSelectedRowText = tm->headerData(index.row(), Qt::Vertical).toString();
    selectedVerticalHeaderItem->setData(hHeaderSelectedRowText, Qt::DisplayRole);
    selectionModel->setHeaderData(0, Qt::Horizontal, hHeaderSelectedRowText);

    ui->selectionTableView->setModel(selectionModel);
}

void MainWindow::on_originalTextButton_clicked()
{
    int selectedRow = 0;
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
