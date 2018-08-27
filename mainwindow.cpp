#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    v_= ui->viewer;
    fs_ = new FileService();
    axWidgets_ = v_->getAxWidgets();
    connectAll();
    changeWindowProperties();
    ui->openFileAction->trigger();
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
    connect(v_, &DescriptorsWidget::fileNameChanged,
            ui->pathLineEdit, &QLineEdit::setText);
    connect(v_, &DescriptorsWidget::fileNameChanged,
            this, &MainWindow::setWindowFilePath);
    connect(v_, &DescriptorsWidget::cornerRowChanged,
            ui->plainTextEdit, &QPlainTextEdit::appendPlainText);

    connect(v_, &DescriptorsWidget::colCountInFileChanged,
            ui->fileColSpin, &QSpinBox::setValue);
    connect(v_, &DescriptorsWidget::colCountinModelChanged,
            ui->modelColSpin, &QSpinBox::setValue);

    connect(v_, &DescriptorsWidget::objectProccessed,
            ui->modelRowSpin, &QSpinBox::setValue);
    connect(v_, &DescriptorsWidget::objectProccessed,
            this, &MainWindow::setupProgressBar);
    connect(v_, &DescriptorsWidget::rowCountInFileChanged,
            ui->fileRowSpin, &QSpinBox::setValue);
    connect(v_, &DescriptorsWidget::objectProccessed,
            ui->fileProgressBar, &QProgressBar::setValue);

    connect(v_, &DescriptorsWidget::sendStatusMessage,
            this, &MainWindow::messageResiver);

    for(auto a : axWidgets_)
    {
        connect( a, &AxisSettingsWidget::selectedIndexChanged,
                 v_, &DescriptorsWidget::scrollToCol);
        connect( a, &AxisSettingsWidget::colorChanged,
                 v_, &DescriptorsWidget::setObjColClr);
        connect( a, &AxisSettingsWidget::checkedChanged,
                 v_, &DescriptorsWidget::updatePointsTable);
    }
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
    //QString path = fs_->initDialogAndGetOpenedFileName(QString(OPEN_FD_TITTLE), FileType::CSV);
    v_->loadModelFromCSVFile("C:/Users/dmvgu/YandexDisk/EDUCATION/_VIDEO/DescriptorsView/data/C.csv");
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

void MainWindow::setupProgressBar(int objCnt)
{
    ui->fileProgressBar->setMaximum(objCnt * 2);
}

void MainWindow::on_actionQuit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_pathLineEdit_textChanged(const QString &arg1)
{
    QString fileExtenssion = arg1.split(".").last();
    if(fileExtenssion == "csv") {
        ui->typeCB->addItem(CSVTYPE);
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

}

void MainWindow::on_pointsAct_triggered()
{
    v_->createPointsModel(false);
}

void MainWindow::on_addFileAct_triggered()
{
    //TODO: механизм сравнения 2 файлов
}

void MainWindow::on_closeFileAction_triggered()
{
    //TODO: механизм закрытия ыфайлов и сброса интерфейса
}
