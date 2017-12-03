#include "MapEditorData.h"

MapEditorData::MapEditorData(MapEditorControl* mapEditorControl, QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    configureUI(mapEditorControl);
    this->setWindowFlags(Qt::Sheet | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::CustomizeWindowHint);
}

MapEditorData::~MapEditorData()
{
}

void MapEditorData::configureUI(MapEditorControl* mapEditorControl)
{
  m_tableWidget = std::unique_ptr<SGOOnMapTableWidget>(new SGOOnMapTableWidget(mapEditorControl));
  this->tabWidget->clear();
  this->tabWidget->addTab(m_tableWidget.get(), "static game objects");
}