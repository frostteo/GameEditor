#include "MapEditorData.h"

MapEditorData::MapEditorData(std::shared_ptr<MapEditorControl> mapEditorControl, QWidget *parent)
    : QWidget(parent),
    m_tableWidget(new SGOOnMapTableWidget(mapEditorControl))
{
    setupUi(this);
    this->tabWidget->clear();
    this->tabWidget->addTab(m_tableWidget.get(), "game objects");
    this->setWindowFlags(Qt::Sheet | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::CustomizeWindowHint);
}

MapEditorData::~MapEditorData()
{
}
