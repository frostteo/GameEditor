#include "BoundingBox.h"

const char BoundingBox::BOUNDING_BOX_SERIALIZE_NAME[BOUNDING_BOX_SERIALIZE_NAME_LENGTH] = "bounding box: ";

BoundingBox::BoundingBox()
{
  
}

void BoundingBox::CorrectZeroCoordinates(float& min, float& max)
{
  if (abs(min - max) < 5)
  {
    min = -5.0f;
    max = 5.0f;
  }
}

void BoundingBox::Initialize(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
  CorrectZeroCoordinates(minX, maxX);
  CorrectZeroCoordinates(minY, maxY);
  CorrectZeroCoordinates(minZ, maxZ);

  XMFLOAT3 bottomNearLeft = { minX, minY, minZ };
  XMFLOAT3 bottomFarLeft = { minX, minY, maxZ };
  XMFLOAT3 bottomFarRight = { maxX, minY, maxZ };
  XMFLOAT3 bottomNearRight = { maxX, minY, minZ };
  XMFLOAT3 topNearLeft = { minX, maxY, minZ };
  XMFLOAT3 topFarLeft = { minX, maxY, maxZ };
  XMFLOAT3 topFarRight = { maxX, maxY, maxZ };
  XMFLOAT3 topNearRight = { maxX, maxY, minZ };

  m_vertices.clear();
  m_vertices.reserve(COUNT_OF_POINTS);
  m_vertices.push_back(bottomNearLeft);
  m_vertices.push_back(bottomFarLeft);
  m_vertices.push_back(bottomFarRight);
  m_vertices.push_back(bottomNearRight);
  m_vertices.push_back(topNearLeft);
  m_vertices.push_back(topFarLeft);
  m_vertices.push_back(topFarRight);
  m_vertices.push_back(topNearRight);
}

void BoundingBox::Initialize(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, XMMATRIX worldMatrix)
{
  std::vector<XMVECTOR> xmvectors;
  xmvectors.reserve(COUNT_OF_POINTS);

  m_vertices.clear();
  m_vertices.reserve(COUNT_OF_POINTS);

  CorrectZeroCoordinates(minX, maxX);
  CorrectZeroCoordinates(minY, maxY);
  CorrectZeroCoordinates(minZ, maxZ);

  xmvectors.push_back(XMVectorSet(minX, minY, minZ, 0.0f));
  xmvectors.push_back(XMVectorSet(minX, minY, maxZ, 0.0f));
  xmvectors.push_back(XMVectorSet(maxX, minY, maxZ, 0.0f));
  xmvectors.push_back(XMVectorSet(maxX, minY, minZ, 0.0f));
  xmvectors.push_back(XMVectorSet(minX, maxY, minZ, 0.0f));
  xmvectors.push_back(XMVectorSet(minX, maxY, maxZ, 0.0f));
  xmvectors.push_back(XMVectorSet(maxX, maxY, maxZ, 0.0f));
  xmvectors.push_back(XMVectorSet(maxX, maxY, minZ, 0.0f));

  for (size_t i = 0; i < COUNT_OF_POINTS; ++i)
  {
    xmvectors[i] = XMVector3Transform(xmvectors[i], worldMatrix);
    XMFLOAT3 space;
    XMStoreFloat3(&space, xmvectors[i]);
    m_vertices.push_back(space);
  }
}

void BoundingBox::SerializeStatic(std::ostream& ostream, float& minX, float& minY, float& minZ, float& maxX, float& maxY, float& maxZ)
{
  char space = ' ';
  ostream << BOUNDING_BOX_SERIALIZE_NAME;
  ostream << minX << space << minY << space << minZ << space;
  ostream << maxX << space << maxY << space << maxZ << std::endl;
}

void BoundingBox::Serialize(std::ostream& ostream)
{
  SerializeStatic(ostream, m_vertices[0].x, m_vertices[0].y, m_vertices[0].z, m_vertices[6].x, m_vertices[6].y, m_vertices[6].z);
}

void BoundingBox::Deserialize(std::istream& istream)
{
  float minX, minY, minZ, maxX, maxY, maxZ;

  char space[BOUNDING_BOX_SERIALIZE_NAME_LENGTH];
  istream.read(space, BOUNDING_BOX_SERIALIZE_NAME_LENGTH - 1);

  if (strncmp(space, BOUNDING_BOX_SERIALIZE_NAME, BOUNDING_BOX_SERIALIZE_NAME_LENGTH - 1))
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("Cant read bounding box from stream", __FILE__, __LINE__));

  istream >> minX >> minY >> minZ >> maxX >> maxY >> maxZ;
  Initialize(minX, minY, minZ, maxX, maxY, maxZ);
}

BoundingBox::~BoundingBox()
{
}

XMFLOAT3 BoundingBox::GetMinPoint()
{
  if (m_vertices.size() < 8)
    RUNTIME_ERROR("Bounding box was not initialized");

  return m_vertices[0];
}

XMFLOAT3 BoundingBox::GetMaxPoint()
{
  if (m_vertices.size() < 8)
    RUNTIME_ERROR("Bounding box was not initialized");

  return m_vertices[6];
}