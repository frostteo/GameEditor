#include "MapEditorControl.h"

MapEditorControl::MapEditorControl(MapEditorViewModel* mapEditorViewModel, std::vector<StaticGameObject*>* visibleSgos, Camera* camera)
{
  m_mapEditorViewModel = mapEditorViewModel;
  m_selectedObjectIds = m_mapEditorViewModel->GetSelectedSgoIds();
  m_staticGameObjectMap = m_mapEditorViewModel->GetSgoMap();
  m_visibleSgos = visibleSgos;
  m_mapEditorPreferences = m_mapEditorViewModel->GetMapEditorPreferences();
  m_camera = camera;
}


MapEditorControl::~MapEditorControl()
{
}

void MapEditorControl::EditGameObject(int id)
{
  SGOOnMapDbInfo gameObject = m_mapEditorViewModel->GetSGOOnMapTM()->GetEntityByKey(id);
  
  switch (gameObject.gameObjectType)
  {
    case GameObjectType::STATIC_GAME_OBJECT:
      EditSgoOnMap(id);
      break;
    case GameObjectType::POINT_LIGHT:
      auto pointLight = m_mapEditorViewModel->GetPointLightOnMapService()->GetBySgoOnMapId(gameObject.id);
      EditPointLightOnMap(pointLight.id);
      break;
  }
}

void MapEditorControl::EditSgoOnMap(int id)
{
  SGOOnMapDbInfo gameObject = m_mapEditorViewModel->GetSGOOnMapTM()->GetEntityByKey(id);
  AddOrEditSGOOnMapDialog dialog;
  dialog.setSGOOnMap(gameObject);

  if (dialog.exec() == QDialog::Accepted) {
    SGOOnMapDbInfo editedGameObject = dialog.GetSGOOnMap();
    m_mapEditorViewModel->EditSgo(editedGameObject);
  }
}

void MapEditorControl::EditPointLightOnMap(int id)
{
  auto gameObject = m_mapEditorViewModel->GetPointLightOnMapService()->Get(id);
  AddOrEditPointLightOnMapDialog dialog;
  dialog.SetPointLightOnMap(gameObject);

  if (dialog.exec() == QDialog::Accepted) {
    auto editedGameObject = dialog.GetPointLightOnMap();
    m_mapEditorViewModel->EditPointLight(editedGameObject);
  }
}

void MapEditorControl::Delete(std::vector<int>& ids)
{
  m_mapEditorViewModel->SetSelectedObjectIds(std::vector<int>()); //TODO FHolod: возможно этот метод должен быть protected

  for (int id : ids) {
    SGOOnMapDbInfo gameObject = m_mapEditorViewModel->GetSGOOnMapTM()->GetEntityByKey(id);

    switch (gameObject.gameObjectType)
    {
      case GameObjectType::STATIC_GAME_OBJECT:
        DeleteSgo(id);
        break;
      case GameObjectType::POINT_LIGHT:
        auto pointLight = m_mapEditorViewModel->GetPointLightOnMapService()->GetBySgoOnMapId(gameObject.id);
        DeletePointLight(pointLight.id);
        break;
    }
    m_camera->needRebuildDependOnWorldMatrix = true;
  }
}

void MapEditorControl::DeleteSgo(int id)
{
  m_mapEditorViewModel->DeleteSgo(id);
}

void MapEditorControl::DeletePointLight(int id)
{
  m_mapEditorViewModel->DeletePointLight(id);
}

void MapEditorControl::Clone(std::vector<int>& ids)
{
  for (int id : ids)
  {
    SGOOnMapDbInfo gameObject = m_mapEditorViewModel->GetSGOOnMapTM()->GetEntityByKey(id);
    
    switch (gameObject.gameObjectType)
    {
    case GameObjectType::STATIC_GAME_OBJECT:
      CloneSgo(id);
      break;
    case GameObjectType::POINT_LIGHT:
      auto pointLight = m_mapEditorViewModel->GetPointLightOnMapService()->GetBySgoOnMapId(gameObject.id);
      ClonePointLight(pointLight.id);
      break;
    }
  }
}

void MapEditorControl::CloneSgo(int id)
{
  SGOOnMapDbInfo gameObject = m_mapEditorViewModel->GetSGOOnMapTM()->GetEntityByKey(id);
  gameObject.id = 0;

  if (gameObject.staticGameObjectDbInfo.countOnMap > 0)
    gameObject.instanceName = gameObject.staticGameObjectDbInfo.name + QString::number(gameObject.staticGameObjectDbInfo.countOnMap);

  AddOrEditSGOOnMapDialog dialog;
  dialog.setSGOOnMap(gameObject);

  if (dialog.exec() == QDialog::Accepted) {
    SGOOnMapDbInfo clonedGameObject = dialog.GetSGOOnMap();
    m_mapEditorViewModel->AddSgo(clonedGameObject);
  }
}

