#pragma once

#include <DirectXMath.h>

using namespace DirectX;

class BoundingBox;

class AxisAlignedBBHelper final
{
public:
  AxisAlignedBBHelper() = default;
  ~AxisAlignedBBHelper() = default;
  static bool IsCompletelyInside(const BoundingBox& aabb, const BoundingBox& bb);
  static bool PointContains(const BoundingBox& aabb, XMFLOAT3 point);
  static bool TwoAABBIntersects(const BoundingBox& firstAabb, const BoundingBox& secondAabb);
};

