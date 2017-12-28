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
  GameObjectType m_gameObjectTypeFilter = GameObjectType::ALL;

protected:
  virtual void FillOrderFieldMap() override;
  virtual void GetData() override;

  virtual void appendEntity(SGOOnMapDbInfo& gameObject) override;
  virtual void editEntity(SGOOnMapDbInfo& gameObject) override;
  virtual void removeEntity(int id) override;
public:
  SGOOnMapTM(int onPage = 10, QObject *parent = {});
  virtual ~SGOOnMapTM();

  QList<SGOOnMapDbInfo> GetAll() { return m_SGOOnMapService->GetAll(); }
  virtual SGOOnMapDbInfo GetEntityByKey(int id) override;
  virtual bool ContainsInMemory(int id) override;
  void UpdateTable(int pageNumber, int onPage, int orderFieldIndex, Qt::SortOrder orderDirection, QString SGONameFilter = "", QString instanceNameFilter = "", GameObjectType gameObjectType = GameObjectType::ALL);

  int columnCount(const QModelIndex &) const override { return 11; }
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex & index) const;
  bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

  void FreezeSgo(int id) { m_SGOOnMapService->FreezeSgo(id);  if (ContainsInMemory(id)) UpdateData(); }
  void UnfreezeSgo(int id) { m_SGOOnMapService->UnfreezeSgo(id);  if (ContainsInMemory(id)) UpdateData(); }
  void FreezeAll() { m_SGOOnMapService->FreezeAll(); UpdateData(); }
  void UnfreezeAll() { m_SGOOnMapService->UnfreezeAll(); UpdateData(); }
  void SetSelectedSGOIds(std::vector<int>& selectedSgoIds) { emit SelectionChanged(selectedSgoIds); }

  void ClearSelection() { emit ClearSelectionSignal(); }
public slots:
  void EditPosition(int id, float x, float y, float z);
  void EditRotation(int id, float x, float y, float z);
signals:
  void SGOCountChanged(int id);
  void FreezeSgoSignal(int id);
  void UnfreezeSgoSignal(int id);
  void SelectionChanged(std::vector<int> selectedSgoIds);
  void ClearSelectionSignal();
};
