#include "MapEditorControl.h"

MapEditorControl::MapEditorControl()
{
}


MapEditorControl::~MapEditorControl()
{
}


void MapEditorControl::ProcessUserInput(InputState* inputState)
{
  if (inputState->IsMouseBtnPressed(MouseButtons::LeftMouseBtn))
  {
    PickObject(inputState->mouseXCoor, inputState->mouseYCoor);
  }
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

  (*m_selectedObjectId) = NOTHING_SELECTED;

  m_camera->GetProjectionMatrix(projectionMatrix);
  XMStoreFloat4x4(&projectionMatrixReadable, projectionMatrix);

  float viewSpaceCursorXCoor = (mouseXCoor * 2.0f / m_camera->GetScreenWidth() - 1.0f) / projectionMatrixReadable._11;
  float viewSpaceCursorYCoor = -(mouseYCoor * 2.0f / m_camera->GetScreenHeight() - 1.0f) / projectionMatrixReadable._22;
  float viewSpaceCursorZCoor = 1.0f;

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
