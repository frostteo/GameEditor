#include "MapEditorControl.h"

MapEditorControl::MapEditorControl(Camera* camera, std::map<int, StaticGameObject>* staticGameObjectMap)
{
  SetCamera(camera);
  SetSGOMap(staticGameObjectMap);
}


MapEditorControl::~MapEditorControl()
{
}


void MapEditorControl::ProcessUserInput(InputState* inputState)
{
  if (m_camera)
  {
    if (inputState->IsMouseBtnPressed(MouseButtons::LeftMouseBtn))
      PickObject(inputState->mouseXCoor, inputState->mouseYCoor);
  
    MoveCamera(inputState);

    if (inputState->IsKeyPressed(DIK_C) && (*m_selectedObjectId) != NOTHING_SELECTED)
      LookToObjectFromFront();

    if (inputState->IsKeyPressed(DIK_T) && (*m_selectedObjectId) != NOTHING_SELECTED)
       LookToObjectFromUp();

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
    }
  }
}

void MapEditorControl::LookToObjectFromHelper(float& newWidth, float& newHeight, float& newDepth, XMVECTOR& newObjectCenter)
{
  XMMATRIX objectWorldMatrix;
  const int TEST_POINTS_COUNT = 4;
  XMVECTOR testPoints[TEST_POINTS_COUNT];
  float minX, maxX, minY, maxY, minZ, maxZ;
  XMFLOAT3 boundingBoxMinPoint, boundingBoxMaxPoint;
  XMVECTOR minPoint, maxPoint, secondDiagonalFirstPoint, secondDiagonalSecondPoint;

  m_staticGameObjectMap->at((*m_selectedObjectId)).GetWorldMatrix(objectWorldMatrix);
  boundingBoxMinPoint = m_staticGameObjectMap->at((*m_selectedObjectId)).GetModel()->GetBoundingBox()->GetMinPoint();
  boundingBoxMaxPoint = m_staticGameObjectMap->at((*m_selectedObjectId)).GetModel()->GetBoundingBox()->GetMaxPoint();
  minPoint = XMLoadFloat3(&boundingBoxMinPoint);
  maxPoint = XMLoadFloat3(&boundingBoxMaxPoint);
  secondDiagonalFirstPoint = XMVectorSet(boundingBoxMinPoint.x, boundingBoxMaxPoint.y, boundingBoxMinPoint.z, 0.0f);
  secondDiagonalSecondPoint = XMVectorSet(boundingBoxMaxPoint.x, boundingBoxMinPoint.y, boundingBoxMaxPoint.z, 0.0f);

  testPoints[0] = XMVector3Transform(minPoint, objectWorldMatrix);
  testPoints[1] = XMVector3Transform(maxPoint, objectWorldMatrix);
  testPoints[2] = XMVector3Transform(secondDiagonalFirstPoint, objectWorldMatrix);
  testPoints[3] = XMVector3Transform(secondDiagonalSecondPoint, objectWorldMatrix);
  newObjectCenter = XMVector3Transform(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), objectWorldMatrix);

  minX = XMVectorGetX(testPoints[0]);
  maxX = minX;
  minY = XMVectorGetY(testPoints[0]);
  maxY = minY;
  minZ = XMVectorGetZ(testPoints[0]);
  maxZ = minZ;

  for (int i = 1; i < TEST_POINTS_COUNT; ++i)
  {
    float pointX = XMVectorGetX(testPoints[i]);
    float pointY = XMVectorGetY(testPoints[i]);
    float pointZ = XMVectorGetZ(testPoints[i]);

    if (pointX < minX)
      minX = pointX;
    else if (pointX > maxX)
      maxX = pointX;

    if (pointY < minY)
      minY = pointY;
    else if (pointY > maxY)
      maxY = pointY;

    if (pointZ < minZ)
      minZ = pointZ;
    else if (pointZ > maxZ)
      maxZ = pointZ;
  }

  newWidth = maxX - minX;
  newHeight = maxY - minY;
  newDepth = maxZ - minZ;
}

