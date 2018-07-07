#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelectionModel>
#include <QtCharts>
#include "filemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFileButton_clicked();

    void on_openFileAction_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_originalTextButton_clicked();

    void on_originalTextAction_triggered();

private:
    Ui::MainWindow *ui;
    FileManager fm;
    void connectAll();
    void chartInit();
};

#endif // MAINWINDOW_H
