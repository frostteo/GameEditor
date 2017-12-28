#include "AddOrEditPointLightOnMapDialog.h"

AddOrEditPointLightOnMapDialog::AddOrEditPointLightOnMapDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    float smalestGreaterThenZero = 0.000001f;

    QDoubleValidator* validator = new QDoubleValidator();
    QDoubleValidator* colorValidator = new QDoubleValidator(0, 1, 6);
    QDoubleValidator* linearAttenuationValidator = new QDoubleValidator(smalestGreaterThenZero, INT_MAX, 6);
    QDoubleValidator* quadraticAttenuationValidator = new QDoubleValidator(0, INT_MAX, 6);

    validator->setLocale(QLocale::English);
    colorValidator->setLocale(QLocale::English);
    linearAttenuationValidator->setLocale(QLocale::English);
    quadraticAttenuationValidator->setLocale(QLocale::English);

    this->xPosTxt->setValidator(validator);
    this->yPosTxt->setValidator(validator);
    this->zPosTxt->setValidator(validator);
    this->xRotateTxt->setValidator(validator);
    this->yRotateTxt->setValidator(validator);
    this->zRotateTxt->setValidator(validator);

    this->redTxt->setValidator(colorValidator);
    this->greenTxt->setValidator(colorValidator);
    this->blueTxt->setValidator(colorValidator);
    this->linearAttenuationTxt->setValidator(linearAttenuationValidator);
    this->quadraticAttenuationTxt->setValidator(quadraticAttenuationValidator);
}

AddOrEditPointLightOnMapDialog::~AddOrEditPointLightOnMapDialog()
{
}

void AddOrEditPointLightOnMapDialog::SetPointLightOnMap(PointLightOnMapDbInfo pointLight)
{
  m_pointLightOnMap = pointLight;
  this->xPosTxt->setText(QString::number(m_pointLightOnMap.sgoOnMapDbInfo.xPos));
  this->yPosTxt->setText(QString::number(m_pointLightOnMap.sgoOnMapDbInfo.yPos));
  this->zPosTxt->setText(QString::number(m_pointLightOnMap.sgoOnMapDbInfo.zPos));

  this->xRotateTxt->setText(QString::number(m_pointLightOnMap.sgoOnMapDbInfo.xRotate));
  this->yRotateTxt->setText(QString::number(m_pointLightOnMap.sgoOnMapDbInfo.yRotate));
  this->zRotateTxt->setText(QString::number(m_pointLightOnMap.sgoOnMapDbInfo.zRotate));

  QString instanceName = m_pointLightOnMap.sgoOnMapDbInfo.instanceName;
  if (instanceName.isNull() || instanceName.isEmpty()) {
    instanceName = m_pointLightOnMap.sgoOnMapDbInfo.staticGameObjectDbInfo.name;
    if (m_pointLightOnMap.sgoOnMapDbInfo.staticGameObjectDbInfo.countOnMap > 0)
      instanceName += QString::number(m_pointLightOnMap.sgoOnMapDbInfo.staticGameObjectDbInfo.countOnMap);
  }
  this->instanceNameTxt->setText(instanceName);
  this->isFrozenCheckBox->setChecked(m_pointLightOnMap.sgoOnMapDbInfo.isFrozen > 0);

  this->redTxt->setText(QString::number(m_pointLightOnMap.red));
  this->greenTxt->setText(QString::number(m_pointLightOnMap.green));
  this->blueTxt->setText(QString::number(m_pointLightOnMap.blue));

  this->linearAttenuationTxt->setText(QString::number(m_pointLightOnMap.linearAttenuation));
  this->quadraticAttenuationTxt->setText(QString::number(m_pointLightOnMap.quadraticAttenuation));
}

PointLightOnMapDbInfo AddOrEditPointLightOnMapDialog::GetPointLightOnMap()
{
  const float gradesInCircle = 360.0f;

  m_pointLightOnMap.sgoOnMapDbInfo.instanceName = this->instanceNameTxt->text().trimmed();
  m_pointLightOnMap.sgoOnMapDbInfo.xPos = this->xPosTxt->text().toFloat();
  m_pointLightOnMap.sgoOnMapDbInfo.yPos = this->yPosTxt->text().toFloat();
  m_pointLightOnMap.sgoOnMapDbInfo.zPos = this->zPosTxt->text().toFloat();

  m_pointLightOnMap.sgoOnMapDbInfo.xRotate = fmod(this->xRotateTxt->text().toFloat(), gradesInCircle);
  m_pointLightOnMap.sgoOnMapDbInfo.yRotate = fmod(this->yRotateTxt->text().toFloat(), gradesInCircle);
  m_pointLightOnMap.sgoOnMapDbInfo.zRotate = fmod(this->zRotateTxt->text().toFloat(), gradesInCircle);

  m_pointLightOnMap.sgoOnMapDbInfo.isFrozen = this->isFrozenCheckBox->isChecked() ? 1 : 0;

  m_pointLightOnMap.red = this->redTxt->text().toFloat();
  m_pointLightOnMap.green = this->greenTxt->text().toFloat();
  m_pointLightOnMap.blue = this->blueTxt->text().toFloat();

  m_pointLightOnMap.linearAttenuation = this->linearAttenuationTxt->text().toFloat();
  m_pointLightOnMap.quadraticAttenuation = this->quadraticAttenuationTxt->text().toFloat();

  return m_pointLightOnMap;
}

void AddOrEditPointLightOnMapDialog::done(int result)
{
  QDialog::done(result);
}