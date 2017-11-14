#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

class GEMath
{
public:
  const static XMVECTOR UpWorld;
  const static XMVECTOR ForwardWorld;
  const static XMVECTOR RightWorld;
public:
  GEMath();
  virtual ~GEMath();
};

