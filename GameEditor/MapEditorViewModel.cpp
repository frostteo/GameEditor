#include "MapEditorViewModel.h"
#include "Camera.h"
#include "LightininigSystem.h"
#include "AxisAlignedBBHelper.h"
#include "D3DConfigurer.h"

MapEditorViewModel::MapEditorViewModel()
{
  connect(&m_sgoOnMapTM, SIGNAL(FreezeSgoSignal(int)), this, SLOT(FreezeSgo(int)));
  connect(&m_sgoOnMapTM, SIGNAL(UnfreezeSgoSignal(int)), this, SLOT(UnfreezeSgo(int)));
  connect(&m_sgoOnMapTM, SIGNAL(SelectionChanged(std::vector<int>)), this, SLOT(SelectionChanged(std::vector<int>)));
}

void MapEditorViewModel::Initialize(const std::string& pathToModels, ModelFactory* modelFactory, MapEditorPreferences* mapEditorPreferences, D3DConfigurer* d3dConfigurer)
{
  m_d3dConfigurer = d3dConfigurer;
  m_pathToModels = pathToModels;
  m_modelFactory = modelFactory;
  m_mapEditorPreferences = mapEditorPreferences;

  m_pointLightOnMapService = DependencyResolver::GetPointLightOnMapService();
  InitializeSgos();
  InitializePointLights();
}

MapEditorViewModel::~MapEditorViewModel()
{
}


void MapEditorViewModel::InitializeSgos()
{
  for (auto& sgo : m_sgoOnMapTM.GetAll())
  {
    AddSgoToMap(sgo);
  }

  std::map<int, StaticGameObject*> temporarySgoMap;
  for (auto& sgo : m_staticGameObjectMap)
  {
    temporarySgoMap[sgo.first] = &(sgo.second);
  }
  m_octoTree.Initialize(&temporarySgoMap, XMFLOAT3(0.0f, 0.0f, 0.0f), OCT_TREE_CELL_HALF_SIZE);
}

void MapEditorViewModel::InitializePointLights()
{
  for (auto& pointLight : m_pointLightOnMapService->GetAll())
  {
    AddPointLightToMap(pointLight);
  }
}

void MapEditorViewModel::AddSgoToMap(SGOOnMapDbInfo& sgoOnMap)
{
  StaticGameObject sgo;
  sgo.SetModel(GetModel(sgoOnMap.staticGameObjectDbInfo.modelFileName.toStdString()));
  sgo.SetPosition(sgoOnMap.xPos, sgoOnMap.yPos, sgoOnMap.zPos);
  sgo.SetRotation(sgoOnMap.xRotate, sgoOnMap.yRotate, sgoOnMap.zRotate);
  sgo.dbInfoId = sgoOnMap.staticGameObjectDbInfo.id;
  sgo.isFrozen = sgoOnMap.isFrozen;
  sgo.uniqueId = sgoOnMap.id;
  sgo.castShadows = sgoOnMap.castShadows;
  m_staticGameObjectMap[sgoOnMap.id] = sgo;
}

void MapEditorViewModel::AddPointLightToMap(PointLightOnMapDbInfo& dbInfo)
{
  if (m_pointLightsOnMap.count(dbInfo.id) == 0)
  {
    PointLight pointLight;
    m_pointLightsOnMap[dbInfo.id] = pointLight;
    m_pointLightsOnMap[dbInfo.id].InitializeShadowResources(m_d3dConfigurer->GetDevice());
  }

  m_pointLightsOnMap[dbInfo.id].Initialize(
    dbInfo.linearAttenuation,
    dbInfo.quadraticAttenuation,
    XMFLOAT3(dbInfo.pointLightDbInfo.relativePosX, dbInfo.pointLightDbInfo.relativePosY, dbInfo.pointLightDbInfo.relativePosZ),
    XMFLOAT3(dbInfo.red, dbInfo.green, dbInfo.blue),
    &m_staticGameObjectMap[dbInfo.sgoOnMapId], 
    dbInfo.castShadows,
    static_cast<PointLightShadowDirection>(dbInfo.shadowDirections)
    );
}

Model* MapEditorViewModel::GetModel(const std::string& modelName)
{
  return m_modelFactory->GetResource(m_pathToModels + FileProcessor::FILE_SEPARATOR + modelName);
}

