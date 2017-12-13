#include "AddOrEditSGOOnMapDialog.h"

AddOrEditSGOOnMapDialog::AddOrEditSGOOnMapDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    QDoubleValidator* validator = new QDoubleValidator();
    validator->setLocale(QLocale::English);

    this->xPosTxt->setValidator(validator);
    this->yPosTxt->setValidator(validator);
    this->zPosTxt->setValidator(validator);
    this->xRotateTxt->setValidator(validator);
    this->yRotateTxt->setValidator(validator);
    this->zRotateTxt->setValidator(validator);
}

AddOrEditSGOOnMapDialog::~AddOrEditSGOOnMapDialog()
{
}

void AddOrEditSGOOnMapDialog::setSGOOnMap(SGOOnMapDbInfo gameObject)
{
  m_SGOOnMap = gameObject;
  this->xPosTxt->setText(QString::number(m_SGOOnMap.xPos));
  this->yPosTxt->setText(QString::number(m_SGOOnMap.yPos));
  this->zPosTxt->setText(QString::number(m_SGOOnMap.zPos));

  this->xRotateTxt->setText(QString::number(m_SGOOnMap.xRotate));
  this->yRotateTxt->setText(QString::number(m_SGOOnMap.yRotate));
  this->zRotateTxt->setText(QString::number(m_SGOOnMap.zRotate));

  QString instanceName = gameObject.instanceName;
  if (instanceName.isNull() || instanceName.isEmpty()) {
    instanceName = gameObject.staticGameObjectDbInfo.name;
    if (gameObject.staticGameObjectDbInfo.countOnMap > 0)
      instanceName += QString::number(gameObject.staticGameObjectDbInfo.countOnMap);
  }
  this->instanceNameTxt->setText(instanceName);
  this->isFrozenCheckBox->setChecked(m_SGOOnMap.isFrozen > 0);
}

SGOOnMapDbInfo AddOrEditSGOOnMapDialog::GetSGOOnMap()
{
  const float gradesInCircle = 360.0f;

  m_SGOOnMap.instanceName = this->instanceNameTxt->text().trimmed();
  m_SGOOnMap.xPos = this->xPosTxt->text().toFloat();
  m_SGOOnMap.yPos = this->yPosTxt->text().toFloat();
  m_SGOOnMap.zPos = this->zPosTxt->text().toFloat();

  m_SGOOnMap.xRotate = fmod(this->xRotateTxt->text().toFloat(), gradesInCircle);
  m_SGOOnMap.yRotate = fmod(this->yRotateTxt->text().toFloat(), gradesInCircle);
  m_SGOOnMap.zRotate = fmod(this->zRotateTxt->text().toFloat(), gradesInCircle);

  m_SGOOnMap.isFrozen = this->isFrozenCheckBox->isChecked()? 1 : 0;

  return m_SGOOnMap;
}

void AddOrEditSGOOnMapDialog::done(int result)
{
   QDialog::done(result);
}
