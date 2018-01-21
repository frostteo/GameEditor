#pragma once

#include <vector>
#include "GridObject.h"
#include "Logger.h"

class PointLightVolumeGridObject :
  public GridObject
{
protected:
  struct Vertex {
    XMFLOAT3 position;
    XMFLOAT3 color;
  };
private:
  static const XMFLOAT3 LIGHT_COLOR;
  static const int COUNT_OF_POINTS = 8;
  static const int INDEX_COUNT = 24;
protected:
  std::vector<XMFLOAT3> m_vertexPositions;
  ID3D11Buffer* m_vertexBuffer;
  ID3D11Buffer* m_indexBuffer;
public:
  PointLightVolumeGridObject();
  virtual ~PointLightVolumeGridObject();

  void InitializeBuffers(ID3D11Device* device);
  void ShutdownBuffers();
  virtual void PrepareToRender(ID3D11DeviceContext* deviceContext) override;
  virtual int GetIndexCount() override { return INDEX_COUNT; }
};

