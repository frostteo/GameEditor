#include "MapEditorControl.h"
#include "SGOOnMapTableWidget.h"

MapEditorControl::MapEditorControl(MapEditorPreferences* mapEditorPreferences, SGOOnMapTableWidget* sgoOnMapTableWidget, Camera* camera, std::map<int, StaticGameObject>* staticGameObjectMap)
{
  SetCamera(camera);
  SetSGOMap(staticGameObjectMap);
  SetSGOOnMapTableWidget(sgoOnMapTableWidget);
  SetMapEditorPreferenses(mapEditorPreferences);
}


MapEditorControl::~MapEditorControl()
{
}

void MapEditorControl::SetSGOOnMapTableWidget(SGOOnMapTableWidget* sgoOnMapTableWidget)
{
  m_sgoOnMapTableWidget = sgoOnMapTableWidget; 
  SetSGOOnMapTM(sgoOnMapTableWidget->GetTableModel());
}

void MapEditorControl::ProcessUserInput(InputState* inputState)
{
  if (m_camera)
  {
    if (inputState->IsKeyPressed(DIK_DELETE) && !m_selectedObjectIds->empty())
    {
      for (int selectedId : (*m_selectedObjectIds))
        m_sgoOnMapTableWidget->Delete(selectedId);
      (*m_selectedObjectIds).clear();
    }

    m_timeInSecondsBetweenFrames = inputState->time * 0.001;

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
      LookAtObjectFromHelper::LookToObjectFromWorldFront(m_camera, &gameObject);
    }
      
    if (inputState->IsKeyPressed(DIK_T) && !m_selectedObjectIds->empty())
    {
      auto gameObject = m_staticGameObjectMap->at((*m_selectedObjectIds->begin()));
      LookAtObjectFromHelper::LookToObjectFromWorldUp(m_camera, &gameObject);
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
    m_SGOOnMapTM->EditPosition(selectedId, position.x, position.y, position.z);
  }
}