void MapEditorControl::ClonePointLight(int id)
{
  auto gameObject = m_mapEditorViewModel->GetPointLightOnMapService()->Get(id);
  gameObject.id = 0;

  if (gameObject.pointLightDbInfo.countOnMap > 0)
    gameObject.sgoOnMapDbInfo.instanceName = gameObject.pointLightDbInfo.name + QString::number(gameObject.pointLightDbInfo.countOnMap);

  AddOrEditPointLightOnMapDialog dialog;
  dialog.SetPointLightOnMap(gameObject);

  if (dialog.exec() == QDialog::Accepted) {
    auto clonedGameObject = dialog.GetPointLightOnMap();
    m_mapEditorViewModel->AddPointLight(clonedGameObject);
  }
}

void MapEditorControl::ProcessUserInput(InputState* inputState)
{
  if (m_camera)
  {
    if (inputState->IsKeyDown(DIK_LCONTROL) && inputState->IsKeyDown(DIK_F) && m_selectedObjectIds->size() > 0)
    {
      if (inputState->IsKeyDown(DIK_LSHIFT))
        m_mapEditorViewModel->UnfreezeSelected();
      else
        m_mapEditorViewModel->FreezeSelected();
    }
   

    if (inputState->IsKeyDown(DIK_LCONTROL) && inputState->IsKeyDown(DIK_E) && m_selectedObjectIds->size() == 1)
      EditGameObject((*m_selectedObjectIds->begin()));

    if (inputState->IsKeyPressed(DIK_DELETE) && !m_selectedObjectIds->empty())
      Delete();

    m_timeInSecondsBetweenFrames = inputState->time * 0.001f;

    if (inputState->IsMouseBtnPressed(MouseButtons::LeftMouseBtn))
      PickObject(inputState, inputState->mouseXCoor, inputState->mouseYCoor);
  
    MoveCamera(inputState);

    if (inputState->IsKeyDown(DIK_LCONTROL) && inputState->IsKeyDown(DIK_C) && !m_selectedObjectIds->empty())
    {
      Clone();
    }
    else if (inputState->IsKeyDown(DIK_C) && !m_selectedObjectIds->empty())
    {
      auto gameObject = m_staticGameObjectMap->at((*m_selectedObjectIds->begin()));
      GEMath::LookToObjectFromWorldFront(m_camera, &gameObject);
    }
      
    if (inputState->IsKeyPressed(DIK_T) && !m_selectedObjectIds->empty())
    {
      auto gameObject = m_staticGameObjectMap->at((*m_selectedObjectIds->begin()));
      GEMath::LookToObjectFromWorldUp(m_camera, &gameObject);
    }

    if (inputState->IsKeyDown(DIK_LSHIFT))
    {
      if (!m_selectedObjectIds->empty())
      {
        RotateCameraAroundObject(inputState);
      }
      else {
        RotateCamera(inputState);
      }
    }

    if (!m_selectedObjectIds->empty())
    {
      if (inputState->IsMouseBtnDown(MouseButtons::LeftMouseBtn))
        MoveObjects(inputState);
      
      if (inputState->IsMouseBtnDown(MouseButtons::RightMouseBtn))
        RotateObjects(inputState);

      if (inputState->IsMouseBtnReleased(MouseButtons::LeftMouseBtn) && m_sgoTranslated)
        SaveChangedPositionsInDB();

      if (inputState->IsMouseBtnReleased(MouseButtons::RightMouseBtn) && m_sgoRotated)
        SaveChangedRotationsInDB();
    }
  }
}

void MapEditorControl::SaveChangedPositionsInDB()
{
  m_sgoTranslated = false;
  m_needRecalculateAcumulativePositionForSnap = true;
  for (int selectedId : (*m_selectedObjectIds))
  {
    XMFLOAT3 position = m_staticGameObjectMap->at(selectedId).GetPosition();
    auto gameObject = m_mapEditorViewModel->GetSGOOnMapTM()->GetEntityByKey(selectedId);
    gameObject.xPos = position.x;
    gameObject.yPos = position.y;
    gameObject.zPos = position.z;
    m_mapEditorViewModel->EditSgo(gameObject);
  }
}

