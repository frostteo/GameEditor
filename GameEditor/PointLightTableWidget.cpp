#include "PointLightTableWidget.h"

PointLightTableWidget::PointLightTableWidget(MapEditorPreferences* mapEditorPreferences, QString& pathToModels, QString& pathToMaterials, QWidget *parent)
    : QWidget(parent)
{
  m_mapEditorPreferences = mapEditorPreferences;
  m_pathToModels = pathToModels;
  m_pathToMaterials = pathToMaterials;
  m_pointLightService = DependencyResolver::GetPointLightService();

  setupUi(this);
  configureUI();
}

PointLightTableWidget::~PointLightTableWidget()
{
}

void PointLightTableWidget::configureUI()
{
  m_paginator = std::unique_ptr<QtGEPaginator>(new QtGEPaginator);
  m_toolBox = std::unique_ptr<PointLightWidgetToolBox>(new PointLightWidgetToolBox);

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

  m_configurePLRelativePosWidget = std::unique_ptr<ConfigurePLRelativePosWidget>(new ConfigurePLRelativePosWidget(m_mapEditorPreferences, m_pathToModels, m_pathToMaterials, this));

  connect(m_configurePLRelativePosWidget.get(), SIGNAL(PointLightPositionChanged(int, float, float, float)), this, SLOT(PointLightPositionChanged(int, float, float, float)));
}

void PointLightTableWidget::PointLightPositionChanged(int id, float x, float y, float z)
{
  PointLightDbInfo pointLightDbInfo = m_tableModel->GetEntityByKey(id);
  pointLightDbInfo.relativePosX = x;
  pointLightDbInfo.relativePosY = y;
  pointLightDbInfo.relativePosZ = z;

  m_tableModel->edit(pointLightDbInfo);
  emit PointLightDbInfoEdited(pointLightDbInfo);
}

void PointLightTableWidget::configureTable()
{
  m_table = std::unique_ptr<QTableView>(new QTableView);
  m_tableModel = std::unique_ptr<PointLightTM>(new PointLightTM(10));

  m_table->setModel(m_tableModel.get());

  m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_table->setSelectionMode(QAbstractItemView::SingleSelection);
  m_table->resizeColumnsToContents();
  m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  m_table->horizontalHeader()->setStretchLastSection(true);

  m_table->horizontalHeader()->setSortIndicatorShown(true);
  m_table->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);

  connect(m_toolBox->addBtn, SIGNAL(clicked()), this, SLOT(on_addPointLightBtn_clicked()));
  connect(m_toolBox->editBtn, SIGNAL(clicked()), this, SLOT(on_editPointLightBtn_clicked()));
  connect(m_toolBox->deleteBtn, SIGNAL(clicked()), this, SLOT(on_deletePointLightBtn_clicked()));
  connect(m_toolBox->configureRelPosBtn, SIGNAL(clicked()), this, SLOT(on_configureRelPosBtn_clicked()));
  connect(m_toolBox->addToMapBtn, SIGNAL(clicked()), this, SLOT(on_addToMapBtn_clicked()));

  connect(m_table->selectionModel(),
    SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
    SLOT(RowSelected(const QItemSelection &, const QItemSelection &)));

  connect(m_tableModel.get(), SIGNAL(TableDataChanged()), this, SLOT(editBtnsStateConfigure()));
  connect(m_table->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(HeaderSectionClicked(int)));
}

void PointLightTableWidget::configurePaginator()
{
  connect(m_tableModel.get(), SIGNAL(PagingInfoChanged(PagingInfo)), m_paginator.get(), SLOT(UpdatePagingInfo(PagingInfo)));
  m_paginator->UpdatePagingInfo(m_tableModel->GetPagingInfo());

  connect(m_paginator.get(), SIGNAL(PageChanged(int, int)), this, SLOT(PaginatorPageChanged(int, int)));
}

