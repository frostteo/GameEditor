#pragma once

#include <QAbstractTableModel>
#include <string>
#include <map>
#include "DependencyResolver.h"
#include "GetParameters.h"
#include "GETableSignals.h"

template <class T>
class GETable : public GETableSignals
{
protected:
  QList<T> m_data;
  GetParameters m_getParameters;
  PagingInfo m_pagingInfo;
  std::map<int, std::string> m_orderFieldMap;
protected:
  virtual void FillOrderFieldMap() = 0;
  void UpdateData();
  virtual void GetData() = 0;
  virtual void appendEntity(T& entity) = 0;
  virtual void editEntity(T& entity) = 0;
  virtual void removeEntity(int id) = 0;
public:
  GETable(QObject *parent = {});
  void Initialize(int onPage = 10);
  ~GETable() {}
  int rowCount(const QModelIndex &) const override { return m_data.count(); }
  void append(T& entity);
  void edit(T& entity);
  void remove(int id);
  T GetEntity(int rowNumber) { return m_data.at(rowNumber); }
  virtual T GetEntityByKey(int id) = 0;
  PagingInfo GetPagingInfo() { return m_pagingInfo; }
  virtual bool ContainsInMemory(int id) = 0;
};

template <class T>
GETable<T>::GETable(QObject *parent)
  : GETableSignals(parent)
{

}

template <class T>
void GETable<T>::Initialize(int onPage)
{
  m_getParameters.onPage = onPage;
  FillOrderFieldMap();
  UpdateData();
}

template <class T>
void GETable<T>::UpdateData()
{
  this->beginResetModel();
  GetData();
  this->endResetModel();
  emit TableDataChanged();
  emit PagingInfoChanged(m_pagingInfo);
}

template <class T>
void GETable<T>::append(T& entity)
{
  beginInsertRows({}, m_data.count(), m_data.count());
  appendEntity(entity);
  UpdateData();
  endInsertRows();
}

template <class T>
void GETable<T>::edit(T& entity)
{
  editEntity(entity);
  UpdateData();
}

template <class T>
void GETable<T>::remove(int id)
{
  removeEntity(id);
  UpdateData();
}