void MapEditorControl::SaveChangedRotationsInDB()
{
  m_sgoRotated = false;
  m_needRecalculateAcumulativeRotationForSnap = true;
  for (int selectedId : (*m_selectedObjectIds))
  {
    XMFLOAT3 rotation = m_staticGameObjectMap->at(selectedId).GetRotation();
    auto gameObject = m_mapEditorViewModel->GetSGOOnMapTM()->GetEntityByKey(selectedId);
    gameObject.xRotate = rotation.x;
    gameObject.yRotate = rotation.y;
    gameObject.zRotate = rotation.z;
    m_mapEditorViewModel->EditSgo(gameObject);
  }
}

void MapEditorControl::RotateCameraAroundObject(InputState* inputState)
{
  const float angleDirectCameraToObject = 0.05f;
  XMMATRIX newCameraMatrix;
  XMVECTOR helper;
  XMFLOAT3 objectPosition;
  XMFLOAT3 cameraPosition;
  XMVECTOR forwardCameraVector;
  XMVECTOR rightCameraVector;
  XMVECTOR cameraPositionXm;
  XMVECTOR objectPositionXm;
  XMVECTOR vectorToObject;
  float angleBeetwenForwardCamAndToObject;

  float deltaXRadians = XMConvertToRadians(inputState->m_mouseState.lX * m_mapEditorPreferences->GetCameraRotationSpeed() * m_timeInSecondsBetweenFrames);
  float deltaYRadians = XMConvertToRadians(inputState->m_mouseState.lY * m_mapEditorPreferences->GetCameraRotationSpeed() * m_timeInSecondsBetweenFrames);

  objectPosition = GetCenterOfSelectedObjects(false);
  cameraPosition = m_camera->GetPosition();
  forwardCameraVector = m_camera->GetForward();
  rightCameraVector = m_camera->GetRight();

  cameraPositionXm = XMLoadFloat3(&cameraPosition);
  objectPositionXm = XMLoadFloat3(&objectPosition);
  vectorToObject = objectPositionXm - cameraPositionXm;

  angleBeetwenForwardCamAndToObject = XMVectorGetX(XMVector3AngleBetweenNormals(forwardCameraVector, XMVector3Normalize(vectorToObject)));

  if (angleBeetwenForwardCamAndToObject <= angleDirectCameraToObject) {
    m_needRecalculateRotationAroundPoint = true;
    m_rotateAroundPoint = objectPositionXm;
  }
  else 
    if (m_needRecalculateRotationAroundPoint)
    {
      XMFLOAT3 forwardCameraReadable;
      XMStoreFloat3(&forwardCameraReadable, forwardCameraVector);

      float lambda = (forwardCameraReadable.x * (objectPosition.x - cameraPosition.x) + forwardCameraReadable.y * (objectPosition.y - cameraPosition.y) + forwardCameraReadable.z * (objectPosition.z - cameraPosition.z)) / (pow(forwardCameraReadable.x, 2) + pow(forwardCameraReadable.y, 2) + pow(forwardCameraReadable.z, 2));

      float targetX, targetY, targetZ;
      targetX = cameraPosition.x + forwardCameraReadable.x * lambda;
      targetY = cameraPosition.y + forwardCameraReadable.y * lambda;
      targetZ = cameraPosition.z + forwardCameraReadable.z * lambda;
      m_rotateAroundPoint = XMVectorSet(targetX, targetY, targetZ, 0.0f);

    m_needRecalculateRotationAroundPoint = false;
  }

  newCameraMatrix = GEMath::GetCameraMatrixRotateAroundTarget(cameraPositionXm, m_rotateAroundPoint, deltaXRadians, deltaYRadians, rightCameraVector);
  m_camera->SetWorldMatrix(XMMatrixInverse(&helper, newCameraMatrix));
}

