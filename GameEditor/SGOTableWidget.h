#pragma once

#include <string>
#include <memory>
#include <algorithm>
#include <QWidget>
#include <qtableview.h>
#include <qboxlayout.h>
#include "ui_SGOTableWidget.h"

class MapEditorPreferences;
class SGOWidgetToolBox;
class StaticGameObjectTM;
class QtGEPaginator;
class PreviewStaticGOWidget;
class AddStaticGameObjectDialog;
class StaticGameObjectDbInfo;
class PathesToShaderSet;

class SGOTableWidget : public QWidget
{
    Q_OBJECT
private:
  Ui::SGOTableWidget ui;

  std::string m_pathToModels;

  std::unique_ptr<SGOWidgetToolBox> m_SGOToolBox;
  std::unique_ptr<QTableView> m_SGOTable;
  std::unique_ptr<StaticGameObjectTM> m_SGOTableModel;
  std::unique_ptr<QtGEPaginator> m_SGOPaginator;
  
  std::unique_ptr<PreviewStaticGOWidget> m_previewStaticGOWidget;
protected slots:
  void on_addSGOBtn_clicked();
  void on_editSGOBtn_clicked();
  void on_deleteSGOBtn_clicked();
  void editBtnsStateConfigure();
  void SGOtableRowSelected(const QItemSelection& selected, const QItemSelection& deselected);
  void PaginatorPageChanged(int pageNumber, int onPage);
  void HeaderSectionClicked(int sectionIndex);
  
  void on_previewSGOBtn_clicked();
  void on_addToMapBtn_clicked();
  void on_SGODeletedFromMap(int id);
protected:
  void configureTable();
  void configureUI();
  void configurePaginator();
public slots:
  void UpdateTable();
  void CountOnMapChanged(int id);
public:
  SGOTableWidget(
    MapEditorPreferences* mapEditorPreferences,
    const std::string& pathToModels,
    const std::string& pathToMaterials,
    const PathesToShaderSet& pathesToShaders,
    QWidget *parent = Q_NULLPTR
    );

    ~SGOTableWidget();
signals:
    void AddToMap(StaticGameObjectDbInfo& gameObject);
    void BeforeDeleteSgo(int sgoId);
    void SGODeleted(int sgoId);
    void SGOEdited(StaticGameObjectDbInfo& gameObject);
};
