#include "SGOOnMapTableWidget.h"

SGOOnMapTableWidget::SGOOnMapTableWidget(MapEditorControl* mapEditorControl, QWidget *parent)
    : QWidget(parent)
{
  m_mapEditorControl = mapEditorControl;
  setupUi(this);
  configureUI();
}

SGOOnMapTableWidget::~SGOOnMapTableWidget()
{
}

void SGOOnMapTableWidget::editBtnsStateConfigure()
{
  int selectedRowSize = m_table->selectionModel()->selectedRows().size();
  bool hasSelection = m_table->selectionModel()->hasSelection();
 
  m_toolBox->cloneBtn->setEnabled(hasSelection);
  m_toolBox->deleteBtn->setEnabled(hasSelection);

  m_toolBox->editBtn->setEnabled(selectedRowSize == 1);

  QModelIndex test;
  bool freezeBtnEnabled = m_tableModel->rowCount(test) > 0;
  m_toolBox->freezeAllBtn->setEnabled(freezeBtnEnabled);
  m_toolBox->unfreezeAllBtn->setEnabled(freezeBtnEnabled);
}

void SGOOnMapTableWidget::configureTable()
{
  m_table = std::unique_ptr<QTableView>(new QTableView);
  m_tableModel = m_mapEditorControl->GetMapEditorViewModel()->GetSGOOnMapTM();

  m_table->setModel(m_tableModel);

  m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_table->setSelectionMode(QAbstractItemView::MultiSelection);
  m_table->resizeColumnsToContents();
  m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  m_table->horizontalHeader()->setStretchLastSection(true);

  m_table->horizontalHeader()->setSortIndicatorShown(true);
  m_table->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);

  connect(m_toolBox->deleteBtn, SIGNAL(clicked()), this, SLOT(DeleteBtnClicked()));
  connect(m_toolBox->editBtn, SIGNAL(clicked()), this, SLOT(EditBtnClicked()));
  connect(m_toolBox->cloneBtn, SIGNAL(clicked()), this, SLOT(CloneBtnClicked()));
  connect(m_toolBox->freezeAllBtn, SIGNAL(clicked()), this, SLOT(FreezeAllBtnClicked()));
  connect(m_toolBox->unfreezeAllBtn, SIGNAL(clicked()), this, SLOT(UnfreezeAllBtnClicked()));

  connect(m_table->selectionModel(),
    SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
    SLOT(TableRowSelected(const QItemSelection &, const QItemSelection &)));

  connect(m_tableModel, SIGNAL(TableDataChanged()), this, SLOT(editBtnsStateConfigure()));
  connect(m_table->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(HeaderSectionClicked(int)));
  connect(m_tableModel, SIGNAL(ClearSelectionSignal()), this, SLOT(ClearSelection()));

  editBtnsStateConfigure();
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
  connect(m_tableModel, SIGNAL(PagingInfoChanged(PagingInfo)), m_paginator.get(), SLOT(UpdatePagingInfo(PagingInfo)));
  m_paginator->UpdatePagingInfo(m_tableModel->GetPagingInfo());

  connect(m_paginator.get(), SIGNAL(PageChanged(int, int)), this, SLOT(PaginatorPageChanged(int, int)));
}

std::vector<int> SGOOnMapTableWidget::GetSelectedIds()
{
  std::vector<int> selectedObjectsIds;
  selectedObjectsIds.reserve(m_table->selectionModel()->selectedRows().size());
  for (auto& index : m_table->selectionModel()->selectedRows())
  {
    selectedObjectsIds.push_back(index.data().toInt());
  }
  return selectedObjectsIds;
}

void SGOOnMapTableWidget::TableRowSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
  std::vector<int> selectedObjectsIds = GetSelectedIds();
  m_tableModel->SetSelectedSGOIds(selectedObjectsIds);
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

void SGOOnMapTableWidget::DeleteBtnClicked()
{
  std::vector<int> selectedIds = GetSelectedIds();
  m_mapEditorControl->Delete(selectedIds);
}

void SGOOnMapTableWidget::EditBtnClicked()
{
  int selectedRow = m_table->selectionModel()->currentIndex().row();
  SGOOnMapDbInfo gameObject = m_tableModel->GetEntity(selectedRow);
  m_mapEditorControl->EditSgoOnMap(gameObject.id);
}

void SGOOnMapTableWidget::CloneBtnClicked()
{
  auto selectedIds = GetSelectedIds();
  m_mapEditorControl->Clone(selectedIds);
}

void SGOOnMapTableWidget::FreezeAllBtnClicked()
{
  m_mapEditorControl->FreezeAll();
}

void SGOOnMapTableWidget::UnfreezeAllBtnClicked()
{
  m_mapEditorControl->UnfreezeAll();
}

