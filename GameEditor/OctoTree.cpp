#include "OctoTree.h"
#include "Logger.h"
#include "AxisAlignedBBHelper.h"
#include "Camera.h"
#include "CameraFrustrum.h"

const float OctoTree::MIN_HALF_LENGTH = 64.0f;

OctoTree::OctoTree()
{
 
}

void OctoTree::Initialize(const std::map<int, StaticGameObject*>* objectsMap, XMFLOAT3 center, float halfLength)
{
  for (auto& keyObjectPair : *objectsMap)
  {
    n_allGameObjectIds.insert(keyObjectPair.first);
  }

  std::map<int, StaticGameObject*> objectsMapCopy(*objectsMap);

  m_root = GetNewNode(&objectsMapCopy, center, halfLength, nullptr);

  if (objectsMapCopy.size() > 0)
    RUNTIME_ERROR("object is outside oct tree, in future there will be oct tree cells and object must be moved to correct cell!");
}

OctoTree::~OctoTree()
{
  DeleteNode(m_root);
}

void OctoTree::DeleteNode(OctoTreeNode* node)
{
  for (size_t i = 0; i < OctoTreeNode::CHILD_NODES_COUNT; i++){
    if (node->childNodes[i])
      DeleteNode(node->childNodes[i]);
  }
   
  delete node;
}

XMFLOAT3 OctoTree::GetNewCenter(int index, XMFLOAT3 oldCenter, float halfLength)
{
  XMFLOAT3 newCenter;

  if (index == 0)
  {
    newCenter.x = oldCenter.x - halfLength;
    newCenter.y = oldCenter.y - halfLength;
    newCenter.z = oldCenter.z - halfLength;
  }
  else if (index == 1)
  {
    newCenter.x = oldCenter.x + halfLength;
    newCenter.y = oldCenter.y - halfLength;
    newCenter.z = oldCenter.z - halfLength;
  }
  else if (index == 2)
  {
    newCenter.x = oldCenter.x - halfLength;
    newCenter.y = oldCenter.y + halfLength;
    newCenter.z = oldCenter.z - halfLength;
  }
  else if (index == 3)
  {
    newCenter.x = oldCenter.x + halfLength;
    newCenter.y = oldCenter.y + halfLength;
    newCenter.z = oldCenter.z - halfLength;
  }
  else if (index == 4)
  {
    newCenter.x = oldCenter.x - halfLength;
    newCenter.y = oldCenter.y - halfLength;
    newCenter.z = oldCenter.z + halfLength;
  }
  else if (index == 5)
  {
    newCenter.x = oldCenter.x + halfLength;
    newCenter.y = oldCenter.y - halfLength;
    newCenter.z = oldCenter.z + halfLength;
  }
  else if (index == 6)
  {
    newCenter.x = oldCenter.x - halfLength;
    newCenter.y = oldCenter.y + halfLength;
    newCenter.z = oldCenter.z + halfLength;
  }
  else if (index == 7)
  {
    newCenter.x = oldCenter.x + halfLength;
    newCenter.y = oldCenter.y + halfLength;
    newCenter.z = oldCenter.z + halfLength;
  }

  return newCenter;
}

OctoTreeNode* OctoTree::GetNewNode(std::map<int, StaticGameObject*>* objectsMap, XMFLOAT3 center, float halfLength, OctoTreeNode* parent)
{
  std::vector<int> idsToErase;

  OctoTreeNode* newNode = new OctoTreeNode();
  newNode->parent = parent;
  newNode->center = center;
  newNode->halfLength = halfLength;
  newNode->boundingBox.Initialize(center.x - halfLength, center.y - halfLength, center.z - halfLength, center.x + halfLength, center.y + halfLength, center.z + halfLength);

  for (auto& sgo : (*objectsMap))
  {
    if (AxisAlignedBBHelper::IsCompletelyInside(newNode->boundingBox, *sgo.second->GetBBInWorldCoords())){
      newNode->staticGameObjects[sgo.first] = sgo.second;
      idsToErase.push_back(sgo.first);
    }
  }

  newNode->countOfObjectsInBranch = newNode->staticGameObjects.size();

  for (auto id : idsToErase)
    objectsMap->erase(id);

  float childsHalfLength = newNode->halfLength / 2;

  if (newNode->staticGameObjects.size() > 0 && childsHalfLength > MIN_HALF_LENGTH)
  {
    for (int i = 0; i < OctoTreeNode::CHILD_NODES_COUNT; ++i)
    {
      if (newNode->staticGameObjects.size() > 0)
      {
        newNode->childNodes[i] = GetNewNode(&(newNode->staticGameObjects),
          GetNewCenter(i, newNode->center, childsHalfLength),
          childsHalfLength,
          newNode);
      }
    }
  }

  return newNode;
}

void OctoTree::DeleteUnusedNodes()
{
  if (!m_root){
    RUNTIME_ERROR("It is impossible to delete unused nodes from oct tree, because oct tree has not been initialized yet");
  }

  DeleteUnusedNodeHelper(m_root);
}

