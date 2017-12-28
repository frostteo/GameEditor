#include "SGOTableWidget.h"

SGOTableWidget::SGOTableWidget(MapEditorPreferences* mapEditorPreferences, QString& pathToModels, QString& pathToMaterials, QWidget *parent)
    : QWidget(parent)
{
  m_mapEditorPreferences = mapEditorPreferences;
  SetPathToModels(pathToModels);
  SetPathToMaterials(pathToMaterials);
  ui.setupUi(this);
  configureUI();
}

SGOTableWidget::~SGOTableWidget()
{
}

void SGOTableWidget::configureTable()
{
  m_previewStaticGOWidget = std::unique_ptr<PreviewStaticGOWidget>(new PreviewStaticGOWidget(m_mapEditorPreferences, m_pathToModels, m_pathToMaterials, this));

  m_SGOTable = std::unique_ptr<QTableView>(new QTableView);
  m_SGOTableModel = std::unique_ptr<StaticGameObjectTM>(new StaticGameObjectTM(10));

  m_SGOTable->setModel(m_SGOTableModel.get());

  m_SGOTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_SGOTable->setSelectionMode(QAbstractItemView::SingleSelection);
  m_SGOTable->resizeColumnsToContents();
  m_SGOTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  m_SGOTable->horizontalHeader()->setStretchLastSection(true);

  m_SGOTable->horizontalHeader()->setSortIndicatorShown(true);
  m_SGOTable->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);

  connect(m_SGOToolBox->ui.addSGOBtn, SIGNAL(clicked()), this, SLOT(on_addSGOBtn_clicked()));
  connect(m_SGOToolBox->ui.editSGOBtn, SIGNAL(clicked()), this, SLOT(on_editSGOBtn_clicked()));
  connect(m_SGOToolBox->ui.deleteSGOBtn, SIGNAL(clicked()), this, SLOT(on_deleteSGOBtn_clicked()));
  connect(m_SGOToolBox->ui.previewSGOBtn, SIGNAL(clicked()), this, SLOT(on_previewSGOBtn_clicked()));
  connect(m_SGOToolBox->ui.addToMapBtn, SIGNAL(clicked()), this, SLOT(on_addToMapBtn_clicked()));

  connect(m_SGOTable->selectionModel(),
    SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
    SLOT(SGOtableRowSelected(const QItemSelection &, const QItemSelection &)));

  connect(m_SGOTableModel.get(), SIGNAL(TableDataChanged()), this, SLOT(editBtnsStateConfigure()));
  connect(m_SGOTable->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(HeaderSectionClicked(int)));
}

void SGOTableWidget::configurePaginator()
{
  connect(m_SGOTableModel.get(), SIGNAL(PagingInfoChanged(PagingInfo)), m_SGOPaginator.get(), SLOT(UpdatePagingInfo(PagingInfo)));
  m_SGOPaginator->UpdatePagingInfo(m_SGOTableModel->GetPagingInfo());

  connect(m_SGOPaginator.get(), SIGNAL(PageChanged(int, int)), this, SLOT(PaginatorPageChanged(int, int)));
}



void SGOTableWidget::configureUI()
{
  m_SGOPaginator = std::unique_ptr<QtGEPaginator>(new QtGEPaginator);
  m_SGOToolBox = std::unique_ptr<SGOWidgetToolBox>(new SGOWidgetToolBox);

  configureTable();
  configurePaginator();
  QVBoxLayout* vertToolBoxLayout = new QVBoxLayout;
  vertToolBoxLayout->addWidget(m_SGOToolBox.get());
  vertToolBoxLayout->addSpacerItem(new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding));

  QHBoxLayout* horizontalLayout = new QHBoxLayout;
  horizontalLayout->addLayout(vertToolBoxLayout);


  QVBoxLayout* verticalTableLayout = new QVBoxLayout;
  verticalTableLayout->addWidget(m_SGOTable.get());
  verticalTableLayout->addWidget(m_SGOPaginator.get());

  horizontalLayout->addLayout(verticalTableLayout);
  this->setLayout(horizontalLayout);

  connect(m_SGOToolBox.get(), SIGNAL(FilterChanged()), this, SLOT(UpdateTable()));
}

