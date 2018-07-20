#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "static.h"
#include "Services/fileservice.h"

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

    void on_originalTextButton_clicked();
    void on_originalTextAction_triggered();

private:
    Ui::MainWindow *ui;
    FileService *fs;
    void connectAll();
};

#endif // MAINWINDOW_H
