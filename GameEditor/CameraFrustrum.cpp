#include "CameraFrustrum.h"
#include "Camera.h"
#include "BoundingBox.h"

void CameraFrustrum::ConstructFrustrum(const Camera& camera)
{
  XMMATRIX projectionMatrix;
  XMMATRIX viewMatrix;
  XMMATRIX viewProjMultiply;
  XMFLOAT4X4 viewProjMultiplyReadable;

  camera.GetViewMatrix(viewMatrix);
  camera.GetProjectionMatrix(projectionMatrix);
  viewProjMultiply = XMMatrixMultiply(viewMatrix, projectionMatrix);

  XMStoreFloat4x4(&viewProjMultiplyReadable, viewProjMultiply);

  // Left plane
  m_frustrumPlanes[0] = XMVectorSet(
    viewProjMultiplyReadable._14 + viewProjMultiplyReadable._11,
    viewProjMultiplyReadable._24 + viewProjMultiplyReadable._21, 
    viewProjMultiplyReadable._34 + viewProjMultiplyReadable._31, 
    viewProjMultiplyReadable._44 + viewProjMultiplyReadable._41
    );

  // Right plane
  m_frustrumPlanes[1] = XMVectorSet(
    viewProjMultiplyReadable._14 - viewProjMultiplyReadable._11,
    viewProjMultiplyReadable._24 - viewProjMultiplyReadable._21,
    viewProjMultiplyReadable._34 - viewProjMultiplyReadable._31,
    viewProjMultiplyReadable._44 - viewProjMultiplyReadable._41
    );

  // Top plane
  m_frustrumPlanes[2] = XMVectorSet(
    viewProjMultiplyReadable._14 - viewProjMultiplyReadable._12,
    viewProjMultiplyReadable._24 - viewProjMultiplyReadable._22,
    viewProjMultiplyReadable._34 - viewProjMultiplyReadable._32,
    viewProjMultiplyReadable._44 - viewProjMultiplyReadable._42
    );

  // Bottom plane
  m_frustrumPlanes[3] = XMVectorSet(
    viewProjMultiplyReadable._14 + viewProjMultiplyReadable._12,
    viewProjMultiplyReadable._24 + viewProjMultiplyReadable._22,
    viewProjMultiplyReadable._34 + viewProjMultiplyReadable._32,
    viewProjMultiplyReadable._44 + viewProjMultiplyReadable._42
    );

  // Near plane
  m_frustrumPlanes[4] = XMVectorSet(
    viewProjMultiplyReadable._13,
    viewProjMultiplyReadable._23,
    viewProjMultiplyReadable._33,
    viewProjMultiplyReadable._43
    );

  // Far plane
  m_frustrumPlanes[5] = XMVectorSet(
    viewProjMultiplyReadable._14 - viewProjMultiplyReadable._13,
    viewProjMultiplyReadable._24 - viewProjMultiplyReadable._23,
    viewProjMultiplyReadable._34 - viewProjMultiplyReadable._33,
    viewProjMultiplyReadable._44 - viewProjMultiplyReadable._43
    );

  // Normalize planes
  for (int i = 0; i < COUNT_OF_PLANES; i++)
    m_frustrumPlanes[i] = XMPlaneNormalize(m_frustrumPlanes[i]);
}

bool CameraFrustrum::CheckPoint(const XMVECTOR& point) const
{
  for (int i = 0; i < CameraFrustrum::COUNT_OF_PLANES; ++i)
  {
    if (XMVectorGetX(XMPlaneDotCoord(m_frustrumPlanes[i], point)) < 0.0f)
      return false;
  }

  return true;
}

bool CameraFrustrum::IntersectsBB(const BoundingBox& boundingBox) const
{
  XMFLOAT3 point;
  XMVECTOR pointXm;

  for (int i = 0; i < COUNT_OF_PLANES; ++i)
  {
    point = boundingBox.GetVertex(0);
    pointXm = XMLoadFloat3(&point);
    if (XMVectorGetX(XMPlaneDotCoord(m_frustrumPlanes[i], pointXm)) > 0.0f)
      continue;

    point = boundingBox.GetVertex(1);
    pointXm = XMLoadFloat3(&point);
    if (XMVectorGetX(XMPlaneDotCoord(m_frustrumPlanes[i], pointXm)) > 0.0f)
      continue;

    point = boundingBox.GetVertex(2);
    pointXm = XMLoadFloat3(&point);
    if (XMVectorGetX(XMPlaneDotCoord(m_frustrumPlanes[i], pointXm)) > 0.0f)
      continue;

    point = boundingBox.GetVertex(3);
    pointXm = XMLoadFloat3(&point);
    if (XMVectorGetX(XMPlaneDotCoord(m_frustrumPlanes[i], pointXm)) > 0.0f)
      continue;

    point = boundingBox.GetVertex(4);
    pointXm = XMLoadFloat3(&point);
    if (XMVectorGetX(XMPlaneDotCoord(m_frustrumPlanes[i], pointXm)) > 0.0f)
      continue;

    point = boundingBox.GetVertex(5);
    pointXm = XMLoadFloat3(&point);
    if (XMVectorGetX(XMPlaneDotCoord(m_frustrumPlanes[i], pointXm)) > 0.0f)
      continue;

    point = boundingBox.GetVertex(6);
    pointXm = XMLoadFloat3(&point);
    if (XMVectorGetX(XMPlaneDotCoord(m_frustrumPlanes[i], pointXm)) > 0.0f)
      continue;

    point = boundingBox.GetVertex(7);
    pointXm = XMLoadFloat3(&point);
    if (XMVectorGetX(XMPlaneDotCoord(m_frustrumPlanes[i], pointXm)) > 0.0f)
      continue;

    return false;
  }
  return true;
}

bool CameraFrustrum::IntersectsAABB(const BoundingBox& boundingBox) const
{
  XMFLOAT3 minPoint = boundingBox.GetMinPoint();
  XMFLOAT3 maxPoint = boundingBox.GetMaxPoint();

  for (int i = 0; i < COUNT_OF_PLANES; ++i)
  {
    XMFLOAT4 plane;
    XMStoreFloat4(&plane, m_frustrumPlanes[i]);

    float distance = max(minPoint.x * plane.x, maxPoint.x * plane.x) +
      max(minPoint.y * plane.y, maxPoint.y * plane.y) + 
      max(minPoint.z * plane.z, maxPoint.z * plane.z) + 
      plane.w;
    
    if (distance <= 0)
      return false;
  }

  return true;
}

