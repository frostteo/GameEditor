#include "MapEditorControl.h"

MapEditorControl::MapEditorControl(MapEditorPreferences* mapEditorPreferences, SGOOnMapTM* sgoOnMapTM, Camera* camera, std::map<int, StaticGameObject>* staticGameObjectMap)
{
  SetCamera(camera);
  SetSGOMap(staticGameObjectMap);
  SetSGOOnMapTM(sgoOnMapTM);
  SetMapEditorPreferenses(mapEditorPreferences);
}


MapEditorControl::~MapEditorControl()
{
}


void MapEditorControl::ProcessUserInput(InputState* inputState)
{
  if (m_camera)
  {
    m_timeInSecondsBetweenFrames = inputState->time * 0.001;

    if (inputState->IsMouseBtnPressed(MouseButtons::LeftMouseBtn))
      PickObject(inputState->mouseXCoor, inputState->mouseYCoor);
  
    MoveCamera(inputState);

    if (inputState->IsKeyPressed(DIK_C) && (*m_selectedObjectId) != NOTHING_SELECTED)
    {
      auto gameObject = m_staticGameObjectMap->at((*m_selectedObjectId));
      LookAtObjectFromHelper::LookToObjectFromWorldFront(m_camera, &gameObject);
    }
      
    if (inputState->IsKeyPressed(DIK_T) && (*m_selectedObjectId) != NOTHING_SELECTED)
    {
      auto gameObject = m_staticGameObjectMap->at((*m_selectedObjectId));
      LookAtObjectFromHelper::LookToObjectFromWorldUp(m_camera, &gameObject);
    }

    if (inputState->IsKeyDown(DIK_LSHIFT))
    {
      if ((*m_selectedObjectId) != NOTHING_SELECTED)
      {
        RotateCameraAroundObject(inputState);
      }
      else {
        RotateCamera(inputState);
      }
    }

    if ((*m_selectedObjectId) != NOTHING_SELECTED) 
    {
      if (inputState->IsMouseBtnDown(MouseButtons::LeftMouseBtn))
        MoveObject(inputState);
      
      if (inputState->IsMouseBtnDown(MouseButtons::RightMouseBtn))
        RotateObject(inputState);

      if (inputState->IsMouseBtnReleased(MouseButtons::LeftMouseBtn) && m_sgoTranslated)
      {
        m_sgoTranslated = false;
        m_needRecalculateAcumulativePositionForSnap = true;
        XMFLOAT3 position = m_staticGameObjectMap->at((*m_selectedObjectId)).GetPosition();
        m_SGOOnMapTM->EditPosition((*m_selectedObjectId), position.x, position.y, position.z);
      }

      if (inputState->IsMouseBtnReleased(MouseButtons::RightMouseBtn) && m_sgoRotated)
      {
        m_sgoRotated = false;
        m_needRecalculateAcumulativeRotationForSnap = true;
        XMFLOAT3 rotation = m_staticGameObjectMap->at((*m_selectedObjectId)).GetRotation();
        m_SGOOnMapTM->EditRotation((*m_selectedObjectId), rotation.x, rotation.y, rotation.z);
      }
    }
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

  objectPosition = m_staticGameObjectMap->at((*m_selectedObjectId)).GetPosition();
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

float MapEditorControl::GetCorrectedWithSnapDelta(float delta, float snapSize)
{
  const float MOVE_OBJECT_THRESHOLD = 2.0f;

  float absDelta = abs(delta);
  if (absDelta > MOVE_OBJECT_THRESHOLD && absDelta < snapSize)
    delta = snapSize * GetSign(delta);
  
  return delta;
}

float MapEditorControl::GetCorrectedWithSnapCoord(float coord, float snapSize)
{
  return round(coord / snapSize) * snapSize;
}

void MapEditorControl::MoveObject(InputState* inputState)
{
  XMFLOAT3 selectedObjectPosition = m_staticGameObjectMap->at((*m_selectedObjectId)).GetPosition();
  float deltaX = inputState->m_mouseState.lX * m_mapEditorPreferences->GetObjectMoveSpeed() * m_timeInSecondsBetweenFrames;
  float deltaY = inputState->m_mouseState.lY * m_mapEditorPreferences->GetObjectMoveSpeed() * m_timeInSecondsBetweenFrames;

  if (deltaX == 0.0f && deltaY == 0.0f)
    return;

  if (m_mapEditorPreferences->GetSnapToGridState() && m_needRecalculateAcumulativePositionForSnap)
  {
    /*deltaX = GetCorrectedWithSnapDelta(deltaX, m_mapEditorPreferences->GetGridSnapSize());
    deltaY = GetCorrectedWithSnapDelta(deltaY, m_mapEditorPreferences->GetGridSnapSize());*/
    m_accumulativePositionForSnap = selectedObjectPosition;
    m_needRecalculateAcumulativePositionForSnap = false;
  }

  if (inputState->IsKeyDown(DIK_Z))
  {
    if (m_mapEditorPreferences->GetSnapToGridState()) {
      m_accumulativePositionForSnap.y -= deltaY;
      selectedObjectPosition.y = GetCorrectedWithSnapCoord(m_accumulativePositionForSnap.y, m_mapEditorPreferences->GetGridSnapSize());
    }
    else {
      selectedObjectPosition.y -= deltaY;
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

      selectedObjectPosition.x = GetCorrectedWithSnapCoord(m_accumulativePositionForSnap.x, m_mapEditorPreferences->GetGridSnapSize());
      selectedObjectPosition.z = GetCorrectedWithSnapCoord(m_accumulativePositionForSnap.z, m_mapEditorPreferences->GetGridSnapSize());
    }
    else {
      selectedObjectPosition.x += deltaX * XMVectorGetX(rightCameraVector);
      selectedObjectPosition.z += deltaX * XMVectorGetZ(rightCameraVector);
      selectedObjectPosition.x += deltaY * XMVectorGetX(forwardCameraVector);
      selectedObjectPosition.z += deltaY * XMVectorGetZ(forwardCameraVector);
    }
  }
  (*m_staticGameObjectMap)[(*m_selectedObjectId)].SetPosition(selectedObjectPosition.x, selectedObjectPosition.y, selectedObjectPosition.z);
  m_sgoTranslated = true;
}

void MapEditorControl::RotateObject(InputState* inputState)
{
  XMFLOAT3 rotation = m_staticGameObjectMap->at((*m_selectedObjectId)).GetRotation();
  float deltaX = inputState->m_mouseState.lX * m_mapEditorPreferences->GetObjectRotationSpeed() * m_timeInSecondsBetweenFrames;
  float deltaY = inputState->m_mouseState.lY * m_mapEditorPreferences->GetObjectRotationSpeed() * m_timeInSecondsBetweenFrames;

  if (deltaX == 0.0f && deltaY == 0.0f)
    return;
  
  if (m_mapEditorPreferences->GetSnapToAngleState() && m_needRecalculateAcumulativeRotationForSnap)
  {
    m_accumulativeRotationForSnap = rotation;
    m_needRecalculateAcumulativeRotationForSnap = false;
  }

  m_sgoRotated = true;
  if (inputState->IsKeyDown(DIK_Z))
  {
    if (m_mapEditorPreferences->GetSnapToAngleState())
      m_accumulativeRotationForSnap.z += deltaX;
    else
      rotation.z += deltaX;
  }
  else if (inputState->IsKeyDown(DIK_X))
  {
    if (m_mapEditorPreferences->GetSnapToAngleState())
      m_accumulativeRotationForSnap.x += deltaY;
    else
      rotation.x += deltaY;
  }
  else
  {
    if (m_mapEditorPreferences->GetSnapToAngleState())
      m_accumulativeRotationForSnap.y += deltaX;
    else
      rotation.y += deltaX;
  }

  if (m_mapEditorPreferences->GetSnapToAngleState())
  {
    rotation.x = GetCorrectedWithSnapCoord(m_accumulativeRotationForSnap.x, m_mapEditorPreferences->GetAngleSnap());
    rotation.y = GetCorrectedWithSnapCoord(m_accumulativeRotationForSnap.y, m_mapEditorPreferences->GetAngleSnap());
    rotation.z = GetCorrectedWithSnapCoord(m_accumulativeRotationForSnap.z, m_mapEditorPreferences->GetAngleSnap());
  }
  m_staticGameObjectMap->at((*m_selectedObjectId)).SetRotation(rotation.x, rotation.y, rotation.z);
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

void MapEditorControl::PickObject(int mouseXCoor, int mouseYCoor)
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

  (*m_selectedObjectId) = NOTHING_SELECTED;

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
      if (distance < minDistance)
      {
        minDistance = distance;
        (*m_selectedObjectId) = sgo.first;
        m_needRecalculateRotationAroundPoint = true;
      }
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
