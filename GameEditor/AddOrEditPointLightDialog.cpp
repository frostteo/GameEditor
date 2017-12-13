#include "AddOrEditPointLightDialog.h"

AddOrEditPointLightDialog::AddOrEditPointLightDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    float smalestGreaterThenZero = 0.000001f;

    QDoubleValidator* simpleValidator = new QDoubleValidator();
    QDoubleValidator* linearAttenuationValidator = new QDoubleValidator(smalestGreaterThenZero, INT_MAX, 6);
    QDoubleValidator* quadraticAttenuationValidator = new QDoubleValidator(0, INT_MAX, 6);

    simpleValidator->setLocale(QLocale::English);
    linearAttenuationValidator->setLocale(QLocale::English);
    quadraticAttenuationValidator->setLocale(QLocale::English);

    this->relPosXTxt->setValidator(simpleValidator);
    this->relPosYTxt->setValidator(simpleValidator);
    this->relPosZTxt->setValidator(simpleValidator);
    this->linearAttenuationTxt->setValidator(linearAttenuationValidator);
    this->quadraticAttenuationTxt->setValidator(quadraticAttenuationValidator);

    QSqlTableModel * model = new QSqlTableModel(this, ((QtUnitOfWork *)BLLDependencyResolver::GetUnitOfWork())->GetDatabase());
    model->setTable(m_sgoMetadata.GetTableName());
    model->select();

    QCompleter *completer = new QCompleter(model, this);
    completer->setCompletionColumn(1);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    this->sgoNameTxt->setCompleter(completer);
}

AddOrEditPointLightDialog::~AddOrEditPointLightDialog()
{
}

void AddOrEditPointLightDialog::SetPointLight(PointLightDbInfo pointLight)
{
  m_pointLight = pointLight;
  this->nameTxt->setText(pointLight.name);
  //this->sgoNameTxt->setText(pointLight.staticGameObjectDbInfo.name);
  this->relPosXTxt->setText(QString::number(pointLight.relativePosX));
  this->relPosYTxt->setText(QString::number(pointLight.relativePosY));
  this->relPosZTxt->setText(QString::number(pointLight.relativePosZ));
  this->linearAttenuationTxt->setText(QString::number(pointLight.linearAttenuation));
  this->quadraticAttenuationTxt->setText(QString::number(pointLight.quadraticAttenuation));
}

PointLightDbInfo AddOrEditPointLightDialog::GetPointLight()
{
  m_pointLight.name = this->nameTxt->text();
  m_pointLight.relativePosX = this->relPosXTxt->text().toFloat();
  m_pointLight.relativePosY = this->relPosYTxt->text().toFloat();
  m_pointLight.relativePosZ = this->relPosZTxt->text().toFloat();
  m_pointLight.linearAttenuation = this->linearAttenuationTxt->text().toFloat();
  m_pointLight.quadraticAttenuation = this->quadraticAttenuationTxt->text().toFloat();

  return m_pointLight;
}

void AddOrEditPointLightDialog::done(int result)
{
  if (result == QDialog::Accepted)
  {
    GetParameters getParameters;
    PagingInfo pagingInfo;
    QString errorsMsg = "";
    std::string trimmedSgoNameFromInput = this->sgoNameTxt->text().trimmed().toStdString();

    if (this->nameTxt->text().trimmed().isEmpty())
      errorsMsg += tr("Name must be defined\n");

    if (!trimmedSgoNameFromInput.empty()) {
      QList<StaticGameObjectDbInfo> sgosWithNameList = DependencyResolver::GetStaticGOService()->GetFiltered(getParameters, pagingInfo, trimmedSgoNameFromInput);

      if (sgosWithNameList.size() == 0 || sgosWithNameList.first().name != this->sgoNameTxt->text())
        errorsMsg += tr("static game object name must be selected from dropdown list\n");
      else if (sgosWithNameList.size() > 0)
        m_pointLight.staticGameObjectId = sgosWithNameList.first().id;
    }

    this->errorsMsgLbl->setText(errorsMsg);
    if (this->errorsMsgLbl->text().isEmpty())
      QDialog::done(result);
  }
  else
  {
    QDialog::done(result);
  }
}