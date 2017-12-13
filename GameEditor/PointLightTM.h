#pragma once

#include <algorithm>
#include "IPointLightService.h"
#include "QtUtils.h"
#include "PointLightMetadata.h"
#include "GETable.h"


class PointLightTM
  : public GETable<PointLightDbInfo>
{
protected:
  IPointLightService* m_pointLightService;

  std::string m_nameFilter = "";
  std::string m_sgoNameFilter = "";
protected:
  virtual void FillOrderFieldMap() override;
  virtual void GetData() override;

  virtual void appendEntity(PointLightDbInfo& gameObject) override;
  virtual void editEntity(PointLightDbInfo& gameObject) override;
  virtual void removeEntity(int id) override;
public:
  PointLightTM(int onPage = 10, QObject * parent = {});
  virtual ~PointLightTM(); 
  int columnCount(const QModelIndex &) const override { return 9; }
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

  void UpdateTable(int pageNumber, int onPage, int orderFieldIndex, Qt::SortOrder orderDirection, QString nameFilter = "", QString SGONameFilter = "");
  virtual PointLightDbInfo GetEntityByKey(int id) override;
  virtual bool ContainsInMemory(int id) override;
};