XMMATRIX MapEditorControl::GetCameraMatrixRotateAroundTarget(XMVECTOR cameraPosition, XMVECTOR targetPoint, float deltaXRadians, float deltaYRadians)
{
  XMVECTOR camPosInTargetCoordSystem = cameraPosition - targetPoint;
  float camPosInTargetCoordSystemLength = XMVectorGetX(XMVector3Length(camPosInTargetCoordSystem));

  float azimutal = atan(XMVectorGetZ(camPosInTargetCoordSystem) / XMVectorGetX(camPosInTargetCoordSystem));
  float colatitude = acos(XMVectorGetY(camPosInTargetCoordSystem) / camPosInTargetCoordSystemLength);

  if (XMVectorGetX(camPosInTargetCoordSystem) < 0.0f)
  {
      azimutal = XM_PI + azimutal;
      deltaYRadians = -deltaYRadians;
  } 
  azimutal += deltaXRadians;
  colatitude += deltaYRadians;
 
  float x, y, z;
  float sinColatitude, cosColatitude, sinAzimutal, cosAzimutal;
  sinColatitude = sin(colatitude);
  cosColatitude = cos(colatitude);
  sinAzimutal = sin(azimutal);
  cosAzimutal = cos(azimutal);

  x = XMVectorGetX(targetPoint) + camPosInTargetCoordSystemLength * sinColatitude * cosAzimutal;
  z = XMVectorGetZ(targetPoint) + camPosInTargetCoordSystemLength * sinColatitude * sinAzimutal;
  y = XMVectorGetY(targetPoint) + camPosInTargetCoordSystemLength * cosColatitude;

  XMVECTOR newCameraPosition = XMVectorSet(x, y, z, 0.0f);

  return XMMatrixLookAtLH(newCameraPosition, targetPoint, GEMath::UpWorld);
}

float MapEditorControl::GetCorrectedWithSnapCoord(float coord, float snapSize)
{
  return round(coord / snapSize) * snapSize;
}

void MapEditorControl::CalculateDifferenceWithPoint(std::map<int, XMFLOAT3>* differenceFromPoint, XMFLOAT3 point)
{
  for (int selectedObjectId : (*m_selectedObjectIds))
  {
    XMFLOAT3 differenceWithCenter;
    XMFLOAT3 objectPosition = m_staticGameObjectMap->at(selectedObjectId).GetPosition();
    differenceWithCenter.x = objectPosition.x - point.x;
    differenceWithCenter.y = objectPosition.y - point.y;
    differenceWithCenter.z = objectPosition.z - point.z;
    (*differenceFromPoint)[selectedObjectId] = differenceWithCenter;
  }
}

void MapEditorControl::MoveObjects(InputState* inputState)
{
  if (AllSelectedObjectsAreFrozen())
    return;

  std::map<int, XMFLOAT3> differenceFromCenter;
  XMFLOAT3 centerOfSelectedObjectsGroup;

  float deltaX = inputState->m_mouseState.lX * m_mapEditorPreferences->GetObjectMoveSpeed() * m_timeInSecondsBetweenFrames;
  float deltaY = inputState->m_mouseState.lY * m_mapEditorPreferences->GetObjectMoveSpeed() * m_timeInSecondsBetweenFrames;

  if (deltaX == 0.0f && deltaY == 0.0f)
    return;

  centerOfSelectedObjectsGroup = GetCenterOfSelectedObjects(true);
  CalculateDifferenceWithPoint(&differenceFromCenter, centerOfSelectedObjectsGroup);

  if (m_mapEditorPreferences->GetSnapToGridState() && m_needRecalculateAcumulativePositionForSnap)
  {
    m_accumulativePositionForSnap = centerOfSelectedObjectsGroup;
    m_needRecalculateAcumulativePositionForSnap = false;
  }

  if (inputState->IsKeyDown(DIK_Z))
  {
    if (m_mapEditorPreferences->GetSnapToGridState()) {
      m_accumulativePositionForSnap.y -= deltaY;
      centerOfSelectedObjectsGroup.y = GetCorrectedWithSnapCoord(m_accumulativePositionForSnap.y, m_mapEditorPreferences->GetGridSnapSize());
    }
    else {
      centerOfSelectedObjectsGroup.y -= deltaY;
    }
  }
  else
  {
    XMVECTOR rightCameraVector;
    XMVECTOR forwardMoveVector;
    bool needMoveXAxis = inputState->IsKeyDown(DIK_X);
    bool needMoveZAxis = inputState->IsKeyDown(DIK_Y);
    if (needMoveZAxis == needMoveXAxis)
    {
      needMoveXAxis = true;
      needMoveZAxis = true;
    }

    rightCameraVector = m_camera->GetRight();
    forwardMoveVector = XMVector3Normalize(XMVector3Cross(rightCameraVector, GEMath::UpWorld));

    if (m_mapEditorPreferences->GetSnapToGridState()) {

      if (needMoveXAxis) {
        m_accumulativePositionForSnap.x += deltaX * XMVectorGetX(rightCameraVector);
        m_accumulativePositionForSnap.x += deltaY * XMVectorGetX(forwardMoveVector);
      }

      if (needMoveZAxis) {
        m_accumulativePositionForSnap.z += deltaX * XMVectorGetZ(rightCameraVector);
        m_accumulativePositionForSnap.z += deltaY * XMVectorGetZ(forwardMoveVector);
      }

      centerOfSelectedObjectsGroup.x = GetCorrectedWithSnapCoord(m_accumulativePositionForSnap.x, m_mapEditorPreferences->GetGridSnapSize());
      centerOfSelectedObjectsGroup.z = GetCorrectedWithSnapCoord(m_accumulativePositionForSnap.z, m_mapEditorPreferences->GetGridSnapSize());
    }
    else {

      if (needMoveXAxis) {
        centerOfSelectedObjectsGroup.x += deltaX * XMVectorGetX(rightCameraVector);
        centerOfSelectedObjectsGroup.x += deltaY * XMVectorGetX(forwardMoveVector);
      }
      if (needMoveZAxis) {
        centerOfSelectedObjectsGroup.z += deltaX * XMVectorGetZ(rightCameraVector);
        centerOfSelectedObjectsGroup.z += deltaY * XMVectorGetZ(forwardMoveVector);
      }

    }
  }

  for (int selectedObjectId : (*m_selectedObjectIds))
  {
    if (!(*m_staticGameObjectMap)[selectedObjectId].isFrozen) {
      (*m_staticGameObjectMap)[selectedObjectId].SetPosition(centerOfSelectedObjectsGroup.x + differenceFromCenter[selectedObjectId].x, centerOfSelectedObjectsGroup.y + differenceFromCenter[selectedObjectId].y, centerOfSelectedObjectsGroup.z + differenceFromCenter[selectedObjectId].z);
    }
  }
  m_sgoTranslated = true;
}

