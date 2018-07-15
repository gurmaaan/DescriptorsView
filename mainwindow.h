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

    void on_selectionTableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    FileManager fm;
    void connectAll();
    void chartInit();
    void makeAllItemsTextColor(QAbstractItemModel *model, int colorCode);
    void setFontBold(QStandardItem *item);
    void makeItemTextColor(QStandardItem *item, int colorCode);
    void makeItemTextColor(QAbstractItemModel *model, int r, int c, int colorCode);

};

#endif // MAINWINDOW_H
