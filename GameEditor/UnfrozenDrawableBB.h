#pragma once

#include "TwoColoredDrawableBB.h"
class BoundingBox;

class UnfrozenDrawableBB :
  public TwoColoredDrawableBB
{
private:
  static const XMFLOAT3 UNFROZEN_COLOR_FIRST;
  static const XMFLOAT3 UNFROZEN_COLOR_SECOND;
public:
  UnfrozenDrawableBB(ID3D11Device* device, const BoundingBox& boundingBox);
  virtual ~UnfrozenDrawableBB() = default;
};

