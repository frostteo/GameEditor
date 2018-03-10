
#include "GameObject.h"
#include "Logger.h"

void GameObject::SetPosition(float x, float y, float z)
{
  m_positionX = x;
  m_positionY = y;
  m_positionZ = z;
  m_needRebuildTranslationMatrix = true;
}

void GameObject::SetRotation(float x, float y, float z)
{
  m_rotationX = fmod(x, 360.0f);
  m_rotationY = fmod(y, 360.0f);
  m_rotationZ = fmod(z, 360.0f);
  m_needRebuildRotationMatrix = true;
}

void GameObject::SetScale(float scale)
{ 
  m_scale = scale;
  m_needRebuildScaleMatrix = true; 
}

const XMFLOAT3 GameObject::GetPosition() const
{
  return XMFLOAT3(m_positionX, m_positionY, m_positionZ);
}

const XMFLOAT3 GameObject::GetRotation() const
{
  return XMFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}

void GameObject::ChangeXRotation(float angle)
{
  m_rotationX += angle;
  m_rotationX = fmod(m_rotationX, 360.0f);
  m_needRebuildRotationMatrix = true;
}

void GameObject::ChangeYRotation(float angle)
{
  m_rotationY += angle;
  m_rotationY = fmod(m_rotationY, 360.0f);
  m_needRebuildRotationMatrix = true;
}

void GameObject::ChangeZRotation(float angle)
{
  m_rotationZ += angle;
  m_rotationZ = fmod(m_rotationZ, 360.0f);
  m_needRebuildRotationMatrix = true;
}

void GameObject::RebuildWorldMatrix() const
{
  m_needRebuildBBInWorldCoords = true;

  if (m_needRebuildScaleMatrix) {
    m_scaleMatrix = XMMatrixScaling(m_scale, m_scale, m_scale);
    m_needRebuildScaleMatrix = false;
  }

  if (m_needRebuildRotationMatrix) {
    m_rotationMatrix = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_rotationX), XMConvertToRadians(m_rotationY), XMConvertToRadians(m_rotationZ));
    m_needRebuildRotationMatrix = false;
  }

  if (m_needRebuildTranslationMatrix) {
    m_translationMatrix = XMMatrixTranslation(m_positionX, m_positionY, m_positionZ);
    m_needRebuildTranslationMatrix = false;
  }

  if (m_scale != 1.0f)
  {
    m_worldMatrix = m_scaleMatrix * m_rotationMatrix * m_translationMatrix;
  }
  else
  {
    m_worldMatrix = m_rotationMatrix * m_translationMatrix;
  }
}

void GameObject::GetWorldMatrix(XMMATRIX& worldMatrix) const
{
  if (NeedRebuildWorldMatrix())
  {
    RebuildWorldMatrix();
  }

  if (m_parent)
  {
    XMMATRIX parentMatrix;
    GetParentMatrix(parentMatrix);
    worldMatrix = m_worldMatrix * parentMatrix;
  }
  else
  {
    worldMatrix = m_worldMatrix;
  }
}

const XMFLOAT3 GameObject::GetWorldPosition() const
{
  if (NeedRebuildWorldMatrix())
  {
    RebuildWorldMatrix();
  }
  
  if (m_parent)
  {
    XMMATRIX parentMatrix, worldParentMultiply;
    XMFLOAT4X4 readableWorldMatrix;

    GetParentMatrix(parentMatrix);
    worldParentMultiply = m_worldMatrix * parentMatrix;

    XMStoreFloat4x4(&readableWorldMatrix, worldParentMultiply);
    m_worldPosition = XMFLOAT3(readableWorldMatrix._41, readableWorldMatrix._42, readableWorldMatrix._43);
  }
  else
  {
    m_worldPosition = XMFLOAT3(m_positionX, m_positionY, m_positionZ);
  }

  return m_worldPosition;
}

