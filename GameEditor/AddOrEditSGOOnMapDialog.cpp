#include "AddOrEditSGOOnMapDialog.h"

AddOrEditSGOOnMapDialog::AddOrEditSGOOnMapDialog(ISGOOnMapService* SGOOnMapService, QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    m_SGOOnMapService = SGOOnMapService;

    this->validationWarningLbl->setVisible(false);
    this->xPosTxt->setValidator(new QDoubleValidator());
    this->yPosTxt->setValidator(new QDoubleValidator());
    this->zPosTxt->setValidator(new QDoubleValidator());
    this->xRotateTxt->setValidator(new QDoubleValidator());
    this->yRotateTxt->setValidator(new QDoubleValidator());
    this->zRotateTxt->setValidator(new QDoubleValidator());
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

  return m_SGOOnMap;
}

void AddOrEditSGOOnMapDialog::done(int result)
{
  if (result == QDialog::Accepted)
  {
    this->validationWarningLbl->setVisible(false);

    GetParameters getParameter;
    PagingInfo pagingInfo;

    auto objectsWithSameName = m_SGOOnMapService->GetFiltered(getParameter, pagingInfo, "", this->instanceNameTxt->text().trimmed().toStdString());

    if (objectsWithSameName.count() > 0 && objectsWithSameName[0].id != m_SGOOnMap.id)
      this->validationWarningLbl->setVisible(true);
    else
      QDialog::done(result);
  }
  else
  {
    QDialog::done(result);
  }
}
