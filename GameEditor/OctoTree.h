#pragma once

#include <vector>
#include <set>
#include <math.h>
#include "OctoTreeNode.h"


class Logger;
class AxisAlignedBBHelper;
class CameraFrustrum;

class OctoTree
{
protected:
  static const float MIN_HALF_LENGTH;

  std::set<int> n_allGameObjectIds;
  OctoTreeNode* m_root = nullptr;
protected:
  XMFLOAT3 GetNewCenter(int index, XMFLOAT3 oldCenter, float halfLength);

  void DeleteNode(OctoTreeNode* node);
  OctoTreeNode* GetNewNode(std::map<int, StaticGameObject*>* objectsMap, XMFLOAT3 center, float halfLength, OctoTreeNode* parent);
  void DeleteUnusedNodeHelper(OctoTreeNode* node);
  void AddSgoHelper(OctoTreeNode* node, int id, StaticGameObject* sgo);
  void DeleteSgoHelper(OctoTreeNode* node, int id, StaticGameObject* sgo);
  void ObjectChangedPositionHelper(OctoTreeNode* node, int id, StaticGameObject* sgo);
  void MoveObjectToSmallerOcts(OctoTreeNode* node, int id, StaticGameObject* sgo);
  bool CanOctTreeContainObject(StaticGameObject* sgo);
  void GetVisibleSgoHelper(OctoTreeNode* node, const CameraFrustrum& cameraFrustrum, std::vector<StaticGameObject*>* sgosToRender);

  void InitializeAllBBsHelper(OctoTreeNode* node);
public:
  OctoTree();
  void Initialize(const std::map<int, StaticGameObject*>* objectsMap, XMFLOAT3 center, float halfLength);
  void DeleteUnusedNodes();
  void AddSgo(int id, StaticGameObject* sgo);
  void DeleteSgo(int id, StaticGameObject* sgo);
  void ObjectChangedPosition(int id, StaticGameObject* sgo);

  void GetVisibleSgo(const CameraFrustrum& cameraFrustrum, std::vector<StaticGameObject*>* sgosToRender);

  virtual ~OctoTree();

  std::vector<BoundingBox*> AllBBs; // необходимо для отладки, для визуализации октодерева
  void InitializeAllBBs();
};

