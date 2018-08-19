#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileInfo>

#include "static.h"
#include "Services/fileservice.h"
#include "Services/itemsservice.h"
#include "DescriptorsWidget/axissettingswidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_openFileButton_clicked();
    void on_openFileAction_triggered();
    void messageResiver(QString message);
    void scrollSelect(int colInd);

private slots:
    void on_pointsBtn_clicked();
    void on_buildBtn_clicked();
    void on_addFileBtn_clicked();

    void on_actionQuit_triggered();
    void on_closeFileAction_triggered();
    void on_originalTextAction_triggered();
    void on_githubAct_triggered();
    void on_chartBuildAct_triggered();
    void on_pointsAct_triggered();
    void on_addFileAct_triggered();  

    void on_pathLineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    FileService *fs_;
    void connectAll();
    void changeWindowProperties();
};

#endif // MAINWINDOW_H
