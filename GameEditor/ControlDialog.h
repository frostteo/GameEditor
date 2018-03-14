#pragma once

#include <QWidget>
#include "ui_ControlDialog.h"

class ControlDialog : public QWidget, public Ui::ControlDialog
{
    Q_OBJECT

public:
    ControlDialog(QWidget *parent = Q_NULLPTR);
    ~ControlDialog();
};