void MapEditorControl::RotateObjects(InputState* inputState)
{
  if (AllSelectedObjectsAreFrozen())
    return;

  XMFLOAT3 centerOfSelectedObjects; 
  XMMATRIX newRotaions;
  float correctedAngleWithSnap;
  float deltaX = inputState->m_mouseState.lX * m_mapEditorPreferences->GetObjectRotationSpeed() * m_timeInSecondsBetweenFrames;
  float deltaY = inputState->m_mouseState.lY * m_mapEditorPreferences->GetObjectRotationSpeed() * m_timeInSecondsBetweenFrames;

  if (deltaX == 0.0f && deltaY == 0.0f)
    return;
  
  centerOfSelectedObjects = GetCenterOfSelectedObjects(true);

  if (m_mapEditorPreferences->GetSnapToAngleState() && m_needRecalculateAcumulativeRotationForSnap)
  {
    m_accumulativeRotationForSnap = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_needRecalculateAcumulativeRotationForSnap = false;
  }

  if (inputState->IsKeyDown(DIK_Z))
  {
    if (m_mapEditorPreferences->GetSnapToAngleState())
    {
      m_accumulativeRotationForSnap.z += deltaX;
      correctedAngleWithSnap = GetCorrectedWithSnapCoord(m_accumulativeRotationForSnap.z, m_mapEditorPreferences->GetAngleSnap());
      newRotaions = XMMatrixRotationZ(XMConvertToRadians(correctedAngleWithSnap));
      if (correctedAngleWithSnap != 0.0f)
        m_accumulativeRotationForSnap.z = 0.0f;
    }
    else
    {
      newRotaions = XMMatrixRotationZ(XMConvertToRadians(deltaX));
    }
  }
  else if (inputState->IsKeyDown(DIK_X))
  {
    if (m_mapEditorPreferences->GetSnapToAngleState())
    {
      m_accumulativeRotationForSnap.x += deltaY;
      correctedAngleWithSnap = GetCorrectedWithSnapCoord(m_accumulativeRotationForSnap.x, m_mapEditorPreferences->GetAngleSnap());
      newRotaions = XMMatrixRotationX(XMConvertToRadians(correctedAngleWithSnap));
      if (correctedAngleWithSnap != 0.0f)
        m_accumulativeRotationForSnap.x = 0.0f;
    }
    else
    {
      newRotaions = XMMatrixRotationX(XMConvertToRadians(deltaY));
    }
   
  }
  else
  {
    if (m_mapEditorPreferences->GetSnapToAngleState())
    {
      m_accumulativeRotationForSnap.y += deltaX;
      correctedAngleWithSnap = GetCorrectedWithSnapCoord(m_accumulativeRotationForSnap.y, m_mapEditorPreferences->GetAngleSnap());
      newRotaions = XMMatrixRotationY(XMConvertToRadians(correctedAngleWithSnap));
      if (correctedAngleWithSnap != 0.0f)
        m_accumulativeRotationForSnap.y = 0.0f;
    }
    else 
    {
      newRotaions = XMMatrixRotationY(XMConvertToRadians(deltaX));
    }
  }

  for (int selectedObjectId : (*m_selectedObjectIds))
  {
    if (!(*m_staticGameObjectMap)[selectedObjectId].isFrozen)
    {
      XMMATRIX worldMatrix;
      (*m_staticGameObjectMap)[selectedObjectId].GetWorldMatrix(worldMatrix);
      worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(-centerOfSelectedObjects.x, -centerOfSelectedObjects.y, -centerOfSelectedObjects.z));
      worldMatrix = XMMatrixMultiply(worldMatrix, newRotaions);
      worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(centerOfSelectedObjects.x, centerOfSelectedObjects.y, centerOfSelectedObjects.z));

      (*m_staticGameObjectMap)[selectedObjectId].SetWorldMatrix(worldMatrix);
    }
  }
  m_sgoRotated = true;
}

