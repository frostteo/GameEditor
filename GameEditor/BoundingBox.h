#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <vector>
#include <iostream>

class Logger;

using namespace DirectX;

/*
   Order of bounding box building: bottom square, then top square by clockwise
*/
class BoundingBox
{

private:
  static const int BOUNDING_BOX_SERIALIZE_NAME_LENGTH = 15;
  static const char BOUNDING_BOX_SERIALIZE_NAME[BOUNDING_BOX_SERIALIZE_NAME_LENGTH];
protected:
  std::vector<XMFLOAT3> m_vertices;
protected:
  void CorrectZeroCoordinates(float& min, float& max);
public:
  static const int COUNT_OF_POINTS = 8;
  /*
  * Serialize with same algorithm as class member Serialize function, deserialize can restore object
  */
  static void SerializeStatic(std::ostream& ostream, const float& minX, const float& minY, const float& minZ, const float& maxX, const float& maxY, const float& maxZ);
public:
  BoundingBox() = default;

  /*
  * Serialize in format: minX, minY, minZ, maxX, maxY, maxZ
  */
  void Serialize(std::ostream& ostream) const;
  void Deserialize(std::istream& istream);
  void Initialize(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
  void Initialize(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const XMMATRIX& worldMatrix);
  virtual ~BoundingBox() = default;
 
  const XMFLOAT3 GetMinPoint() const;
  const XMFLOAT3 GetMaxPoint() const;
  const XMFLOAT3 GetVertex(int index) const { return m_vertices[index]; }

  const std::vector<XMFLOAT3>* GetVertices() const { return &m_vertices; }
};

