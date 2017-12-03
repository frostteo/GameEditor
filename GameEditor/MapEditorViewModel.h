#pragma once

#include <qobject.h>
#include <map>
#include <set>
#include <string>
#include "StaticGameObject.h"
#include "OctoTree.h"
#include "MapEditorPreferences.h"
#include "ModelFactory.h"
#include "SGOOnMapTM.h"

class MapEditorViewModel : public QObject
{
  Q_OBJECT
private:
  static const int OCT_TREE_CELL_HALF_SIZE = 32768;

  std::map<int, StaticGameObject> m_staticGameObjectMap;
  std::set<int> m_selectedObjectIds;
  OctoTree m_octoTree;
  MapEditorPreferences* m_mapEditorPreferences;
  std::string m_pathToModels;
  ModelFactory* m_modelFactory;
  SGOOnMapTM m_sgoOnMapTM;

protected:
  Model* GetModel(const std::string& modelName);

  void AddSgoToMap(SGOOnMapDbInfo& sgoOnMap);
  void DeleteSgoFromMap(int id);
  void EditSgoOnMap(SGOOnMapDbInfo& editedGameObject);

  void InitializeSgos();
public:
  MapEditorViewModel();
  virtual ~MapEditorViewModel();

  void Initialize(const std::string& pathToModels, ModelFactory* modelFactory, MapEditorPreferences* mapEditorPreferences);

  void GetVisibleSgo(CameraFrustrum* cameraFrustrum, std::vector<StaticGameObject*>* sgosToRender);
  void DeleteUnusedNodesInOctTree() { m_octoTree.DeleteUnusedNodes(); }
  void GetSelectedSgos(std::vector<StaticGameObject*>* selectedSgos);

  MapEditorPreferences* GetMapEditorPreferences() { return m_mapEditorPreferences; }
  SGOOnMapTM* GetSGOOnMapTM() { return &m_sgoOnMapTM; }
  std::map<int, StaticGameObject>* GetSgoMap() { return &m_staticGameObjectMap; }
  std::set<int>* GetSelectedSgoIds() { return &m_selectedObjectIds; }

  void AddSgo(SGOOnMapDbInfo& sgoOnMapDbInfo);
  void DeleteSgo(int id);
  void EditSgo(SGOOnMapDbInfo& editedGameObject);
  void EditPositionInSgoTableOnMapTableModel(int id, float x, float y, float z) { m_sgoOnMapTM.EditPosition(id, x, y, z); }
  void EditRotationInSgoTableOnMapTableModel(int id, float x, float y, float z) { m_sgoOnMapTM.EditRotation(id, x, y, z); }

  void FreezeAll();
  void UnfreezeAll();
  void FreezeSelected();
  void UnfreezeSelected();

  void SetSelectedObjectIds(std::vector<int>& selectedObjectIds) { m_selectedObjectIds.clear(); std::copy(selectedObjectIds.begin(), selectedObjectIds.end(), std::inserter(m_selectedObjectIds, m_selectedObjectIds.end())); }
  void ClearSelectionInSgoOnMapTable() { m_sgoOnMapTM.ClearSelection(); }
public slots:
  void SGODbInfoDeleted(int sgoDbInfoId);
  void SGODbInfoEdited(StaticGameObjectDbInfo& staticGameObjectDbInfo);
  void FreezeSgo(int id);
  void UnfreezeSgo(int id);
  void SelectionChanged(std::vector<int> selectedSgoIds);
};
