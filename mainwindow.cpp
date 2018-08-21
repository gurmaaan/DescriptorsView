#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fs_ = new FileService();
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

    connect(ui->viewer->getXWid(), &AxisSettingsWidget::selectedIndexChenged,
            ui->viewer, &DescriptorsWidget::scrollToCol);
    connect(ui->viewer->getYWid(), &AxisSettingsWidget::selectedIndexChenged,
            ui->viewer, &DescriptorsWidget::scrollToCol);
    connect(ui->viewer->getErXWid(), &AxisSettingsWidget::selectedIndexChenged,
            ui->viewer, &DescriptorsWidget::scrollToCol);
    connect(ui->viewer->getErYWid(), &AxisSettingsWidget::selectedIndexChenged,
            ui->viewer, &DescriptorsWidget::scrollToCol);
}

void MainWindow::changeWindowProperties()
{
    if (QGuiApplication::screens().count() > 1)
    {
        setGeometry(QGuiApplication::screens().at(1)->geometry());
        showMaximized();
    } else
    {
        setGeometry(QGuiApplication::screens().first()->geometry());
        showMaximized();
    }
}

void MainWindow::on_openFileAction_triggered()
{
    QString path = fs_->initDialogAndGetOpenedFileName(QString(OPEN_FD_TITTLE), FileType::CSV);
    ui->viewer->loadModelFromCSVFile(path);
}

void MainWindow::on_originalTextAction_triggered()
{
    QFileInfo fi(ui->pathLineEdit->text());
    if( fi.exists() && fi.isFile() )
        QDesktopServices::openUrl(ui->pathLineEdit->text());
       // ui->textBrowser->setText(FileService::getTextOfFile( ui->pathLineEdit->text() ) );
}

void MainWindow::messageResiver(QString message)
{
    qDebug().noquote() << message;
    ui->statusBar->showMessage(message, MSG_TIME);
}

void MainWindow::on_actionQuit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_pathLineEdit_textChanged(const QString &arg1)
{
    QString fileExtenssion = arg1.split(".").last();
    if(fileExtenssion == "csv") {
        ui->typeCB->addItem("Comma Separatred table *.CSV");
    }
}

void MainWindow::on_pointsBtn_clicked()
{
    ui->pointsAct->trigger();
}

void MainWindow::on_buildBtn_clicked()
{
   ui->chartBuildAct->trigger();
}

void MainWindow::on_addFileBtn_clicked()
{
    ui->addFileAct->trigger();
}

void MainWindow::on_githubAct_triggered()
{
    QDesktopServices::openUrl(QUrl(GURMAAAN));
}

void MainWindow::on_chartBuildAct_triggered()
{
     //TODO: триггер действия построения графика
}

void MainWindow::on_pointsAct_triggered()
{
    int cNx = ui->viewer->getAxisColumnID(AxisType::AxisX);
    int cNy = ui->viewer->getAxisColumnID(AxisType::AxisY);

    QStandardItemModel *pointsModel = new QStandardItemModel();
    pointsModel = ui->viewer->getAndPushToViewModel(cNx, cNy);
    ui->viewer->setPointsModel(pointsModel);
}

void MainWindow::on_addFileAct_triggered()
{
    //TODO: механизм сравнения 2 файлов
}

void MainWindow::on_closeFileAction_triggered()
{
    //TODO: механизм закрытия ыфайлов и сброса интерфейса
}
