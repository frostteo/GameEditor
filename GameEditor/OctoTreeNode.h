#pragma once

#include <map>
#include "StaticGameObject.h"
#include "AxisAlignedBBHelper.h"

class OctoTree;

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

