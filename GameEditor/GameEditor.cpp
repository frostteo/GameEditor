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
}

void GameEditor::on_addStaticGOBtn_clicked()
{
  AddStaticGameObjectDialog dialog(this);
  if (dialog.exec() == QDialog::Accepted) {
    StaticGameObject gameObject;
    gameObject.name = dialog.staticGONameEdit->text();
    gameObject.modelFileName = dialog.staticGOModelEdit->text();
    gameObject.materialFileName = dialog.staticGOMaterialEdit->text();
    m_gameObjectTableModel->append(gameObject);
  }
}