void MapEditorViewModel::AddSgo(SGOOnMapDbInfo& sgoOnMapDbInfo)
{
  m_sgoOnMapTM.append(sgoOnMapDbInfo);
  AddSgoToMap(sgoOnMapDbInfo);
  m_octoTree.AddSgo(sgoOnMapDbInfo.id, &m_staticGameObjectMap[sgoOnMapDbInfo.id]);
}

void MapEditorViewModel::AddPointLight(PointLightOnMapDbInfo& pointLightOnMapDbInfo)
{
  AddSgo(pointLightOnMapDbInfo.sgoOnMapDbInfo);
  pointLightOnMapDbInfo.sgoOnMapId = pointLightOnMapDbInfo.sgoOnMapDbInfo.id;
  m_pointLightOnMapService->Create(pointLightOnMapDbInfo);
  emit PointLightCountChanged(pointLightOnMapDbInfo.pointLightId);
  AddPointLightToMap(pointLightOnMapDbInfo);
}

void MapEditorViewModel::DeleteSgo(int id)
{
  m_sgoOnMapTM.remove(id);
  DeleteSgoFromMap(id);
}

void MapEditorViewModel::DeletePointLight(int id)
{
  auto pointLightOnMap = m_pointLightOnMapService->Get(id);
  int sgoOnMapId = pointLightOnMap.sgoOnMapId;
  m_pointLightOnMapService->Delete(id);
  DeletePointLightFromMap(pointLightOnMap.id);
  DeleteSgo(sgoOnMapId);
  emit PointLightCountChanged(pointLightOnMap.pointLightId);
}

void MapEditorViewModel::DeleteSgoFromMap(int id)
{
  m_octoTree.DeleteSgo(id, &m_staticGameObjectMap[id]);
  m_selectedObjectIds.erase(id);
  m_staticGameObjectMap.erase(id);
}

void MapEditorViewModel::DeletePointLightFromMap(int id)
{
  m_pointLightsOnMap.erase(id);
}

void MapEditorViewModel::SGODbInfoDeleted(int sgoDbInfoId)
{
  for (auto it = m_staticGameObjectMap.begin(), itEnd = m_staticGameObjectMap.end(); it != itEnd;)
  {
    if (it->second.dbInfoId == sgoDbInfoId)
    {
      m_octoTree.DeleteSgo(it->first, &m_staticGameObjectMap[it->first]);
      m_selectedObjectIds.erase(it->first);
      it = m_staticGameObjectMap.erase(it);
    }
    else
    {
      ++it;
    }
  }

  m_sgoOnMapTM.UpdateData();
}

void MapEditorViewModel::PointLightDbInfoDeleted(int pointLightId)
{
  auto pointLightsOnMap = m_pointLightOnMapService->GetByPointLightId(pointLightId);

  for (auto& pointLightOnMap : pointLightsOnMap)
  {
    DeletePointLight(pointLightOnMap.id);
  }
}

void MapEditorViewModel::PointLightDbInfoEdited(PointLightDbInfo& pointLight)
{
  //TODO FHolod: Внести изменение об отсносительной позиции или любые другие влияющие изменения
  auto pointLightsOnMap = m_pointLightOnMapService->GetByPointLightId(pointLight.id);

  if (pointLight.staticGameObjectId == 0)
  {
    auto sgo = m_pointLightOnMapService->GetDefaultPointLightSgo();
    pointLight.staticGameObjectId = sgo.id;
    pointLight.staticGameObjectDbInfo = sgo;
  }

  for (auto& pointLightOnMap : pointLightsOnMap)
  {
    auto sgoOnMap = pointLightOnMap.sgoOnMapDbInfo;
    sgoOnMap.staticGameObjectId = pointLight.staticGameObjectId;
    sgoOnMap.staticGameObjectDbInfo = pointLight.staticGameObjectDbInfo;
    EditPointLightOnMap(pointLightOnMap);
    EditSgo(sgoOnMap);
  }

}

void MapEditorViewModel::SGODbInfoEdited(StaticGameObjectDbInfo& staticGameObjectDbInfo)
{
  for (auto& sgo : m_staticGameObjectMap)
  {
    if (sgo.second.dbInfoId == staticGameObjectDbInfo.id)
    {
      sgo.second.SetModel(GetModel(staticGameObjectDbInfo.modelFileName.toStdString()));
    }
  }
}

