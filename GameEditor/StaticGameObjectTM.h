#pragma once

#include <algorithm>
#include "IStaticGOService.h"
#include "QtUtils.h"
#include "SGOMetadata.h"
#include "GETable.h"

class StaticGameObjectTM 
  : public GETable<StaticGameObjectDbInfo>
{
  Q_OBJECT
protected:
  IStaticGOService* m_staticGOService;

  std::string m_SGONameFilter = "";
  std::string m_modelFileNameFilter = "";
protected:
  virtual void FillOrderFieldMap() override;
  virtual void GetData() override;

  virtual void appendEntity(StaticGameObjectDbInfo& gameObject) override;
  virtual void editEntity(StaticGameObjectDbInfo& gameObject) override;
  virtual void removeEntity(int id) override;
public:
  StaticGameObjectTM(int onPage = 10, QObject * parent = {});
  virtual ~StaticGameObjectTM();
  int columnCount(const QModelIndex &) const override { return 4; }
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
 
  void UpdateTable(int pageNumber, int onPage, int orderFieldIndex, Qt::SortOrder orderDirection, QString SGONameFilter = "", QString SGOModelFilenameFilter = "");
  virtual StaticGameObjectDbInfo GetEntityByKey(int id) override;
  virtual bool ContainsInMemory(int id) override;
};

