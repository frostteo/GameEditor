#pragma once

#include <QWidget>
#include "ui_MapEditor.h"
#include "QtDirectXWidget.h"

class MapEditor : public QtDirectXWidget, public Ui::MapEditor
{
    Q_OBJECT

public:
  MapEditor(QString pathToModels, QString pathToMaterials, QWidget *parent = Q_NULLPTR);
    ~MapEditor();
};
