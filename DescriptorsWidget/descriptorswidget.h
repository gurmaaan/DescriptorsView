#ifndef DESCRIPTORSWIDGET_H
#define DESCRIPTORSWIDGET_H

#include <QWidget>

namespace Ui {
class DescriptorsWidget;
}

class DescriptorsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DescriptorsWidget(QWidget *parent = 0);
    ~DescriptorsWidget();

private:
    Ui::DescriptorsWidget *ui;
};

#endif // DESCRIPTORSWIDGET_H
