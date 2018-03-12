#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include "DrawableIndexed.h"

class Logger;

using namespace DirectX;

struct GridVertex {
  XMFLOAT3 position;
  XMFLOAT3 color;
};

class GridObject : public DrawableIndexed<GridVertex>
{
public:
  GridObject() = default;
  virtual ~GridObject() = default;
};

