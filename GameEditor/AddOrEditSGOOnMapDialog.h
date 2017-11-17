#pragma once

#include <math.h>
#include <QDialog>
#include "ui_AddOrEditSGOOnMapDialog.h"
#include "SGOOnMapDbInfo.h"

class AddOrEditSGOOnMapDialog : public QDialog, public Ui::AddOrEditSGOOnMapDialog
{
    Q_OBJECT
private:
  SGOOnMapDbInfo m_SGOOnMap;
public:
  AddOrEditSGOOnMapDialog(QWidget *parent = Q_NULLPTR);
  ~AddOrEditSGOOnMapDialog();
  void setSGOOnMap(SGOOnMapDbInfo gameObject);
  SGOOnMapDbInfo GetSGOOnMap();
  void done(int result) override;
};
