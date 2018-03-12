#include "PointLightVolumeGridObject.h"
#include "Logger.h"

const XMFLOAT3 PointLightVolumeGridObject::LIGHT_COLOR = XMFLOAT3(1.0f, 0.5f, 0.0f);

PointLightVolumeGridObject::PointLightVolumeGridObject(ID3D11Device* device)
{
  float min = -1;
  float max = 1;

  GridVertex bottomNearLeft = { { min, min, min }, LIGHT_COLOR };
  GridVertex bottomFarLeft = { { min, min, max }, LIGHT_COLOR };
  GridVertex bottomFarRight = { { max, min, max }, LIGHT_COLOR };
  GridVertex bottomNearRight = { { max, min, min }, LIGHT_COLOR };
  GridVertex topNearLeft = { { min, max, min }, LIGHT_COLOR };
  GridVertex topFarLeft = { { min, max, max }, LIGHT_COLOR };
  GridVertex topFarRight = { { max, max, max }, LIGHT_COLOR };
  GridVertex topNearRight = { { max, max, min }, LIGHT_COLOR };
  
  std::vector<GridVertex> vertexes;
  vertexes.reserve(COUNT_OF_POINTS);

  vertexes.push_back(bottomNearLeft);
  vertexes.push_back(bottomFarLeft);
  vertexes.push_back(bottomFarRight);
  vertexes.push_back(bottomNearRight);
  vertexes.push_back(topNearLeft);
  vertexes.push_back(topFarLeft);
  vertexes.push_back(topFarRight);
  vertexes.push_back(topNearRight);

  std::vector<unsigned long> indexes;
  indexes.reserve(INDEX_COUNT);

  //prepare indexes
  //bottom
  indexes.push_back(0);
  indexes.push_back(3);
  indexes.push_back(3);
  indexes.push_back(2);
  indexes.push_back(2);
  indexes.push_back(1);
  indexes.push_back(1);
  indexes.push_back(0);

  //top face
  indexes.push_back(4);
  indexes.push_back(5);
  indexes.push_back(5);
  indexes.push_back(6);
  indexes.push_back(6);
  indexes.push_back(7);
  indexes.push_back(7);
  indexes.push_back(4);

  //sides
  indexes.push_back(0);
  indexes.push_back(4);
  indexes.push_back(7);
  indexes.push_back(3);
  indexes.push_back(6);
  indexes.push_back(2);
  indexes.push_back(1);
  indexes.push_back(5);

  InitializeBuffers(device, vertexes, indexes);
}