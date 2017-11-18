#include "SGOOnMapTableWidget.h"

SGOOnMapTableWidget::SGOOnMapTableWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    configureUI();
}

SGOOnMapTableWidget::~SGOOnMapTableWidget()
{
}

void SGOOnMapTableWidget::editBtnsStateConfigure()
{
  bool hasSelection = m_table->selectionModel()->hasSelection();
  m_toolBox->editBtn->setEnabled(hasSelection);
  m_toolBox->cloneBtn->setEnabled(hasSelection);
  m_toolBox->deleteBtn->setEnabled(hasSelection);
}

void SGOOnMapTableWidget::configureTable()
{
  m_table = std::unique_ptr<QTableView>(new QTableView);
  m_tableModel = std::unique_ptr<SGOOnMapTM>(new SGOOnMapTM(10));

  m_table->setModel(m_tableModel.get());

  m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_table->setSelectionMode(QAbstractItemView::SingleSelection);
  m_table->resizeColumnsToContents();
  m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  m_table->horizontalHeader()->setStretchLastSection(true);

  m_table->horizontalHeader()->setSortIndicatorShown(true);
  m_table->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);

  connect(m_toolBox->deleteBtn, SIGNAL(clicked()), this, SLOT(DeleteBtnClicked()));
  connect(m_toolBox->editBtn, SIGNAL(clicked()), this, SLOT(EditBtnClicked()));
  connect(m_toolBox->cloneBtn, SIGNAL(clicked()), this, SLOT(CloneBtnClicked()));

  connect(m_table->selectionModel(),
    SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
    SLOT(TableRowSelected(const QItemSelection &, const QItemSelection &)));

  connect(m_tableModel.get(), SIGNAL(TableDataChanged()), this, SLOT(editBtnsStateConfigure()));
  connect(m_table->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(HeaderSectionClicked(int)));
}

void SGOOnMapTableWidget::configureUI()
{
  m_paginator = std::unique_ptr<QtGEPaginator>(new QtGEPaginator);
  m_toolBox = std::unique_ptr<SGOOnMapToolBox>(new SGOOnMapToolBox);

  configureTable();
  configurePaginator();
  QVBoxLayout* vertToolBoxLayout = new QVBoxLayout;
  vertToolBoxLayout->addWidget(m_toolBox.get());
  vertToolBoxLayout->addSpacerItem(new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));

  QHBoxLayout* horizontalLayout = new QHBoxLayout;
  horizontalLayout->addLayout(vertToolBoxLayout);


  QVBoxLayout* verticalTableLayout = new QVBoxLayout;
  verticalTableLayout->addWidget(m_table.get());
  verticalTableLayout->addWidget(m_paginator.get());

  horizontalLayout->addLayout(verticalTableLayout);
  this->setLayout(horizontalLayout);

  connect(m_toolBox.get(), SIGNAL(FilterChanged()), this, SLOT(UpdateTable()));
}

void SGOOnMapTableWidget::configurePaginator()
{
  connect(m_tableModel.get(), SIGNAL(PagingInfoChanged(PagingInfo)), m_paginator.get(), SLOT(UpdatePagingInfo(PagingInfo)));
  m_paginator->UpdatePagingInfo(m_tableModel->GetPagingInfo());

  connect(m_paginator.get(), SIGNAL(PageChanged(int, int)), this, SLOT(PaginatorPageChanged(int, int)));
}

void SGOOnMapTableWidget::TableRowSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
  int selectedRow = m_table->selectionModel()->currentIndex().row();
  SGOOnMapDbInfo gameObject = m_tableModel->GetEntity(selectedRow);
  m_mapEditor->SetSelectedObjectObjectId(gameObject.id);
  editBtnsStateConfigure();
}

void SGOOnMapTableWidget::PaginatorPageChanged(int pageNumber, int onPage)
{
  UpdateTable();
}

void SGOOnMapTableWidget::HeaderSectionClicked(int sectionIndex)
{
  UpdateTable();
}

void SGOOnMapTableWidget::UpdateTable()
{
  m_tableModel->UpdateTable(m_paginator->GetPageNumber(),
    m_paginator->GetOnPageCount(),
    m_table->horizontalHeader()->sortIndicatorSection(),
    m_table->horizontalHeader()->sortIndicatorOrder(),
    m_toolBox->GetSGONameFilter(),
    m_toolBox->GetInstanceNameFilter());
}

void SGOOnMapTableWidget::AddSGOToMap(StaticGameObjectDbInfo& sgo)
{
  AddOrEditSGOOnMapDialog dialog(this);
  SGOOnMapDbInfo sgoOnMap;
  sgoOnMap.staticGameObjectDbInfo = sgo;
  sgoOnMap.staticGameObjectId = sgo.id;
  sgoOnMap.instanceName = sgo.name;
  if (sgo.countOnMap > 0)
    sgoOnMap.instanceName += QString::number(sgo.countOnMap);

  //TODO FHolod: установить позицию и поворот в зависимости от координат камеры редакторы карты
  dialog.setSGOOnMap(sgoOnMap);

  if (dialog.exec() == QDialog::Accepted) {
    sgoOnMap = dialog.GetSGOOnMap();
    m_tableModel->append(sgoOnMap);
    m_mapEditor->AddSGO(sgoOnMap);
  }
}

void SGOOnMapTableWidget::Delete(int id)
{
  m_mapEditor->DeleteSGO(id);
  m_tableModel->remove(id);
}

void SGOOnMapTableWidget::DeleteBtnClicked()
{
  int selectedRow = m_table->selectionModel()->currentIndex().row();
  SGOOnMapDbInfo gameObject = m_tableModel->GetEntity(selectedRow);
  Delete(gameObject.id);
}

void SGOOnMapTableWidget::EditBtnClicked()
{
  int selectedRow = m_table->selectionModel()->currentIndex().row();
  SGOOnMapDbInfo gameObject = m_tableModel->GetEntity(selectedRow);

  AddOrEditSGOOnMapDialog dialog(this);
  dialog.setSGOOnMap(gameObject);

  if (dialog.exec() == QDialog::Accepted) {
    SGOOnMapDbInfo editedGameObject = dialog.GetSGOOnMap();
    m_tableModel->edit(editedGameObject);
    m_mapEditor->EditSGO(editedGameObject);
  }
}

void SGOOnMapTableWidget::Clone(int id)
{
  SGOOnMapDbInfo gameObject = m_tableModel->GetEntityByKey(id);
  gameObject.id = 0;

  if (gameObject.staticGameObjectDbInfo.countOnMap > 0)
    gameObject.instanceName = gameObject.staticGameObjectDbInfo.name + QString::number(gameObject.staticGameObjectDbInfo.countOnMap);

  AddOrEditSGOOnMapDialog dialog;
  dialog.setSGOOnMap(gameObject);

  if (dialog.exec() == QDialog::Accepted) {
    SGOOnMapDbInfo clonedGameObject = dialog.GetSGOOnMap();
    m_tableModel->append(clonedGameObject);
    m_mapEditor->AddSGO(clonedGameObject);
  }
}

void SGOOnMapTableWidget::CloneBtnClicked()
{
  int selectedRow = m_table->selectionModel()->currentIndex().row();
  Clone(m_tableModel->GetEntity(selectedRow).id);
}

void SGOOnMapTableWidget::SetMapEditor(MapEditor* mapEditor)
{
  m_mapEditor = mapEditor; 
  auto allGameObjectsOnMap = m_tableModel->GetSGOOnMapService()->GetAll();
  for (auto& gameObject : allGameObjectsOnMap)
  {
    m_mapEditor->AddSGO(gameObject);
  }
}