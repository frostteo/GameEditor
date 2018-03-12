#pragma once

#include "TwoColoredDrawableBB.h"
class BoundingBox;

class FrozenDrawableBB :
  public TwoColoredDrawableBB
{
private:
  static const XMFLOAT3 FROZEN_COLOR_FIRST;
  static const XMFLOAT3 FROZEN_COLOR_SECOND;
public:
  FrozenDrawableBB(ID3D11Device* device, const BoundingBox& boundingBox);
  virtual ~FrozenDrawableBB() = default;
};

