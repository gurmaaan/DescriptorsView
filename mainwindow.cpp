#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fs = new FileService();
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
    connect(ui->viewer, &DescriptorsWidget::fileNameChanged,
            ui->pathLineEdit, &QLineEdit::setText);
    connect(ui->viewer, &DescriptorsWidget::cornerRowChanged,
            ui->firstRowCOlLineEdit, &QLineEdit::setText);

    connect(ui->viewer, &DescriptorsWidget::colCountChanged,
            ui->modelColSpin, &QSpinBox::setValue);

    connect(ui->viewer, &DescriptorsWidget::rowCountInModelChanged,
            ui->modelRowSpin, &QSpinBox::setValue);
    connect(ui->viewer, &DescriptorsWidget::rowCountInFileChanged,
            ui->fileRowSpin, &QSpinBox::setValue);
}

void MainWindow::on_openFileAction_triggered()
{
    QString path = fs->initDialogAndGetOpenedFileName(QString(OPEN_FD_TITTLE), FileType::CSV);
    ui->viewer->loadModelFromCSVFile(path);
}

void MainWindow::on_originalTextButton_clicked()
{
    ui->originalTextAction->trigger();
}

void MainWindow::on_originalTextAction_triggered()
{
    qDebug() << "Test";
}
