#pragma once

#include <QDialog>
#include "ui_AddOrEditPointLightDialog.h"
#include "PointLightDbInfo.h"
#include "SGOMetadata.h"
#include "qcompleter.h"

class BLLDependencyResolver;
class DependencyResolver;

class AddOrEditPointLightDialog : public QDialog, public Ui::AddOrEditPointLightDialog
{
    Q_OBJECT
private:
  PointLightDbInfo m_pointLight;
  SGOMetadata m_sgoMetadata;
 protected slots:
  void on_sgoNameTxt_textChanged(const QString &text);
public:
  AddOrEditPointLightDialog(QWidget *parent = Q_NULLPTR);
  ~AddOrEditPointLightDialog();
  void SetPointLight(const PointLightDbInfo& pointLight);
  PointLightDbInfo GetPointLight();
  void done(int result) override;
};
