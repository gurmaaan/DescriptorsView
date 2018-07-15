#include "descriptorswidget.h"
#include "ui_descriptorswidget.h"

DescriptorsWidget::DescriptorsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DescriptorsWidget)
{
    ui->setupUi(this);
}

DescriptorsWidget::~DescriptorsWidget()
{
    delete ui;
}
