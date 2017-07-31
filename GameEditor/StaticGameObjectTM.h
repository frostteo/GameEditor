#pragma once

#include <QAbstractTableModel>
#include "DependencyResolver.h"
#include "IStaticGOService.h"
#include "QtUtils.h"

class StaticGameObjectTM 
  : public QAbstractTableModel
{
protected:
  IStaticGOService* m_staticGOService;
  QList<StaticGameObject> m_data;
protected:
  void UpdateData();
public:
  StaticGameObjectTM(QObject * parent = {});
  virtual ~StaticGameObjectTM();
  int rowCount(const QModelIndex &) const override { return m_data.count(); }
  int columnCount(const QModelIndex &) const override { return 4; }
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  void append(const StaticGameObject& gameObject);
};

