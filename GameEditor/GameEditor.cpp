#include "GameEditor.h"

GameEditor::GameEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    BLLDependencyResolver::GetUnitOfWork()->Initialize(m_hostName, m_databaseName, m_connectionName);
    m_gameObjectTableModel = std::unique_ptr<StaticGameObjectTM>(new StaticGameObjectTM());

    m_SGOTableOrderFieldMap.insert(std::pair<int, std::string>(0, "id"));
    m_SGOTableOrderFieldMap.insert(std::pair<int, std::string>(1, "name"));
    m_SGOTableOrderFieldMap.insert(std::pair<int, std::string>(2, "modelFileName"));

    m_SGOTableOnPageCountMap.insert(std::pair<int, std::string>(0, "10"));
    m_SGOTableOnPageCountMap.insert(std::pair<int, std::string>(1, "25"));
    m_SGOTableOnPageCountMap.insert(std::pair<int, std::string>(2, "50"));

    this->createUI();

    m_previewStaticGOWidget = std::unique_ptr<PreviewStaticGOWidget>(new PreviewStaticGOWidget(m_pathToModels, m_pathToMaterials));
    m_previewStaticGOWidget->setWindowModality(Qt::WindowModality::ApplicationModal);
}

void GameEditor::createUI()
{
  ui.staticGOTableView->setModel(m_gameObjectTableModel.get());     // Устанавливаем модель на TableView
  // Разрешаем выделение строк
  ui.staticGOTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  // Устанавливаем режим выделения лишь одно строки в таблице
  ui.staticGOTableView->setSelectionMode(QAbstractItemView::SingleSelection);
  // Устанавливаем размер колонок по содержимому
  ui.staticGOTableView->resizeColumnsToContents();
  ui.staticGOTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui.staticGOTableView->horizontalHeader()->setStretchLastSection(true);

  ui.staticGOTableView->horizontalHeader()->setSortIndicatorShown(true);
  ui.staticGOTableView->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);

  connect(ui.staticGOTableView->selectionModel(),
    SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
    SLOT(staticGameObjectTableRowSelected(const QItemSelection &, const QItemSelection &)));

  fillComboBoxFromMap(ui.SGOTableOnPage, m_SGOTableOnPageCountMap);

  ui.SGOTableOrdrerDir->setCurrentIndex(0);
  ui.SGOTableSortField->setCurrentIndex(1);


  this->setStyleSheet(
    "QPushButton#SGOTableFirstPageBtn {"
    "background-color: red;"
    "border-style: outset;"
    "border-width: 2px;"
    "border-radius: 10px;"
    "border-color: beige;"
    "font: bold 14px;"
    "min-width: 10em;"
    "padding: 6px; "
    "icon: backward-icon"
    "}"
    );
  //ui.SGOTableFirstPageBtn->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward
    //));
  updateSGOTable();
}

void GameEditor::fillComboBoxFromMap(QComboBox* comboBox, std::map<int, std::string>& map)
{
  for (auto &elem : map)
  {
    comboBox->addItem(elem.second.c_str());
  }
}

void GameEditor::updateSGOTablePagingInfo()
{
  PagingInfo pagingInfo = m_gameObjectTableModel.get()->GetPagingInfo();
  ui.SGOTablePageTxt->setValidator(new QIntValidator(1, pagingInfo.pageCount, this));
  ui.SGOTablePageTxt->setText(QString::number(pagingInfo.pageNumber));
  ui.SGOTablePageCountTxt->setText(QString::number(pagingInfo.pageCount));

 
  ui.SGOTableFirstPageBtn->setEnabled(pagingInfo.pageNumber > 1);
  ui.SGOTablePrevPageBtn->setEnabled(pagingInfo.pageNumber > 1);

  ui.SGOTableLastBtn->setEnabled(pagingInfo.pageNumber < pagingInfo.pageCount);
  ui.SGOTableNextBtn->setEnabled(pagingInfo.pageNumber < pagingInfo.pageCount);
}

void GameEditor::updateSGOTable()
{
  m_gameObjectTableModel.get()->UpdateTable(ui.SGOTablePageTxt->text().toInt(),
    std::stoi(m_SGOTableOnPageCountMap[ui.SGOTableOnPage->currentIndex()]),
    m_SGOTableOrderFieldMap[ui.SGOTableSortField->currentIndex()].c_str(),
    ui.SGOTableOrdrerDir->currentIndex() == 0? "ASC": "DESC",
    ui.filterSGONameTxt->text().trimmed(),
    ui.filterSGOModelTxt->text().trimmed());

  updateSGOTablePagingInfo();
}

