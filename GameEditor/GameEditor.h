#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GameEditor.h"

class GameEditor : public QMainWindow
{
    Q_OBJECT

public:
    GameEditor(QWidget *parent = Q_NULLPTR);

private:
    Ui::GameEditorClass ui;
};
