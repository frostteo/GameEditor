#pragma once

#include <algorithm>
#include "GETable.h"
#include "ISGOOnMapService.h"
#include "qstandarditemmodel.h"

class SGOOnMapTM : public GETable<SGOOnMapDbInfo>
{
  Q_OBJECT
protected:
  ISGOOnMapService* m_SGOOnMapService;
  std::string m_SGONameFilter = "";
  std::string m_instanceNameFilter = "";

  bool m_testCheckbox = true;
protected:
  virtual void FillOrderFieldMap() override;
  virtual void GetData() override;

  virtual void appendEntity(SGOOnMapDbInfo& gameObject) override;
  virtual void editEntity(SGOOnMapDbInfo& gameObject) override;
  virtual void removeEntity(int id) override;
public:
  SGOOnMapTM(int onPage = 10, QObject *parent = {});
  virtual ~SGOOnMapTM();

  ISGOOnMapService* GetSGOOnMapService() { return m_SGOOnMapService; }
  virtual SGOOnMapDbInfo GetEntityByKey(int id) override;
  virtual bool ContainsInMemory(int id) override;
  void UpdateTable(int pageNumber, int onPage, int orderFieldIndex, Qt::SortOrder orderDirection, QString SGONameFilter = "", QString instanceNameFilter = "");

  int columnCount(const QModelIndex &) const override { return 10; }
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex & index) const;
  bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

  void FreezeAll() { m_SGOOnMapService->FreezeAll(); UpdateData(); }
  void UnfreezeAll() { m_SGOOnMapService->UnfreezeAll(); UpdateData(); }
public slots:
  void EditPosition(int id, float x, float y, float z);
  void EditRotation(int id, float x, float y, float z);
signals:
  void SGOCountChanged(int id);
};
