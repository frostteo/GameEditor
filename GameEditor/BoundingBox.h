#pragma once

#include <vector>
#include <iostream>
#include "Logger.h"
#include "GridObject.h"

/*
   Order of bounding box building: bottom square, then top square by clockwise
*/
class BoundingBox : public GridObject
{
public:
  struct Vertex {
    XMFLOAT3 position;
    XMFLOAT3 color;
  };
private:
  static const int BOUNDING_BOX_SERIALIZE_NAME_LENGTH = 15;
  static const char BOUNDING_BOX_SERIALIZE_NAME[BOUNDING_BOX_SERIALIZE_NAME_LENGTH];
protected:
  std::vector<XMFLOAT3> m_vertices;
  ID3D11Buffer* m_vertexBuffer;
  ID3D11Buffer* m_indexBuffer;
protected:
  void CorrectZeroCoordinates(float& min, float& max);
public:
  static const int COUNT_OF_POINTS = 8;
  static const int INDEX_COUNT = 24;
  /*
  * Serialize with same algorithm as class member Serialize function, deserialize can restore object
  */
  static void SerializeStatic(std::ostream& ostream, float& minX, float& minY, float& minZ, float& maxX, float& maxY, float& maxZ);
public:
  BoundingBox();

  /*
  * Serialize in format: minX, minY, minZ, maxX, maxY, maxZ
  */
  void Serialize(std::ostream& ostream);
  void Deserialize(std::istream& istream);
  void Initialize(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
  void Initialize(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, XMMATRIX worldMatrix);
  virtual ~BoundingBox();
  void InitializeBuffers(ID3D11Device* device);
  void ShutdownBuffers();
  virtual void PrepareToRender(ID3D11DeviceContext* deviceContext) override;
  virtual int GetIndexCount() override { return INDEX_COUNT; }
  XMFLOAT3 GetMinPoint();
  XMFLOAT3 GetMaxPoint();
  XMFLOAT3 GetVertex(int index) { return m_vertices[index]; }
};

