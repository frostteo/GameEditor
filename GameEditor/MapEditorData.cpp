#include "MapEditorData.h"

MapEditorData::MapEditorData(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    configureUI();
    this->setWindowFlags(Qt::Sheet | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::CustomizeWindowHint);
}

MapEditorData::~MapEditorData()
{
}

void MapEditorData::configureUI()
{
  m_tableWidget = std::unique_ptr<SGOOnMapTableWidget>(new SGOOnMapTableWidget);
  this->tabWidget->clear();
  this->tabWidget->addTab(m_tableWidget.get(), "static game objects");
}