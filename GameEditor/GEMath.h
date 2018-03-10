#pragma once

#include <d3d11.h>
#include <directxmath.h>

class StaticGameObject;
class Camera;

using namespace DirectX;

class GEMath
{
public:
  const static XMVECTOR UpWorld;
  const static XMVECTOR ForwardWorld;
  const static XMVECTOR RightWorld;
protected:
  static void LookToObjectFromHelper(StaticGameObject* gameObject, float& newWidth, float& newHeight, float& newDepth, XMVECTOR& newObjectCenter);
public:
  GEMath();
  virtual ~GEMath();
  static XMMATRIX GetCameraMatrixRotateAroundTarget(XMVECTOR cameraPosition, XMVECTOR targetPoint, float deltaXRadians, float deltaYRadians, XMVECTOR cameraRight);
  static void LookToObjectFromWorldFront(Camera* camera, StaticGameObject* gameObject);
  static void LookToObjectFromWorldUp(Camera* camera, StaticGameObject* gameObject);
};