void MapEditorControl::MoveCamera(InputState* inputState)
{
  int deltaZ = inputState->m_mouseState.lZ;

  if (deltaZ) {
    m_camera->MoveForward(deltaZ * m_mapEditorPreferences->GetCameraZoomSpeed() * m_timeInSecondsBetweenFrames);
  }

  if (inputState->IsKeyDown(DIK_SPACE) || inputState->IsMouseBtnDown(MouseButtons::WheelMouseBtn))
  {
    int deltaX = inputState->m_mouseState.lX;
    int deltaY = inputState->m_mouseState.lY;

    if (deltaX)
      m_camera->MoveRight(deltaX * m_mapEditorPreferences->GetCameraPanSpeed() * m_timeInSecondsBetweenFrames);

    if (deltaY)
      m_camera->MoveUp(deltaY * m_mapEditorPreferences->GetCameraPanSpeed() * m_timeInSecondsBetweenFrames);
  }
}

void MapEditorControl::RotateCamera(InputState* inputState)
{
  float deltaX = inputState->m_mouseState.lX;
  float deltaY = inputState->m_mouseState.lY;

  if (deltaX == 0.0f && deltaY == 0.0f)
    return;

  m_camera->ChangeYRotation(deltaX * m_mapEditorPreferences->GetCameraRotationSpeed() * m_timeInSecondsBetweenFrames);
  m_camera->ChangeXRotation(deltaY * m_mapEditorPreferences->GetCameraRotationSpeed() * m_timeInSecondsBetweenFrames);
}