void PointLightTableWidget::UpdateTable()
{
  m_tableModel->UpdateTable(m_paginator->GetPageNumber(),
    m_paginator->GetOnPageCount(),
    m_table->horizontalHeader()->sortIndicatorSection(),
    m_table->horizontalHeader()->sortIndicatorOrder(),
    m_toolBox->GetNameFilter(),
    m_toolBox->GetSgoNameFilter());
}

void PointLightTableWidget::HeaderSectionClicked(int sectionIndex)
{
  UpdateTable();
}

void PointLightTableWidget::PaginatorPageChanged(int pageNumber, int onPage)
{
  UpdateTable();
}

void PointLightTableWidget::RowSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
  editBtnsStateConfigure();
}

void PointLightTableWidget::editBtnsStateConfigure()
{
  bool hasSelection = m_table->selectionModel()->hasSelection();
  m_toolBox->editBtn->setEnabled(hasSelection);
  m_toolBox->deleteBtn->setEnabled(hasSelection);
  m_toolBox->addToMapBtn->setEnabled(hasSelection);

  if (hasSelection)
  {
    int selectedRow = m_table->selectionModel()->currentIndex().row();
    PointLightDbInfo pointLight = m_tableModel->GetEntity(selectedRow);
    m_toolBox->configureRelPosBtn->setEnabled(pointLight.staticGameObjectId);
  }
  else
  {
    m_toolBox->configureRelPosBtn->setEnabled(false);
  }
}

void PointLightTableWidget::on_configureRelPosBtn_clicked()
{
  int selectedRow = m_table->selectionModel()->currentIndex().row();
  PointLightDbInfo pointLight = m_tableModel->GetEntity(selectedRow);
  m_configurePLRelativePosWidget->SetPointLight(pointLight);
  m_configurePLRelativePosWidget->show();
}

void PointLightTableWidget::on_addPointLightBtn_clicked()
{
  AddOrEditPointLightDialog dialog(this);
  if (dialog.exec() == QDialog::Accepted) {
    m_tableModel->append(dialog.GetPointLight());
  }
}

void PointLightTableWidget::on_editPointLightBtn_clicked()
{
  int selectedRow = m_table->selectionModel()->currentIndex().row();
  PointLightDbInfo pointLight = m_tableModel->GetEntity(selectedRow);

  AddOrEditPointLightDialog dialog(this);
  dialog.SetPointLight(pointLight);

  if (dialog.exec() == QDialog::Accepted) {
    pointLight = dialog.GetPointLight();
    m_tableModel->edit(pointLight);
    m_configurePLRelativePosWidget->CheckPointLightPosChanged(pointLight);
    pointLight = m_tableModel->GetEntityByKey(pointLight.id);
    emit PointLightDbInfoEdited(pointLight);
  }
}

void PointLightTableWidget::on_deletePointLightBtn_clicked()
{
  int selectedRow = m_table->selectionModel()->currentIndex().row();
  int id = m_tableModel->index(selectedRow, 0).data().toInt();
  emit DeletePointLight(id);
  m_tableModel->remove(id);
}

void PointLightTableWidget::on_addToMapBtn_clicked()
{
  int selectedRow = m_table->selectionModel()->currentIndex().row();
  auto pointLight = m_tableModel->GetEntity(selectedRow);
  emit AddToMap(pointLight);
}

void PointLightTableWidget::SGOEditedSlot(StaticGameObjectDbInfo& gameObject)
{
   m_tableModel->UpdateData();
}

void PointLightTableWidget::SGODeletedSlot(int sgoId)
{
  m_tableModel->UpdateData();
}

void PointLightTableWidget::PointLightCountChanged(int id)
{
  if (m_tableModel->ContainsInMemory(id))
    m_tableModel->UpdateData();
}

void PointLightTableWidget::BeforeDeleteSgo(int id)
{
  auto pointLights = m_pointLightService->GetPointLightsBySgoId(id);
  for (auto& pointLight : pointLights)
  {
    pointLight.staticGameObjectId = 0;
    m_tableModel->edit(pointLight);
    emit PointLightDbInfoEdited(pointLight);
  }
}