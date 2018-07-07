#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
