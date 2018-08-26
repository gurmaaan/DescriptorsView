    int colNum = 0;
    bool errorExisting = false;
    // If eror doesn't exist: 
//     -------------------------
//     |     X     |     Y     |
//     -------------------------
// IF error exist:
//     -------------------------
//     |  X  | erX |  Y  | erY |
//     -------------------------
    switch (t) {
    case AxisType::AxisX:
        colNum = 0;
        break;
    case AxisType::AxisY:
        colNum = errorExisting ? 2 : 1;
        break;
    case AxisType::ErrorX:
        colNum = 1;
        break;
    case AxisType::ErrorY:
        colNum = 3;
        break;
    case AxisType::Default:
    colNum = 0;
        break;
    }

    connect(ui->viewer->getXWid(), &AxisSettingsWidget::colorChanged,
            ui->viewer, &DescriptorsWidget::setObjColClr);
    connect(ui->viewer->getYWid(), &AxisSettingsWidget::colorChanged,
            ui->viewer, &DescriptorsWidget::setObjColClr);
    connect(ui->viewer->getErXWid(), &AxisSettingsWidget::colorChanged,
            ui->viewer, &DescriptorsWidget::setObjColClr);
    connect(ui->viewer->getErYWid(), &AxisSettingsWidget::colorChanged,
            ui->viewer, &DescriptorsWidget::setObjColClr);