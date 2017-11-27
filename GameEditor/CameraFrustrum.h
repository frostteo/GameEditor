#pragma once

#include "BoundingBox.h"

class Camera;

class CameraFrustrum
{
protected:
  static const int COUNT_OF_PLANES = 6;

  XMVECTOR m_frustrumPlanes[COUNT_OF_PLANES];
public:
  XMFLOAT3 cameraCenter;

  CameraFrustrum();
  void ConstructFrustrum(Camera* camera);
  bool CheckPoint(XMVECTOR point);
  bool IntersectsBB(BoundingBox* boundingBox);
  bool IntersectsAABB(BoundingBox* boundingBox);
  virtual ~CameraFrustrum();
};