void MapEditorControl::SaveChangedRotationsInDB()
{
  m_sgoRotated = false;
  m_needRecalculateAcumulativeRotationForSnap = true;
  for (int selectedId : (*m_selectedObjectIds))
  {
    XMFLOAT3 rotation = m_staticGameObjectMap->at(selectedId).GetRotation();
    m_SGOOnMapTM->EditRotation(selectedId, rotation.x, rotation.y, rotation.z);
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

  objectPosition = GetCenterOfSelectedObjects();
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

  newCameraMatrix = GetCameraMatrixRotateAroundTarget(cameraPositionXm, m_rotateAroundPoint, deltaXRadians, deltaYRadians, rightCameraVector);
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

XMMATRIX MapEditorControl::GetCameraMatrixRotateAroundTarget(XMVECTOR cameraPosition, XMVECTOR targetPoint, float deltaXRadians, float deltaYRadians, XMVECTOR cameraRight)
{
  XMVECTOR camFocusVector = cameraPosition - targetPoint;
  if (XMVectorGetX(camFocusVector) < 0.0f)
    deltaYRadians = -deltaYRadians;

  XMMATRIX rotationX = XMMatrixRotationAxis(cameraRight, deltaYRadians);
  XMMATRIX rotaionY = XMMatrixRotationY(deltaXRadians);
  XMMATRIX rotations = XMMatrixMultiply(rotationX, rotaionY);
  camFocusVector = XMVector3TransformNormal(camFocusVector, rotations);
  XMVECTOR newCamPosition = camFocusVector + targetPoint;
  return XMMatrixLookAtLH(newCamPosition, targetPoint, GEMath::UpWorld);
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
  std::map<int, XMFLOAT3> differenceFromCenter;
  XMFLOAT3 centerOfSelectedObjectsGroup;

  float deltaX = inputState->m_mouseState.lX * m_mapEditorPreferences->GetObjectMoveSpeed() * m_timeInSecondsBetweenFrames;
  float deltaY = inputState->m_mouseState.lY * m_mapEditorPreferences->GetObjectMoveSpeed() * m_timeInSecondsBetweenFrames;

  if (deltaX == 0.0f && deltaY == 0.0f)
    return;

  centerOfSelectedObjectsGroup = GetCenterOfSelectedObjects();
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
    XMVECTOR forwardCameraVector;

    rightCameraVector = m_camera->GetRight();
    forwardCameraVector = m_camera->GetForward();

    if (m_mapEditorPreferences->GetSnapToGridState()) {
      m_accumulativePositionForSnap.x += deltaX * XMVectorGetX(rightCameraVector);
      m_accumulativePositionForSnap.z += deltaX * XMVectorGetZ(rightCameraVector);
      m_accumulativePositionForSnap.x += deltaY * XMVectorGetX(forwardCameraVector);
      m_accumulativePositionForSnap.z += deltaY * XMVectorGetZ(forwardCameraVector);

      centerOfSelectedObjectsGroup.x = GetCorrectedWithSnapCoord(m_accumulativePositionForSnap.x, m_mapEditorPreferences->GetGridSnapSize());
      centerOfSelectedObjectsGroup.z = GetCorrectedWithSnapCoord(m_accumulativePositionForSnap.z, m_mapEditorPreferences->GetGridSnapSize());
    }
    else {
      centerOfSelectedObjectsGroup.x += deltaX * XMVectorGetX(rightCameraVector);
      centerOfSelectedObjectsGroup.z += deltaX * XMVectorGetZ(rightCameraVector);
      centerOfSelectedObjectsGroup.x += deltaY * XMVectorGetX(forwardCameraVector);
      centerOfSelectedObjectsGroup.z += deltaY * XMVectorGetZ(forwardCameraVector);
    }
  }

  for (int selectedObjectId : (*m_selectedObjectIds))
  {
    (*m_staticGameObjectMap)[selectedObjectId].SetPosition(centerOfSelectedObjectsGroup.x + differenceFromCenter[selectedObjectId].x, centerOfSelectedObjectsGroup.y + differenceFromCenter[selectedObjectId].y, centerOfSelectedObjectsGroup.z + differenceFromCenter[selectedObjectId].z);
  }
  m_sgoTranslated = true;
}

void MapEditorControl::RotateObjects(InputState* inputState)
{
  XMFLOAT3 centerOfSelectedObjects; 
  XMMATRIX newRotaions;
  float correctedAngleWithSnap;
  float deltaX = inputState->m_mouseState.lX * m_mapEditorPreferences->GetObjectRotationSpeed() * m_timeInSecondsBetweenFrames;
  float deltaY = inputState->m_mouseState.lY * m_mapEditorPreferences->GetObjectRotationSpeed() * m_timeInSecondsBetweenFrames;

  if (deltaX == 0.0f && deltaY == 0.0f)
    return;
  
  centerOfSelectedObjects = GetCenterOfSelectedObjects();

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
    XMMATRIX worldMatrix;
    (*m_staticGameObjectMap)[selectedObjectId].GetWorldMatrix(worldMatrix);
    worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(-centerOfSelectedObjects.x, -centerOfSelectedObjects.y, -centerOfSelectedObjects.z));
    worldMatrix = XMMatrixMultiply(worldMatrix, newRotaions);
    worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(centerOfSelectedObjects.x, centerOfSelectedObjects.y, centerOfSelectedObjects.z));

    (*m_staticGameObjectMap)[selectedObjectId].SetWorldMatrix(worldMatrix);
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
  for (auto& sgo : (*m_staticGameObjectMap))
  {
    BoundingBox* box = sgo.second.GetModel()->GetBoundingBox();
    XMFLOAT3 minPoint = box->GetMinPoint();
    XMFLOAT3 maxPoint = box->GetMaxPoint();
    XMFLOAT3 rayPosReadable;
    XMFLOAT3 rayDirectReadable;
    float distance;

    sgo.second.GetWorldMatrix(objectWorldMatrix);
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
        selectedObjectId = sgo.first;
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

  for (auto selectedId : (*m_selectedObjectIds))
    m_sgoOnMapTableWidget->Clone(selectedId);
}

XMFLOAT3 MapEditorControl::GetCenterOfSelectedObjects()
{
  if (m_selectedObjectIds->empty())
    RUNTIME_ERROR("There is no selected objects")

  XMFLOAT3 center = XMFLOAT3(0.0f, 0.0f, 0.0f);
  for (int selectedObjectId : (*m_selectedObjectIds))
  {
    StaticGameObject gameObject = m_staticGameObjectMap->at(selectedObjectId);
    XMFLOAT3 position = gameObject.GetPosition();
    center.x += position.x;
    center.y += position.y;
    center.z += position.z;
  }
  center.x = center.x / m_selectedObjectIds->size();
  center.y = center.y / m_selectedObjectIds->size();
  center.z = center.z / m_selectedObjectIds->size();

  return center;
}