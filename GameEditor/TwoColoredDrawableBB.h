#pragma once

#include <vector>
#include "GridObject.h"

class BoundingBox;

class TwoColoredDrawableBB : public GridObject
{
public:
  const XMFLOAT3 FIRST_COLOR;
  const XMFLOAT3 SECOND_COLOR;
public:
  TwoColoredDrawableBB(ID3D11Device* device, const BoundingBox& boundingBox, const XMFLOAT3& firstColor, const XMFLOAT3& secondColor);
  virtual ~TwoColoredDrawableBB() = default;
};