void MapEditorControl::LookToObjectFromFront()
{
  float newWidth, newHeight, newDepth, greatestDimension, FOV, cameraDistanceFromObjectCenter;
  XMVECTOR newObjectCenter, newCameraPosition, helper;
  XMMATRIX newCameraMatrix;

  LookToObjectFromHelper(newWidth, newHeight, newDepth, newObjectCenter);

  greatestDimension = newWidth > newHeight ? newWidth : newHeight;
  FOV = m_camera->GetFieldOfView();
  cameraDistanceFromObjectCenter = (greatestDimension * 0.75) / tan(FOV * 0.5) + abs(newDepth * 0.5);
  newCameraPosition = newObjectCenter;

  newCameraPosition = XMVectorSetZ(newCameraPosition, XMVectorGetZ(newCameraPosition) - cameraDistanceFromObjectCenter);

  newCameraMatrix = XMMatrixLookAtLH(newCameraPosition, newObjectCenter, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
  m_camera->SetWorldMatrix(XMMatrixInverse(&helper, newCameraMatrix));
}

void MapEditorControl::LookToObjectFromUp()
{
  float newWidth, newHeight, newDepth, greatestDimension, FOV, cameraDistanceFromObjectCenter;
  XMVECTOR newObjectCenter, newCameraPosition, helper;
  XMMATRIX newCameraMatrix;

  LookToObjectFromHelper(newWidth, newHeight, newDepth, newObjectCenter);

  greatestDimension = newWidth > newDepth ? newWidth : newDepth;
  FOV = m_camera->GetFieldOfView();
  cameraDistanceFromObjectCenter = (greatestDimension * 0.75) / tan(FOV * 0.5) + abs(newHeight * 0.5);
  newCameraPosition = newObjectCenter;

  newCameraPosition = XMVectorSetY(newCameraPosition, XMVectorGetY(newCameraPosition) + cameraDistanceFromObjectCenter);
  newCameraPosition = XMVectorSetZ(newCameraPosition, XMVectorGetZ(newCameraPosition) - 2);

  newCameraMatrix = XMMatrixLookAtLH(newCameraPosition, newObjectCenter, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
  m_camera->SetWorldMatrix(XMMatrixInverse(&helper, newCameraMatrix));
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

  float deltaX = XMConvertToRadians(inputState->m_mouseState.lX * 0.1);
  float deltaY = XMConvertToRadians(inputState->m_mouseState.lY * 0.1);

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

  newCameraMatrix = GetCameraMatrixRotateAroundTarget(cameraPositionXm, m_rotateAroundPoint, deltaX, deltaY, rightCameraVector);
  m_camera->SetWorldMatrix(XMMatrixInverse(&helper, newCameraMatrix));
}

XMMATRIX MapEditorControl::GetCameraMatrixRotateAroundTarget(XMVECTOR cameraPosition, XMVECTOR targetPoint, float deltaX, float deltaY)
{
  XMVECTOR camPosInTargetCoordSystem = cameraPosition - targetPoint;
  float camPosInTargetCoordSystemLength = XMVectorGetX(XMVector3Length(camPosInTargetCoordSystem));

  float azimutal = atan(XMVectorGetZ(camPosInTargetCoordSystem) / XMVectorGetX(camPosInTargetCoordSystem));
  float colatitude = acos(XMVectorGetY(camPosInTargetCoordSystem) / camPosInTargetCoordSystemLength);

  if (XMVectorGetX(camPosInTargetCoordSystem) < 0.0f)
  {
      azimutal = XM_PI + azimutal;
      deltaY = -deltaY;
  } 
  azimutal += deltaX;
  colatitude += deltaY;
 
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

XMMATRIX MapEditorControl::GetCameraMatrixRotateAroundTarget(XMVECTOR cameraPosition, XMVECTOR targetPoint, float deltaX, float deltaY, XMVECTOR cameraRight)
{
  XMVECTOR camFocusVector = cameraPosition - targetPoint;
  if (XMVectorGetX(camFocusVector) < 0.0f)
     deltaY = -deltaY;

  XMMATRIX rotationX = XMMatrixRotationAxis(cameraRight, deltaY);
  XMMATRIX rotaionY = XMMatrixRotationY(deltaX);
  XMMATRIX rotations = XMMatrixMultiply(rotationX, rotaionY);
  camFocusVector = XMVector3TransformNormal(camFocusVector, rotations);
  XMVECTOR newCamPosition = camFocusVector + targetPoint;
  return XMMatrixLookAtLH(newCamPosition, targetPoint, GEMath::UpWorld);
}

void MapEditorControl::MoveObject(InputState* inputState)
{
  XMFLOAT3 selectedObjectPosition = m_staticGameObjectMap->at((*m_selectedObjectId)).GetPosition();
  float deltaX = inputState->m_mouseState.lX;
  float deltaY = inputState->m_mouseState.lY;

  if (deltaX == 0.0f && deltaY == 0.0f)
    return;

  if (inputState->IsKeyDown(DIK_Z))
  {
    selectedObjectPosition.y -= deltaY;
  }
  else
  {
    XMVECTOR rightCameraVector;
    XMVECTOR forwardCameraVector;

    rightCameraVector = m_camera->GetRight();
    forwardCameraVector = m_camera->GetForward();

    selectedObjectPosition.x += deltaX * XMVectorGetX(rightCameraVector);
    selectedObjectPosition.z += deltaX * XMVectorGetZ(rightCameraVector);

    selectedObjectPosition.x += deltaY * XMVectorGetX(forwardCameraVector);
    selectedObjectPosition.z += deltaY * XMVectorGetZ(forwardCameraVector);
  }
  (*m_staticGameObjectMap)[(*m_selectedObjectId)].SetPosition(selectedObjectPosition.x, selectedObjectPosition.y, selectedObjectPosition.z);
}

void MapEditorControl::RotateObject(InputState* inputState)
{
  float deltaX = inputState->m_mouseState.lX;
  float deltaY = inputState->m_mouseState.lY;
  if (inputState->IsKeyDown(DIK_Z))
  {
    if (deltaX)
      m_staticGameObjectMap->at((*m_selectedObjectId)).ChangeZRotation(deltaX);
  }
  else if (inputState->IsKeyDown(DIK_X))
  {
    if (deltaY)
      m_staticGameObjectMap->at((*m_selectedObjectId)).ChangeXRotation(deltaY);
  }
  else
  {
    if (deltaX)
      m_staticGameObjectMap->at((*m_selectedObjectId)).ChangeYRotation(deltaX);
  }
}

void MapEditorControl::MoveCamera(InputState* inputState)
{
  int deltaZ = inputState->m_mouseState.lZ;

  if (deltaZ)
    m_camera->MoveForward(inputState->m_mouseState.lZ);

  if (inputState->IsKeyDown(DIK_SPACE) || inputState->IsMouseBtnDown(MouseButtons::WheelMouseBtn))
  {
    int deltaX = inputState->m_mouseState.lX;
    int deltaY = inputState->m_mouseState.lY;

    if (deltaX)
      m_camera->MoveRight(deltaX);

    if (deltaY)
      m_camera->MoveUp(deltaY);
  }
}

void MapEditorControl::RotateCamera(InputState* inputState)
{
  float deltaX = inputState->m_mouseState.lX;
  float deltaY = inputState->m_mouseState.lY;

  if (deltaX == 0.0f && deltaY == 0.0f)
    return;

  m_camera->ChangeYRotation(deltaX * CAMERA_ROTATION_COEF);
  m_camera->ChangeXRotation(deltaY * CAMERA_ROTATION_COEF);
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
