#include "AxisAlignedBBHelper.h"
#include "BoundingBox.h"

bool AxisAlignedBBHelper::IsCompletelyInside(const BoundingBox& aabb, const BoundingBox& bb)
{
  XMFLOAT3 minPoint = aabb.GetMinPoint();
  XMFLOAT3 maxPoint = aabb.GetMaxPoint();

  for (int i = 0; i < BoundingBox::COUNT_OF_POINTS; ++i)
  {
    XMFLOAT3 vertex = bb.GetVertex(i);
    if (vertex.x > maxPoint.x || vertex.x < minPoint.x ||
      vertex.y > maxPoint.y || vertex.y < minPoint.y ||
      vertex.z > maxPoint.z || vertex.z < minPoint.z)
      return false;
  }

  return true;
}

bool AxisAlignedBBHelper::PointContains(const BoundingBox& aabb, XMFLOAT3 point)
{
  XMFLOAT3 minPoint = aabb.GetMinPoint();
  XMFLOAT3 maxPoint = aabb.GetMaxPoint();

  if (point.x > maxPoint.x || point.x < minPoint.x ||
    point.y > maxPoint.y || point.y < minPoint.y ||
    point.z > maxPoint.z || point.z < minPoint.z)
    return false;

  return true;
}

bool AxisAlignedBBHelper::TwoAABBIntersects(const BoundingBox& firstAabb, const BoundingBox& secondAabb)
{
  XMFLOAT3 firstMinPoint = firstAabb.GetMinPoint();
  XMFLOAT3 firstMaxPoint = firstAabb.GetMaxPoint();
  XMFLOAT3 secondMinPoint = secondAabb.GetMinPoint();
  XMFLOAT3 secondMaxPoint = secondAabb.GetMaxPoint();

  auto test = (firstMinPoint.x <= secondMaxPoint.x && firstMaxPoint.x >= secondMinPoint.x) &&
    (firstMinPoint.y <= secondMaxPoint.y && firstMaxPoint.y >= secondMinPoint.y) &&
    (firstMinPoint.z <= secondMaxPoint.z && firstMaxPoint.z >= secondMinPoint.z);
  return test;
}

bool AxisAlignedBBHelper::AABBIntersectsBB(const BoundingBox& aabb, const BoundingBox& bb)
{
  for (auto& vertex : *bb.GetVertices())
  {
    if (AxisAlignedBBHelper::PointContains(aabb, vertex))
      return true;
  }
  
  return false;
}