#pragma once

#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include "ui_AddStaticGameObjectDialog.h"
#include "StaticGameObjectDbInfo.h"

class AddStaticGameObjectDialog : public QDialog, public Ui::AddStaticGameObjectDialog
{
    Q_OBJECT
private slots:
  void on_chooseModelFileBtn_clicked();
protected:
  const QString m_pathToModels;
  StaticGameObjectDbInfo m_gameObject;
public:
  AddStaticGameObjectDialog(const std::string& pathToModels, QWidget* parent = Q_NULLPTR);
  ~AddStaticGameObjectDialog() = default;

  void SetStaticGameObject(const StaticGameObjectDbInfo& gameObject);
  StaticGameObjectDbInfo GetStaticGameObject();

  void done(int result) override;
};
