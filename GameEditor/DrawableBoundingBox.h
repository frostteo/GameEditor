#pragma once

#include "BoundingBox.h"
#include "GridObject.h"

class DrawableBoundingBox : public GridObject
{
public:
  struct Vertex {
    XMFLOAT3 position;
    XMFLOAT3 color;
  };
private:
  static const XMFLOAT3 UNFROZEN_COLOR_FIRST;
  static const XMFLOAT3 UNFROZEN_COLOR_SECOND;
  static const XMFLOAT3 FROZEN_COLOR_FIRST;
  static const XMFLOAT3 FROZEN_COLOR_SECOND;
protected:
  std::vector<XMFLOAT3> m_vertices;
  ID3D11Buffer* m_vertexBuffer;
  ID3D11Buffer* m_indexBuffer;
  bool m_isFrozen = false;
public:
  static const int INDEX_COUNT = 24;
public:
  DrawableBoundingBox();
  virtual ~DrawableBoundingBox();

  void Initialize(BoundingBox* boundingBox);
  void InitializeBuffers(ID3D11Device* device, bool isFrozen = false);
  void ShutdownBuffers();
  virtual void PrepareToRender(ID3D11DeviceContext* deviceContext) override;
  virtual int GetIndexCount() override { return INDEX_COUNT; }
};

