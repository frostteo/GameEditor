#pragma once

#include <vector>
#include "GridObject.h"

class Logger;

class PointLightVolumeGridObject :
  public GridObject
{
private:
  static const XMFLOAT3 LIGHT_COLOR;
  static const int COUNT_OF_POINTS = 8;
  static const int INDEX_COUNT = 24;
public:
  PointLightVolumeGridObject(ID3D11Device* device);
  virtual ~PointLightVolumeGridObject() = default;
};

