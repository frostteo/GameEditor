#pragma once

#include <map>
#include <d3d11.h>
#include <DirectXMath.h>
#include "BoundingBox.h"

using namespace DirectX;

class OctoTree;
class StaticGameObject;

class OctoTreeNode
{
  friend class OctoTree;

  static const int CHILD_NODES_COUNT = 8;

  XMFLOAT3 center;
  float halfLength;

  BoundingBox boundingBox;

  OctoTreeNode* parent = nullptr;
  OctoTreeNode* childNodes[CHILD_NODES_COUNT];
  std::map<int, StaticGameObject*> staticGameObjects;
  int countOfObjectsInBranch = 0;

protected:
  OctoTreeNode();
  bool operator== (const OctoTreeNode& otherNode);
};

