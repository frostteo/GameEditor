#pragma once

#include <memory>
#include <QWidget>
#include "ui_MapEditorData.h"
#include "SGOOnMapTableWidget.h"

class MapEditorData : public QWidget, public Ui::MapEditorData
{
    Q_OBJECT
private:
  std::unique_ptr<SGOOnMapTableWidget> m_tableWidget;
public:
  MapEditorData(std::shared_ptr<MapEditorControl> mapEditorControl, QWidget *parent = Q_NULLPTR);
    ~MapEditorData();
    SGOOnMapTableWidget* GetSGOOnMapTableWidget() { return m_tableWidget.get(); }
};
