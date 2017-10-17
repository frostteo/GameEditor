#pragma once

#include <map>
#include <string>
#include <QAbstractTableModel>
#include "DependencyResolver.h"
#include "IStaticGOService.h"
#include "QtUtils.h"
#include "GetParameters.h"
#include "PagingInfo.h"

class StaticGameObjectTM 
  : public QAbstractTableModel
{
  Q_OBJECT
protected:
  IStaticGOService* m_staticGOService;
  QList<StaticGameObjectDbInfo> m_data;
  GetParameters m_getParameters;
  PagingInfo m_pagingInfo;

  std::string m_SGONameFilter = "";
  std::string m_modelFileNameFilter = "";
  std::map<int, std::string> m_SGOTableOrderFieldMap;
protected:
  void UpdateData();
public:
  StaticGameObjectTM(int onPage = 10, QObject * parent = {});
  virtual ~StaticGameObjectTM();
  int rowCount(const QModelIndex &) const override { return m_data.count(); }
  int columnCount(const QModelIndex &) const override { return 3; }
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  void append(StaticGameObjectDbInfo& gameObject);
  void edit(StaticGameObjectDbInfo& gameObject);
  void remove(int id);
  StaticGameObjectDbInfo GetStaticGameObject(int rowNumber);
  PagingInfo GetPagingInfo() { return m_pagingInfo; }
  void UpdateTable(int pageNumber, int onPage, int orderFieldIndex, Qt::SortOrder orderDirection, QString SGONameFilter = "", QString SGOModelFilenameFilter = "");
 
signals:
  void TableDataChanged();
  void PagingInfoChanged(PagingInfo pagingInfo);
};

