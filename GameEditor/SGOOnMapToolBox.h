#pragma once

#include <QWidget>
#include "ui_SGOOnMapToolBox.h"
#include "GameObjectType.h"

class SGOOnMapToolBox : public QWidget, public Ui::SGOOnMapToolBox
{
    Q_OBJECT
protected slots:
    void on_SGONameFilterTxt_editingFinished();
    void on_instanceNameFilterTxt_editingFinished();
    void on_gameObjectTypeFilter_currentIndexChanged(int index);
public:
signals :
  void FilterChanged();
public:
    SGOOnMapToolBox(QWidget *parent = Q_NULLPTR);
    ~SGOOnMapToolBox();
    QString GetSGONameFilter() { return this->SGONameFilterTxt->text().trimmed(); }
    QString GetInstanceNameFilter() { return this->instanceNameFilterTxt->text().trimmed(); }
    GameObjectType GetGameObjectTypeFilter() { return static_cast<GameObjectType>(this->gameObjectTypeFilter->currentData().toInt()); }
};
