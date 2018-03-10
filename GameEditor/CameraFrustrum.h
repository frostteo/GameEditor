#pragma once

#include <directxmath.h>

class Camera;
class BoundingBox;

using namespace DirectX;

class CameraFrustrum final
{
protected:
  static const int COUNT_OF_PLANES = 6;

  XMVECTOR m_frustrumPlanes[COUNT_OF_PLANES];
public:
  CameraFrustrum() = default;
  void ConstructFrustrum(const Camera& camera);
  bool CheckPoint(const XMVECTOR& point) const;
  bool IntersectsBB(const BoundingBox& boundingBox) const;
  bool IntersectsAABB(const BoundingBox& boundingBox) const;
  ~CameraFrustrum() = default;
};