void GameObject::SetWorldMatrix(XMMATRIX worldMatrix)
{
  m_worldMatrix = worldMatrix;
  m_needRebuildRotationMatrix = false;
  m_needRebuildTranslationMatrix = false;

  XMFLOAT4X4 worldReadableMatrix;

  XMStoreFloat4x4(&worldReadableMatrix, m_worldMatrix);

  m_positionX = worldReadableMatrix._41;
  m_positionY = worldReadableMatrix._42;
  m_positionZ = worldReadableMatrix._43;
  
  m_rotationX = asin(-worldReadableMatrix._32);
  const float THRESHOLD = 0.001f; 

  float test = cos(m_rotationX);

  if (test > THRESHOLD)
  {
    m_rotationZ = atan2(worldReadableMatrix._12, worldReadableMatrix._22);
    m_rotationY = atan2(worldReadableMatrix._31, worldReadableMatrix._33);
  }
  else
  {
    m_rotationZ = atan2(-worldReadableMatrix._21, worldReadableMatrix._11);
    m_rotationY = 0.0f;
  }

  m_rotationX = XMConvertToDegrees(m_rotationX);
  m_rotationY = XMConvertToDegrees(m_rotationY);
  m_rotationZ = XMConvertToDegrees(m_rotationZ);
  m_needRebuildTranslationMatrix = true;
  m_needRebuildRotationMatrix = true;
}

const XMVECTOR GameObject::GetRight() const
{
  XMFLOAT4X4 worldReadableMatrix;

  XMStoreFloat4x4(&worldReadableMatrix, m_worldMatrix);
  XMVECTOR rightVector = XMVectorSet(worldReadableMatrix._11, worldReadableMatrix._12, worldReadableMatrix._13, 1.0f);
  rightVector = XMVector3Normalize(rightVector);

  if (m_parent)
  {
    XMMATRIX parentMatrix;
    GetParentMatrix(parentMatrix);

    rightVector = XMVector3TransformCoord(rightVector, parentMatrix);
  }

  return rightVector;
}

const XMVECTOR GameObject::GetUp() const
{
  XMFLOAT4X4 worldReadableMatrix;

  XMStoreFloat4x4(&worldReadableMatrix, m_worldMatrix);
  XMVECTOR upVector = XMVectorSet(worldReadableMatrix._21, worldReadableMatrix._22, worldReadableMatrix._23, 1.0f);
  upVector = XMVector3Normalize(upVector);

  if (m_parent)
  {
    XMMATRIX parentMatrix;
    GetParentMatrix(parentMatrix);

    upVector = XMVector3TransformCoord(upVector, parentMatrix);
  }

  return upVector;
}

const XMVECTOR GameObject::GetForward() const
{
  XMFLOAT4X4 worldReadableMatrix;

  XMStoreFloat4x4(&worldReadableMatrix, m_worldMatrix);
  XMVECTOR forwardVector = XMVectorSet(worldReadableMatrix._31, worldReadableMatrix._32, worldReadableMatrix._33, 1.0f);
  forwardVector = XMVector3Normalize(forwardVector);

  if (m_parent)
  {
    XMMATRIX parentMatrix;
    GetParentMatrix(parentMatrix);

    forwardVector = XMVector3TransformCoord(forwardVector, parentMatrix);
  }

  return forwardVector;
}

void GameObject::MoveRight(float distance)
{
  XMVECTOR rightVector = GetRight();

  m_positionX += XMVectorGetX(rightVector) * distance;
  m_positionY += XMVectorGetY(rightVector) * distance;
  m_positionZ += XMVectorGetZ(rightVector) * distance;
  m_needRebuildTranslationMatrix = true;
}

void GameObject::MoveUp(float distance)
{
  XMVECTOR upVector = GetUp();

  m_positionX += XMVectorGetX(upVector) * distance;
  m_positionY += XMVectorGetY(upVector) * distance;
  m_positionZ += XMVectorGetZ(upVector) * distance;
  m_needRebuildTranslationMatrix = true;
}

void GameObject::MoveForward(float distance)
{
  XMVECTOR forwardVector = GetForward();

  m_positionX += XMVectorGetX(forwardVector) * distance;
  m_positionY += XMVectorGetY(forwardVector) * distance;
  m_positionZ += XMVectorGetZ(forwardVector) * distance;
  m_needRebuildTranslationMatrix = true;
}

void GameObject::GetParentMatrix(XMMATRIX& parentMatrix) const
{
  if (!m_parent)
  {
    parentMatrix = XMMatrixIdentity();
  }
  else
  {
    m_parent->GetWorldMatrix(parentMatrix);
  }
}

const BoundingBox* GameObject::GetBBInWorldCoords() const
{
  if (this->NeedRebuildWorldMatrix() || m_needRebuildBBInWorldCoords)
  {
    RebuildBBInWorldCoord();
    m_needRebuildBBInWorldCoords = false;
  }

  return &m_bbInWorldCoord;
}