void MapEditorViewModel::EditSgo(SGOOnMapDbInfo& editedGameObject)
{
  m_sgoOnMapTM.edit(editedGameObject);
  EditSgoOnMap(editedGameObject);
}

void MapEditorViewModel::EditPointLight(PointLightOnMapDbInfo& editedPointLightOnMapDbInfo)
{
  m_pointLightOnMapService->Update(editedPointLightOnMapDbInfo);
  EditSgo(editedPointLightOnMapDbInfo.sgoOnMapDbInfo);
  EditPointLightOnMap(editedPointLightOnMapDbInfo);
}

void MapEditorViewModel::EditSgoOnMap(SGOOnMapDbInfo& editedGameObject)
{
  AddSgoToMap(editedGameObject);
  m_octoTree.ObjectChangedPosition(editedGameObject.id, &m_staticGameObjectMap[editedGameObject.id]);
}

void MapEditorViewModel::EditPointLightOnMap(PointLightOnMapDbInfo& dbInfo)
{
  AddPointLightToMap(dbInfo);
}

void MapEditorViewModel::FreezeSgo(int id)
{
  m_sgoOnMapTM.FreezeSgo(id);
  m_staticGameObjectMap[id].isFrozen = true;
}

void MapEditorViewModel::UnfreezeSgo(int id)
{
  m_sgoOnMapTM.UnfreezeSgo(id);
  m_staticGameObjectMap[id].isFrozen = false;
}

void MapEditorViewModel::FreezeAll()
{
  for (auto& sgo : m_staticGameObjectMap) 
  {
    sgo.second.isFrozen = true;
  }

  m_sgoOnMapTM.FreezeAll();
}

void MapEditorViewModel::UnfreezeAll()
{
  for (auto& sgo : m_staticGameObjectMap)
  {
    sgo.second.isFrozen = false;
  }

  m_sgoOnMapTM.UnfreezeAll();
}

void MapEditorViewModel::FreezeSelected()
{
  for (int id : m_selectedObjectIds)
  {
    auto sgoInDb = m_sgoOnMapTM.GetEntityByKey(id);
    sgoInDb.isFrozen = true;
    EditSgo(sgoInDb);
  }
}

void MapEditorViewModel::UnfreezeSelected()
{
  for (int id : m_selectedObjectIds)
  {
    auto sgoInDb = m_sgoOnMapTM.GetEntityByKey(id);
    sgoInDb.isFrozen = false;
    EditSgo(sgoInDb);
  }
}

void MapEditorViewModel::SelectionChanged(std::vector<int> selectedSgoIds)
{
  SetSelectedObjectIds(selectedSgoIds);
}

void MapEditorViewModel::GetVisibleSgo(const Camera& camera, std::vector<StaticGameObject*>* sgosToRender)
{
  sgosToRender->clear();
  m_octoTree.GetVisibleSgo(camera, sgosToRender);
}

void MapEditorViewModel::GetVisiblePointLights(Camera* camera, LightininigSystem* lightiningSystem)
{
  lightiningSystem->ClearLights();

  XMFLOAT3 cameraPosition = camera->GetWorldPosition();
  float radius = m_mapEditorPreferences->GetRadiusOfAddingLightSourcesToRender();
  m_aabbForPointLight.Initialize(
    cameraPosition.x - radius,
    cameraPosition.y - radius,
    cameraPosition.z - radius,
    cameraPosition.x + radius,
    cameraPosition.y + radius,
    cameraPosition.z + radius
    );

  for (auto& pointLight : m_pointLightsOnMap)
  {
    if (AxisAlignedBBHelper::TwoAABBIntersects(m_aabbForPointLight, *pointLight.second.GetAABBBoundingBox()))
        lightiningSystem->AddPointLight(&pointLight.second);
  }
}

void MapEditorViewModel::GetSelectedSgos(std::vector<StaticGameObject*>* selectedSgos)
{
  selectedSgos->clear();
  selectedSgos->reserve(m_selectedObjectIds.size());

  for (int selectedId : m_selectedObjectIds)
  {
    selectedSgos->push_back(&m_staticGameObjectMap[selectedId]);
  }
}