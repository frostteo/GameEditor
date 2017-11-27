#pragma once

#include "BoundingBox.h"

class AxisAlignedBBHelper
{
public:
  AxisAlignedBBHelper();
  ~AxisAlignedBBHelper();
  bool static IsCompletelyInside(BoundingBox* aabb, BoundingBox* bb);
  bool static PointContains(BoundingBox* aabb, XMFLOAT3 point);
};