void MapEditorControl::PickObject(InputState* inputState, int mouseXCoor, int mouseYCoor)
{
  XMMATRIX projectionMatrix;
  XMMATRIX cameraWorldMatrix;
  XMFLOAT4X4 projectionMatrixReadable;
  XMVECTOR pickRayInViewSpaceDir;
  XMVECTOR pickRayInCameraWorldSpaceDir;
  XMVECTOR pickRayInCameraWorldSpacePos;
  XMVECTOR pickRayInObjectSpaceDir;
  XMVECTOR pickRayInObjectSpacePos;
  XMFLOAT3 cameraPosition;
  XMMATRIX objectWorldMatrix;
  XMVECTOR matInvDeter;
  float minDistance = INT_FAST32_MAX;
  float viewSpaceCursorXCoor, viewSpaceCursorYCoor, viewSpaceCursorZCoor;

  m_camera->GetProjectionMatrix(projectionMatrix);
  XMStoreFloat4x4(&projectionMatrixReadable, projectionMatrix);

  viewSpaceCursorXCoor = (mouseXCoor * 2.0f / m_camera->GetScreenWidth() - 1.0f) / projectionMatrixReadable._11;
  viewSpaceCursorYCoor = -(mouseYCoor * 2.0f / m_camera->GetScreenHeight() - 1.0f) / projectionMatrixReadable._22;
  viewSpaceCursorZCoor = 1.0f;

  pickRayInViewSpaceDir = XMVectorSet(viewSpaceCursorXCoor, viewSpaceCursorYCoor, viewSpaceCursorZCoor, 0.0f);
  m_camera->GetWorldMatrix(cameraWorldMatrix);

  pickRayInCameraWorldSpaceDir = XMVector3TransformNormal(pickRayInViewSpaceDir, cameraWorldMatrix);
  cameraPosition = m_camera->GetPosition();
  pickRayInCameraWorldSpacePos = XMLoadFloat3(&cameraPosition);

  int selectedObjectId = NOTHING_SELECTED;
  m_mapEditorViewModel->ClearSelectionInSgoOnMapTable();
  for (auto sgo : *m_visibleSgos)
  {
    BoundingBox* box = sgo->GetModel()->GetBoundingBox();
    XMFLOAT3 minPoint = box->GetMinPoint();
    XMFLOAT3 maxPoint = box->GetMaxPoint();
    XMFLOAT3 rayPosReadable;
    XMFLOAT3 rayDirectReadable;
    float distance;

    sgo->GetWorldMatrix(objectWorldMatrix);
    objectWorldMatrix = XMMatrixInverse(&matInvDeter, objectWorldMatrix);

    pickRayInObjectSpaceDir = XMVector3TransformNormal(pickRayInCameraWorldSpaceDir, objectWorldMatrix);
    pickRayInObjectSpacePos = XMVector3TransformCoord(pickRayInCameraWorldSpacePos, objectWorldMatrix);

    pickRayInObjectSpaceDir = XMVector3Normalize(pickRayInObjectSpaceDir);

    XMStoreFloat3(&rayPosReadable, pickRayInObjectSpacePos);
    XMStoreFloat3(&rayDirectReadable, pickRayInObjectSpaceDir);

    if (RayAABBIntersect(minPoint, maxPoint, rayPosReadable, rayDirectReadable, distance))
    {
      m_needRecalculateRotationAroundPoint = true;
      if (distance < minDistance)
      {
        minDistance = distance;
        selectedObjectId = sgo->uniqueId;
      }
    }
  }

  if (selectedObjectId == NOTHING_SELECTED)
  {
    if (inputState->IsKeyUp(DIK_LCONTROL) && inputState->IsKeyUp(DIK_LALT))
      m_selectedObjectIds->clear();
  }
  else
  {
    if (inputState->IsKeyDown(DIK_LALT)){
      m_selectedObjectIds->erase(selectedObjectId);
    }
    else {
      if (m_selectedObjectIds->count(selectedObjectId) > 0)
        return;

      if (inputState->IsKeyUp(DIK_LCONTROL))
        m_selectedObjectIds->clear();

      m_selectedObjectIds->insert(selectedObjectId);
    }
     
  }
}

bool MapEditorControl::RayAABBIntersect(XMFLOAT3& minPoint, XMFLOAT3& maxPoint, XMFLOAT3& position, XMFLOAT3& direction, float& distance)
{
  //Проверим если луч находится внутри параллелепипеда.
  if (position.x >= minPoint.x
    && position.x <= maxPoint.x
    && position.y >= minPoint.y
    && position.y <= maxPoint.y
    && position.z >= maxPoint.z
    && position.z <= maxPoint.z)
  {
    distance = 0.0f;
    return true;
  }

  float tnear, tfar, txmin, txmax, tymin, tymax, tzmin, tzmax;

  txmin = (minPoint.x - position.x) / direction.x;
  txmax = (maxPoint.x - position.x) / direction.x;

  if (txmin > txmax) std::swap(txmin, txmax);

  tnear = txmin;
  tfar = txmax;

  tymin = (minPoint.y - position.y) / direction.y;
  tymax = (maxPoint.y - position.y) / direction.y;

  if (tymin > tymax) std::swap(tymin, tymax);

  if (tymin > tnear) tnear = tymin;
  if (tymax < tfar) tfar = tymax;

  tzmin = (minPoint.z - position.z) / direction.z;
  tzmax = (maxPoint.z - position.z) / direction.z;

  if (tzmin > tzmax) std::swap(tzmin, tzmax);

  if (tzmin > tnear) tnear = tzmin;
  if (tzmax < tfar) tfar = tzmax;

  distance = tnear;
  return tnear > 0.0f && tfar > tnear;
}

void MapEditorControl::Clone()
{
  if (m_selectedObjectIds->empty())
    return;

  std::vector<int> selectedObjectIdsVector;
  selectedObjectIdsVector.reserve(m_selectedObjectIds->size());
  std::copy(m_selectedObjectIds->begin(), m_selectedObjectIds->end(), std::back_inserter(selectedObjectIdsVector));
  Clone(selectedObjectIdsVector);
}

void MapEditorControl::Delete()
{
  if (m_selectedObjectIds->empty())
    return;

  std::vector<int> selectedIdsVector;
  selectedIdsVector.reserve(m_selectedObjectIds->size());
  std::copy(m_selectedObjectIds->begin(), m_selectedObjectIds->end(), std::back_inserter(selectedIdsVector));
  Delete(selectedIdsVector);
}

