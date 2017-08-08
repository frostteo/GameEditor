#include "GameEditor.h"

GameEditor::GameEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    BLLDependencyResolver::GetUnitOfWork()->Initialize(m_hostName, m_databaseName, m_connectionName);
    m_gameObjectTableModel = std::unique_ptr<StaticGameObjectTM>(new StaticGameObjectTM());

    this->createUI();
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
  connect(ui.staticGOTableView->selectionModel(),
    SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
    SLOT(staticGameObjectTableRowSelected(const QItemSelection &, const QItemSelection &)));
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
  StaticGameObject gameObject = m_gameObjectTableModel->GetStaticGameObject(selectedRow);

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
  StaticGameObject gameObject = m_gameObjectTableModel->GetStaticGameObject(selectedRow);

  PreviewStaticGOWidget previewStaticGOWidget(m_pathToModels, m_pathToMaterials);
  previewStaticGOWidget.SetStaticGameObject(gameObject);
  previewStaticGOWidget.exec();
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

  objConverterDialog.exec();
}
