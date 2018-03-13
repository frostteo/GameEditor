#include "AddStaticGameObjectDialog.h"

AddStaticGameObjectDialog::AddStaticGameObjectDialog(const std::string& pathToModels, QWidget *parent)
    : QDialog(parent),
    m_pathToModels(QString::fromStdString(pathToModels)),
    m_gameObject()
{
    setupUi(this);
}

void AddStaticGameObjectDialog::on_chooseModelFileBtn_clicked()
{
  QString modelFileName = QFileDialog::getOpenFileName(this,
    tr("Open model file name"), m_pathToModels, tr("Txt Files (*.txt)"));

  this->staticGOModelEdit->setText(QFileInfo(modelFileName).fileName());
}

void AddStaticGameObjectDialog::done(int result)
{
  if (result == QDialog::Accepted)
  {
    QString errorMsg = "";
    if (this->staticGONameEdit->text().trimmed().isEmpty())
      errorMsg += tr("Name must be defined\n");

    if (this->staticGOModelEdit->text().trimmed().isEmpty())
      errorMsg += tr("Model filename must be defined\n");

    this->errorsMsg->setText(errorMsg);

    if (this->errorsMsg->text().isEmpty())
      QDialog::done(result);
  }
  else
  {
    QDialog::done(result);
  }
}


void AddStaticGameObjectDialog::SetStaticGameObject(const StaticGameObjectDbInfo& gameObject)
{
  m_gameObject = gameObject;
  this->staticGONameEdit->setText(m_gameObject.name);
  this->staticGOModelEdit->setText(m_gameObject.modelFileName);
}

StaticGameObjectDbInfo AddStaticGameObjectDialog::GetStaticGameObject()
{
  m_gameObject.name = this->staticGONameEdit->text();
  m_gameObject.modelFileName = this->staticGOModelEdit->text();
  return m_gameObject;
}