void GameEditor::on_addStaticGOBtn_clicked()
{
  AddStaticGameObjectDialog dialog(this);
  dialog.SetPathToModels(m_pathToModels);
  dialog.SetPathToMaterials(m_pathToMaterials);
  if (dialog.exec() == QDialog::Accepted) {
    m_gameObjectTableModel->append(dialog.GetStaticGameObject());
  }
}

void GameEditor::on_editStaticGOBtn_clicked()
{
  int selectedRow = ui.staticGOTableView->selectionModel()->currentIndex().row();
  StaticGameObjectDbInfo gameObject = m_gameObjectTableModel->GetStaticGameObject(selectedRow);

  AddStaticGameObjectDialog dialog(this);
  dialog.SetPathToModels(m_pathToModels);
  dialog.SetPathToMaterials(m_pathToMaterials);
  dialog.SetStaticGameObject(gameObject);

  if (dialog.exec() == QDialog::Accepted) {
    m_gameObjectTableModel->edit(dialog.GetStaticGameObject());
  }
}

void GameEditor::on_deleteStaticGOBtn_clicked()
{
  int selectedRow = ui.staticGOTableView->selectionModel()->currentIndex().row();
  int id = m_gameObjectTableModel->index(selectedRow, 0).data().toInt();
  m_gameObjectTableModel->remove(id);

  if (m_gameObjectTableModel->rowCount(QModelIndex()) == 0)
    StaticGameObjectBtnsStateConfigure();
}

void GameEditor::on_previewStaticGOBtn_clicked()
{
  int selectedRow = ui.staticGOTableView->selectionModel()->currentIndex().row();
  StaticGameObjectDbInfo gameObject = m_gameObjectTableModel->GetStaticGameObject(selectedRow);

  m_previewStaticGOWidget->SetStaticGameObject(gameObject);
  m_previewStaticGOWidget->show();
}

void GameEditor::staticGameObjectTableRowSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
  StaticGameObjectBtnsStateConfigure();
}

void GameEditor::StaticGameObjectBtnsStateConfigure()
{
  bool hasSelection = ui.staticGOTableView->selectionModel()->hasSelection();
  ui.editStaticGOBtn->setEnabled(hasSelection);
  ui.deleteStaticGOBtn->setEnabled(hasSelection);
  ui.previewStaticGOBtn->setEnabled(hasSelection);
}

void GameEditor::on_actionObjConverter_triggered()
{
  ObjConverterDialog objConverterDialog;
  objConverterDialog.SetPathToGEModels(m_pathToModels);
  objConverterDialog.SetPathToObjModels(m_pathToObjModels);
  objConverterDialog.SetPathToGEMaterials(m_pathToMaterials.toStdString());

  objConverterDialog.exec();
}

void GameEditor::on_SGOTableFirstPageBtn_clicked()
{
  ui.SGOTablePageTxt->setText("1");
  updateSGOTable();
}

void GameEditor::on_SGOTablePrevPageBtn_clicked()
{
  int currentPage = ui.SGOTablePageTxt->text().toInt();
  if (currentPage > 1) --currentPage;
  ui.SGOTablePageTxt->setText(QString::number(currentPage));

  updateSGOTable();
}

void GameEditor::on_SGOTableNextBtn_clicked()
{
  int currentPage = ui.SGOTablePageTxt->text().toInt();
  int pageCount = ui.SGOTablePageCountTxt->text().toInt();
  if (currentPage < pageCount) ++currentPage;
  ui.SGOTablePageTxt->setText(QString::number(currentPage));

  updateSGOTable();
}

void GameEditor::on_SGOTableLastBtn_clicked()
{
  ui.SGOTablePageTxt->setText(ui.SGOTablePageCountTxt->text());
  updateSGOTable();
}

void GameEditor::on_SGOTablePageTxt_editingFinished()
{
  updateSGOTable();
}

void GameEditor::on_SGOTableOrdrerDir_currentIndexChanged(int index)
{
  updateSGOTable();
}

void GameEditor::on_SGOTableSortField_currentIndexChanged(int index)
{
  updateSGOTable();
}

void GameEditor::on_SGOTableOnPage_currentIndexChanged(int index)
{
  updateSGOTable();
}

void GameEditor::on_filterSGONameTxt_editingFinished()
{
  updateSGOTable();
}

void GameEditor::on_filterSGOModelTxt_editingFinished()
{
  updateSGOTable();
}

void GameEditor::show()
{
  QMainWindow::show();
}