void SGOTableWidget::on_previewSGOBtn_clicked()
{
  int selectedRow = m_SGOTable->selectionModel()->currentIndex().row();
  StaticGameObjectDbInfo gameObject = m_SGOTableModel->GetEntity(selectedRow);

  m_previewStaticGOWidget->SetStaticGameObject(gameObject);
  m_previewStaticGOWidget->show();
}

void SGOTableWidget::on_addSGOBtn_clicked()
{
  AddStaticGameObjectDialog dialog(this);
  dialog.SetPathToModels(m_pathToModels);
  dialog.SetPathToMaterials(m_pathToMaterials);
  if (dialog.exec() == QDialog::Accepted) {
    m_SGOTableModel->append(dialog.GetStaticGameObject());
  }
}

void SGOTableWidget::on_editSGOBtn_clicked()
{
  int selectedRow = m_SGOTable->selectionModel()->currentIndex().row();
  StaticGameObjectDbInfo gameObject = m_SGOTableModel->GetEntity(selectedRow);

  AddStaticGameObjectDialog dialog(this);
  dialog.SetPathToModels(m_pathToModels);
  dialog.SetPathToMaterials(m_pathToMaterials);
  dialog.SetStaticGameObject(gameObject);

  if (dialog.exec() == QDialog::Accepted) {
    auto gameObject = dialog.GetStaticGameObject();
    m_SGOTableModel->edit(dialog.GetStaticGameObject());
    emit SGOEdited(gameObject);
  }
}

void SGOTableWidget::on_deleteSGOBtn_clicked()
{
  int selectedRow = m_SGOTable->selectionModel()->currentIndex().row();
  int id = m_SGOTableModel->index(selectedRow, 0).data().toInt();
  emit BeforeDeleteSgo(id);
  m_SGOTableModel->remove(id);
  emit SGODeleted(id);
}

void SGOTableWidget::editBtnsStateConfigure()
{
  bool hasSelection = m_SGOTable->selectionModel()->hasSelection();
  m_SGOToolBox->ui.editSGOBtn->setEnabled(hasSelection);
  m_SGOToolBox->ui.deleteSGOBtn->setEnabled(hasSelection);
  m_SGOToolBox->ui.previewSGOBtn->setEnabled(hasSelection);
  m_SGOToolBox->ui.addToMapBtn->setEnabled(hasSelection);
}

void SGOTableWidget::SGOtableRowSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
  editBtnsStateConfigure();
}

void SGOTableWidget::PaginatorPageChanged(int pageNumber, int onPage)
{
  UpdateTable();
}

void SGOTableWidget::HeaderSectionClicked(int sectionIndex)
{
  UpdateTable();
}

void SGOTableWidget::UpdateTable()
{
  m_SGOTableModel->UpdateTable(m_SGOPaginator->GetPageNumber(),
    m_SGOPaginator->GetOnPageCount(),
    m_SGOTable->horizontalHeader()->sortIndicatorSection(),
    m_SGOTable->horizontalHeader()->sortIndicatorOrder(),
    m_SGOToolBox->GetSGONameFilter(),
    m_SGOToolBox->GetSGOModelFilter());
}

void SGOTableWidget::on_addToMapBtn_clicked()
{
  int selectedRow = m_SGOTable->selectionModel()->currentIndex().row();
  StaticGameObjectDbInfo gameObject = m_SGOTableModel->GetEntity(selectedRow);
  emit AddToMap(gameObject);
}

void SGOTableWidget::on_SGODeletedFromMap(int id)
{
  StaticGameObjectDbInfo gameObject = m_SGOTableModel->GetEntityByKey(id);
  gameObject.countOnMap -= 1;
  m_SGOTableModel->edit(gameObject);
}

void SGOTableWidget::CountOnMapChanged(int id)
{
  if (m_SGOTableModel->ContainsInMemory(id))
    UpdateTable();
}