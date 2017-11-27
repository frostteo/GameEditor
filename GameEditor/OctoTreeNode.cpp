#include "OctoTreeNode.h"

OctoTreeNode::OctoTreeNode()
{
  for (size_t i = 0; i < CHILD_NODES_COUNT; i++)
    childNodes[i] = nullptr;
}

bool OctoTreeNode::operator == (const OctoTreeNode& otherNode)
{
  return (this->center.x == otherNode.center.x) && (this->center.y = otherNode.center.y) && (this->center.z == otherNode.center.z) && (this->halfLength == otherNode.halfLength);
}