void OctoTree::DeleteUnusedNodeHelper(OctoTreeNode* node)
{
  for (size_t i = 0; i < OctoTreeNode::CHILD_NODES_COUNT; i++){
    if (node->childNodes[i])
      DeleteUnusedNodeHelper(node->childNodes[i]);
  }
  
  if (node->countOfObjectsInBranch == 0)
  {
    OctoTreeNode* parent = node->parent;
    for (int i = 0; i < OctoTreeNode::CHILD_NODES_COUNT; ++i)
    {
      if (parent->childNodes[i] && parent->childNodes[i] == node) {
        parent->childNodes[i] = nullptr;
        break;
      }
    }

    DeleteNode(node);
  }
}

void OctoTree::InitializeAllBBs()
{
  AllBBs.clear();
  InitializeAllBBsHelper(m_root);
}

void OctoTree::InitializeAllBBsHelper(OctoTreeNode* node)
{
  for (size_t i = 0; i < OctoTreeNode::CHILD_NODES_COUNT; i++) {
    if (node->childNodes[i])
      InitializeAllBBsHelper(node->childNodes[i]);
  }

  AllBBs.push_back(&node->boundingBox);
}

void OctoTree::AddSgo(int id, StaticGameObject* sgo)
{
  if (!m_root){
    RUNTIME_ERROR("It is impossible to add object to oct tree, because oct tree has not been initialized yet");
  }

  if (!CanOctTreeContainObject(sgo))
    RUNTIME_ERROR("object is outside oct tree, in future there will be oct tree cells and object must be moved to correct cell!");

  if (n_allGameObjectIds.count(id) > 0) {
    std::stringstream ss;
    ss << "There is the game object with id = " << id << " in the oct tree already!";
    std::string errorMsg = ss.str();
    RUNTIME_ERROR(errorMsg);
  }
  
  n_allGameObjectIds.insert(id);

  AddSgoHelper(m_root, id, sgo);
}

void OctoTree::AddSgoHelper(OctoTreeNode* node, int id, StaticGameObject* sgo)
{
  bool isCompletyInsideInChilds = false;

  node->countOfObjectsInBranch += 1;

  for (int i = 0; i < OctoTreeNode::CHILD_NODES_COUNT; ++i)
  {
    if (node->childNodes[i]) {
      if (AxisAlignedBBHelper::IsCompletelyInside(node->childNodes[i]->boundingBox, *sgo->GetBBInWorldCoords()))
      {
        AddSgoHelper(node->childNodes[i], id, sgo);
        isCompletyInsideInChilds = true;
      }
    }
    else
    {
      std::map<int, StaticGameObject*> sgoMap;
      sgoMap[id] = sgo;
      float childsHalfLength = node->halfLength / 2;

      if (childsHalfLength > MIN_HALF_LENGTH) {
        node->childNodes[i] = GetNewNode(&sgoMap, GetNewCenter(i, node->center, childsHalfLength), childsHalfLength, node);
        if (node->childNodes[i]->countOfObjectsInBranch > 0)
          isCompletyInsideInChilds = true;
      }
    }
  }

  if (!isCompletyInsideInChilds)
    node->staticGameObjects[id] = sgo;
}

void OctoTree::DeleteSgo(int id, StaticGameObject* sgo)
{
  if (!m_root){
    RUNTIME_ERROR("It is impossible to delete object from oct tree, because oct tree has not been initialized yet");
  }

  if (n_allGameObjectIds.count(id) == 0) {
    std::stringstream ss;
    ss << "There is no game objects with id = " << id << " in the oct tree!";
    std::string errorMsg = ss.str();
    RUNTIME_ERROR(errorMsg);
  }
  n_allGameObjectIds.erase(id);

  DeleteSgoHelper(m_root, id, sgo);
}

void OctoTree::DeleteSgoHelper(OctoTreeNode* node, int id, StaticGameObject* sgo)
{
  node->countOfObjectsInBranch -= 1;

  if (node->staticGameObjects.count(id) > 0)
  {
    node->staticGameObjects.erase(id);
    return;
  }

  for (size_t i = 0; i < OctoTreeNode::CHILD_NODES_COUNT; i++)
  {
    XMFLOAT3 centerOfObject = sgo->GetPosition();

    if (node->childNodes[i] && AxisAlignedBBHelper::PointContains(node->childNodes[i]->boundingBox, centerOfObject))
    {
      DeleteSgoHelper(node->childNodes[i], id, sgo);
      break;
    }
  }
}

void OctoTree::ObjectChangedPosition(int id, StaticGameObject* sgo)
{
  if (!m_root)
    RUNTIME_ERROR("It is impossible to change object position in oct tree, because oct tree has not been initialized yet");

  if (!CanOctTreeContainObject(sgo))
    RUNTIME_ERROR("object is outside oct tree, in future there will be oct tree cells and object must be moved to correct cell!");

  if (n_allGameObjectIds.count(id) == 0) {
    std::stringstream ss;
    ss << "There is no game objects with id = " << id << " in the oct tree!";
    std::string errorMsg = ss.str();
    RUNTIME_ERROR(errorMsg);
  }

  ObjectChangedPositionHelper(m_root, id, sgo);
}

