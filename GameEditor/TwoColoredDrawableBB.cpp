#include "TwoColoredDrawableBB.h"
#include "BoundingBox.h"

TwoColoredDrawableBB::TwoColoredDrawableBB(ID3D11Device* device, const BoundingBox& boundingBox, const XMFLOAT3& firstColor, const XMFLOAT3& secondColor) : FIRST_COLOR(firstColor), SECOND_COLOR(secondColor)
{
  GridVertex vertex;
  std::vector<GridVertex> vertexes;
  vertexes.reserve(boundingBox.GetVertices()->size());

  int i = 0;
  for (auto& positionVertex : *boundingBox.GetVertices())
  {
    vertex.position = positionVertex;

    if (i < 4)
      vertex.color = (i % 2 == 0 ? FIRST_COLOR : SECOND_COLOR);
    else
      vertex.color = (i % 2 == 1 ? FIRST_COLOR : SECOND_COLOR);

    vertexes.push_back(vertex);
    ++i;
  }

  std::vector<unsigned long> indexes;

  //prepare indecex
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

  GridObject::InitializeBuffers(device, vertexes, indexes);
}

