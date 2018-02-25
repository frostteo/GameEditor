#pragma once

#include "BoundingBox.h"

class AxisAlignedBBHelper
{
public:
  AxisAlignedBBHelper();
  ~AxisAlignedBBHelper();
  static bool IsCompletelyInside(BoundingBox* aabb, BoundingBox* bb);
  static bool PointContains(BoundingBox* aabb, XMFLOAT3 point);
  static bool TwoAABBIntersects(BoundingBox* firstAabb, BoundingBox* secondAabb);
};