void OctoTree::MoveObjectToSmallerOcts(OctoTreeNode* node, int id, StaticGameObject* sgo)
{
  if (AxisAlignedBBHelper::IsCompletelyInside(node->boundingBox, *sgo->GetBBInWorldCoords()))
  {
    node->staticGameObjects[id] = sgo;
    node->countOfObjectsInBranch += 1;
    node->parent->staticGameObjects.erase(id);

    float childsHalfLength = node->halfLength / 2;

    if (childsHalfLength > MIN_HALF_LENGTH)
    {

      for (int i = 0; i < OctoTreeNode::CHILD_NODES_COUNT; ++i)
      {
        if (node->childNodes[i]) {
          MoveObjectToSmallerOcts(node->childNodes[i], id, sgo);
        }
        else {
          node->childNodes[i] = GetNewNode(&(node->staticGameObjects),
            GetNewCenter(i, node->center, childsHalfLength),
            childsHalfLength,
            node);
        }
      }

    }
  }
}

void OctoTree::ObjectChangedPositionHelper(OctoTreeNode* node, int id, StaticGameObject* sgo)
{
  if (node->staticGameObjects.count(id) > 0)
  {
    if (AxisAlignedBBHelper::IsCompletelyInside(node->boundingBox, *sgo->GetBBInWorldCoords())) // объект находится в данном узле
    {
      float childsHalfLength = node->halfLength / 2;

      if (childsHalfLength > MIN_HALF_LENGTH) // возможно после изменения позиции объект можно направить в дочерние узлы
      {
        for (int i = 0; i < OctoTreeNode::CHILD_NODES_COUNT; ++i)
        {
          if (node->childNodes[i]) {
            MoveObjectToSmallerOcts(node->childNodes[i], id, sgo);
          }
          else // если дочерних узлов нет, то создать их если мы находимся в неминимальном узле дерева
          {
            node->childNodes[i] = GetNewNode(&(node->staticGameObjects),
              GetNewCenter(i, node->center, childsHalfLength),
              childsHalfLength,
              node);
          }
        }
      }
      return;
    }
    else { //объект после изменения позиции вышел за пределы узла
      node->staticGameObjects.erase(id);
      n_allGameObjectIds.erase(id);

      node->countOfObjectsInBranch -= 1;
      OctoTreeNode* parent = node->parent;
      while (parent)
      {
        parent->countOfObjectsInBranch -= 1;
        parent = parent->parent;
      }
      AddSgo(id, sgo);
    }
  }
  else { // объект не находится в данном узле, ищем его в потомках
    for (size_t i = 0; i < OctoTreeNode::CHILD_NODES_COUNT; i++)
    {
      if (node->childNodes[i])
        ObjectChangedPositionHelper(node->childNodes[i], id, sgo);
    }
  }
  
}

bool OctoTree::CanOctTreeContainObject(StaticGameObject* sgo)
{
  if (AxisAlignedBBHelper::IsCompletelyInside(m_root->boundingBox, *sgo->GetBBInWorldCoords()))
    return true;

  return false;
}

void OctoTree::GetVisibleSgo(const Camera& camera, std::vector<StaticGameObject*>* sgosToRender)
{
  if (!m_root)
    RUNTIME_ERROR("It is impossible to get visible sgos, because oct tree has not been initialized yet");

  GetVisibleSgoHelper(m_root, camera, sgosToRender);
}

void OctoTree::GetVisibleSgoHelper(OctoTreeNode* node, const Camera& camera, std::vector<StaticGameObject*>* sgosToRender)
{
  if (camera.IsCameraFrustrumIntersectsAABB(node->boundingBox))
  {
    for (auto& sgo : node->staticGameObjects)
    {
      XMFLOAT3 rotation = sgo.second->GetRotation();
      bool isAABB = ((int) round(rotation.x) % 90 == 0) && ((int) round(rotation.y) % 90 == 0) && ((int) round(rotation.z) % 90 == 0);

      if (isAABB)
      {
        if (camera.IsCameraFrustrumIntersectsAABB(*sgo.second->GetBBInWorldCoords()))
          sgosToRender->push_back(sgo.second);
      }
      else if (camera.IsCameraFrustrumIntersectsBB(*sgo.second->GetBBInWorldCoords()))
      {
        sgosToRender->push_back(sgo.second);
      }
    }

    for (int i = 0; i < OctoTreeNode::CHILD_NODES_COUNT; ++i)
    {
      if (node->childNodes[i] && node->childNodes[i]->countOfObjectsInBranch > 0)
        GetVisibleSgoHelper(node->childNodes[i], camera, sgosToRender);
    }
  }
}