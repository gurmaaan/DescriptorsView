#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fs_ = new FileService();
    is_ = new ItemsService();
    connectAll();
    changeWindowProperties();
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

    connect(ui->viewer, &DescriptorsWidget::colCountInFileChanged,
            ui->fileColSpin, &QSpinBox::setValue);
    connect(ui->viewer, &DescriptorsWidget::colCountinModelChanged,
            ui->modelColSpin, &QSpinBox::setValue);

    connect(ui->viewer, &DescriptorsWidget::rowCountInModelChanged,
            ui->modelRowSpin, &QSpinBox::setValue);
    connect(ui->viewer, &DescriptorsWidget::rowCountInFileChanged,
            ui->fileRowSpin, &QSpinBox::setValue);

    connect(ui->viewer, &DescriptorsWidget::sendStatusMessage,
            this, &MainWindow::messageResiver);
}

void MainWindow::changeWindowProperties()
{
    if (QGuiApplication::screens().count() > 1)
    {
        QRect secndScrnGeom = QGuiApplication::screens().at(1)->geometry();
        setGeometry(secndScrnGeom);
        showFullScreen();
    } else
        showMaximized();
}

void MainWindow::on_openFileAction_triggered()
{
    QString path = fs_->initDialogAndGetOpenedFileName(QString(OPEN_FD_TITTLE), FileType::CSV);
    ui->viewer->loadModelFromCSVFile(path);
}

void MainWindow::on_originalTextButton_clicked()
{
    ui->originalTextAction->trigger();
}

void MainWindow::on_originalTextAction_triggered()
{
    QFileInfo fi(ui->pathLineEdit->text());
    if( fi.exists() && fi.isFile() )
        ui->textBrowser->setText(FileService::getTextOfFile( ui->pathLineEdit->text() ) );
}

void MainWindow::messageResiver(QString message)
{
    qDebug() << message;
    ui->statusBar->showMessage(message, MSG_TIME);
}