void MapEditorControl::AddSgoToMap(StaticGameObjectDbInfo& sgo)
{
  AddOrEditSGOOnMapDialog dialog; //TODO FHolod: посылался родительский виджет в конструктор
  SGOOnMapDbInfo sgoOnMap;
  sgoOnMap.staticGameObjectDbInfo = sgo;
  sgoOnMap.staticGameObjectId = sgo.id;
  sgoOnMap.instanceName = sgo.name;
  if (sgo.countOnMap > 0)
    sgoOnMap.instanceName += QString::number(sgo.countOnMap);

  //TODO FHolod: установить позицию и поворот в зависимости от координат камеры редакторы карты
  dialog.setSGOOnMap(sgoOnMap);

  if (dialog.exec() == QDialog::Accepted) {
    sgoOnMap = dialog.GetSGOOnMap();
    m_mapEditorViewModel->AddSgo(sgoOnMap);
  }
}

void MapEditorControl::AddPointLightToMap(PointLightDbInfo& pointLight)
{
  if (pointLight.staticGameObjectId == 0)
  {
    auto sgo = m_mapEditorViewModel->GetPointLightOnMapService()->GetDefaultPointLightSgo();
    pointLight.staticGameObjectId = sgo.id;
    pointLight.staticGameObjectDbInfo = sgo;
  }

  AddOrEditPointLightOnMapDialog dialog;
  PointLightOnMapDbInfo pointLightOnMap;
  pointLightOnMap.id = 0;
  pointLightOnMap.sgoOnMapId = 0;
  pointLightOnMap.pointLightDbInfo = pointLight;
  pointLightOnMap.pointLightId = pointLight.id;
  pointLightOnMap.sgoOnMapDbInfo.id = 0;
  pointLightOnMap.sgoOnMapDbInfo.staticGameObjectDbInfo = pointLight.staticGameObjectDbInfo;
  pointLightOnMap.sgoOnMapDbInfo.staticGameObjectId = pointLight.staticGameObjectId;
  pointLightOnMap.sgoOnMapDbInfo.instanceName = pointLight.name;
  pointLightOnMap.sgoOnMapDbInfo.gameObjectType = GameObjectType::POINT_LIGHT;
  if (pointLight.countOnMap > 0)
    pointLightOnMap.sgoOnMapDbInfo.instanceName += QString::number(pointLight.countOnMap);

  pointLightOnMap.red = pointLight.red;
  pointLightOnMap.green = pointLight.green;
  pointLightOnMap.blue = pointLight.blue;
  pointLightOnMap.linearAttenuation = pointLight.linearAttenuation;
  pointLightOnMap.quadraticAttenuation = pointLight.quadraticAttenuation;

  dialog.SetPointLightOnMap(pointLightOnMap);

  if (dialog.exec() == QDialog::Accepted) {
    pointLightOnMap = dialog.GetPointLightOnMap();
    m_mapEditorViewModel->AddPointLight(pointLightOnMap);
  }
}

void MapEditorControl::FreezeAll()
{
  m_mapEditorViewModel->FreezeAll();
}

void MapEditorControl::UnfreezeAll()
{
  m_mapEditorViewModel->UnfreezeAll();
}

XMFLOAT3 MapEditorControl::GetCenterOfSelectedObjects(bool isChangeObjectOperation)
{
  if (m_selectedObjectIds->empty())
    RUNTIME_ERROR("There is no selected objects");

  int countOfNoFrozenObjects = 0;
  XMFLOAT3 center = XMFLOAT3(0.0f, 0.0f, 0.0f);
  for (int selectedObjectId : (*m_selectedObjectIds))
  {
    StaticGameObject gameObject = m_staticGameObjectMap->at(selectedObjectId);
    if (isChangeObjectOperation && gameObject.isFrozen)
      continue;

    XMFLOAT3 position = gameObject.GetPosition();
    center.x += position.x;
    center.y += position.y;
    center.z += position.z;
    ++countOfNoFrozenObjects;
  }
  center.x = center.x / countOfNoFrozenObjects;
  center.y = center.y / countOfNoFrozenObjects;
  center.z = center.z / countOfNoFrozenObjects;

  return center;
}

bool MapEditorControl::AllSelectedObjectsAreFrozen()
{
  for (auto& sgo : *m_staticGameObjectMap)
  {
    if (!sgo.second.isFrozen)
      return false;
  }

  return true;
}