#pragma once

#include <QDialog>
#include "ui_AddOrEditPointLightDialog.h"
#include "PointLightDbInfo.h"
#include "qcompleter.h"
#include "BLLDependencyResolver.h"
#include "DependencyResolver.h"

class AddOrEditPointLightDialog : public QDialog, public Ui::AddOrEditPointLightDialog
{
    Q_OBJECT
private:
  PointLightDbInfo m_pointLight;
  SGOMetadata m_sgoMetadata;
public:
    AddOrEditPointLightDialog(QWidget *parent = Q_NULLPTR);
    ~AddOrEditPointLightDialog();
    void SetPointLight(PointLightDbInfo pointLight);
    PointLightDbInfo GetPointLight();
    void done(int result) override;
};
