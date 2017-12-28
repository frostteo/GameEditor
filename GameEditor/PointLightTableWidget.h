#pragma once

#include <QWidget>
#include "ui_PointLightTableWidget.h"
#include <memory>
#include <algorithm>
#include <qtableview.h>
#include <qboxlayout.h>
#include "PointLightWidgetToolBox.h"
#include "PointLightTM.h"
#include "QtGEPaginator.h"
#include "AddOrEditPointLightDialog.h"
#include "ConfigurePLRelativePosWidget.h"
#include "MapEditorPreferences.h"
#include "IPointLightService.h"

class PointLightTableWidget : public QWidget, public Ui::PointLightTableWidget
{
    Q_OBJECT
private:
  std::unique_ptr<PointLightWidgetToolBox> m_toolBox;
  std::unique_ptr<QTableView> m_table;
  std::unique_ptr<PointLightTM> m_tableModel;
  std::unique_ptr<QtGEPaginator> m_paginator;
  std::unique_ptr<ConfigurePLRelativePosWidget> m_configurePLRelativePosWidget;

  QString m_pathToModels;
  QString m_pathToMaterials;
  MapEditorPreferences* m_mapEditorPreferences;
  IPointLightService* m_pointLightService;
protected slots:
  void on_addPointLightBtn_clicked();
  void on_editPointLightBtn_clicked();
  void on_deletePointLightBtn_clicked();
  void on_configureRelPosBtn_clicked();
  void on_addToMapBtn_clicked();

  void editBtnsStateConfigure();
  void RowSelected(const QItemSelection& selected, const QItemSelection& deselected);
  void PaginatorPageChanged(int pageNumber, int onPage);
  void HeaderSectionClicked(int sectionIndex);
protected:
  void configureTable();
  void configureUI();
  void configurePaginator();
public slots:
  void UpdateTable();
  void PointLightPositionChanged(int id, float x, float y, float z);
  void SGOEditedSlot(StaticGameObjectDbInfo& gameObject);
  void SGODeletedSlot(int sgoId);
  void PointLightCountChanged(int id);
  void BeforeDeleteSgo(int id);
public:
  PointLightTableWidget(MapEditorPreferences* mapEditorPreferences, QString& pathToModels, QString& pathToMaterials, QWidget *parent = Q_NULLPTR);
    ~PointLightTableWidget();
signals:
    void AddToMap(PointLightDbInfo& pointLight);
    void DeletePointLight(int id);
    void PointLightDbInfoEdited(PointLightDbInfo& pointLight);
};
