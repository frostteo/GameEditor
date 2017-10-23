#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include "PagingInfo.h"

class GETableSignals : public QAbstractTableModel
{
  Q_OBJECT

public:
    GETableSignals(QObject *parent);
    ~GETableSignals();
signals:
    void TableDataChanged();
    void PagingInfoChanged(PagingInfo pagingInfo);
};
