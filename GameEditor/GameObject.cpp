
#include "GameObject.h"

GameObject::GameObject()
{
  m_positionX = 0;
  m_positionY = 0;
  m_positionZ = 0;

  m_rotationX = 0;
  m_rotationY = 0;
  m_rotationZ = 0;
 
  m_needRebuildTranslationMatrix = true;
  m_needRebuildRotationMatrix = true;
}


GameObject::~GameObject()
{
}

void GameObject::SetPosition(float x, float y, float z)
{
  m_positionX = x;
  m_positionY = y;
  m_positionZ = z;
  m_needRebuildTranslationMatrix = true;
}

void GameObject::SetRotation(float x, float y, float z)
{
  m_rotationX = x;
  m_rotationY = y;
  m_rotationZ = z;
  m_needRebuildRotationMatrix = true;
}

XMFLOAT3 GameObject::GetPosition()
{
  return XMFLOAT3(m_positionX, m_positionY, m_positionZ);
}

XMFLOAT3 GameObject::GetRotation()
{
  return XMFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}

void GameObject::ChangeXRotation(float angle)
{
  m_rotationX += angle;

  if (angle < 0 && m_rotationX < 0)
    m_rotationX += 360;

  if (angle > 0 && m_rotationX > 360)
    m_rotationX -= 360;

  m_needRebuildRotationMatrix = true;
}

void GameObject::ChangeYRotation(float angle)
{
  m_rotationY += angle;

  if (angle < 0 && m_rotationY < 0)
    m_rotationY += 360;

  if (angle > 0 && m_rotationY > 360)
    m_rotationY -= 360;

  m_needRebuildRotationMatrix = true;
}

void GameObject::ChangeZRotation(float angle)
{
  m_rotationZ += angle;

  if (angle < 0 && m_rotationZ < 0)
    m_rotationZ += 360;

  if (angle > 0 && m_rotationZ > 360)
    m_rotationZ -= 360;

  m_needRebuildRotationMatrix = true;
}

void GameObject::GetWorldMatrix(XMMATRIX& worldMatrix)
{
  if (m_needRebuildRotationMatrix || m_needRebuildTranslationMatrix)
  {
    if (m_needRebuildRotationMatrix)
      m_rotationMatrix = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_rotationX), XMConvertToRadians(m_rotationY), XMConvertToRadians(m_rotationZ));

    if (m_needRebuildTranslationMatrix)
      m_translationMatrix = XMMatrixTranslation(m_positionX, m_positionY, m_positionZ);

    m_worldMatrix = XMMatrixMultiply(m_rotationMatrix, m_translationMatrix);
  }

  worldMatrix = m_worldMatrix;
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

XMVECTOR GameObject::GetRight()
{
  XMFLOAT4X4 worldReadableMatrix;

  XMStoreFloat4x4(&worldReadableMatrix, m_worldMatrix);
  XMVECTOR rightVector = XMVectorSet(worldReadableMatrix._11, worldReadableMatrix._12, worldReadableMatrix._13, 1.0f);
  rightVector = XMVector3Normalize(rightVector);
  return rightVector;
}

XMVECTOR GameObject::GetUp()
{
  XMFLOAT4X4 worldReadableMatrix;

  XMStoreFloat4x4(&worldReadableMatrix, m_worldMatrix);
  XMVECTOR upVector = XMVectorSet(worldReadableMatrix._21, worldReadableMatrix._22, worldReadableMatrix._23, 1.0f);
  upVector = XMVector3Normalize(upVector);
  return upVector;
}

XMVECTOR GameObject::GetForward()
{
  XMFLOAT4X4 worldReadableMatrix;

  XMStoreFloat4x4(&worldReadableMatrix, m_worldMatrix);
  XMVECTOR forwardVector = XMVectorSet(worldReadableMatrix._31, worldReadableMatrix._32, worldReadableMatrix._33, 1.0f);
  forwardVector = XMVector3Normalize(forwardVector);
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
