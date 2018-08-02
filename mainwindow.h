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

    void on_originalTextButton_clicked();
    void on_originalTextAction_triggered();
    void messageResiver(QString message);

private slots:
    void on_actionQuit_triggered();

    void on_closeFileAction_triggered();

private:
    Ui::MainWindow *ui;
    FileService *fs_;
    ItemsService *is_;
    void connectAll();
    void changeWindowProperties();
};

#endif // MAINWINDOW_H
