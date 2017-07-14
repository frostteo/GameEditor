
#include "GameObject.h"

GameObject::GameObject()
{
  m_positionX = 0;
  m_positionY = 0;
  m_positionZ = 0;

  m_rotationX = 0;
  m_rotationY = 0;
  m_rotationZ = 0;
 
  m_needRebuildRotationMatrix = true;
  m_needRebuildTranslationMatrix = true;
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

void GameObject::MoveVerticalInLocalCord(float distance)
{
  m_positionY += distance;
  m_needRebuildTranslationMatrix = true;
}

void GameObject::MoveForwardBackwardInLocalCord(float distance)
{
  float yRotationInRad = XMConvertToRadians(m_rotationY);
  m_positionX += sinf(yRotationInRad) * distance;
  m_positionZ += cosf(yRotationInRad) * distance;
  m_needRebuildTranslationMatrix = true;
}

void GameObject::MoveLeftRightInLocalCord(float distance)
{
  float yRotationInRad = XMConvertToRadians(m_rotationY);
  m_positionX += cosf(yRotationInRad) * distance;
  m_positionZ -= sinf(yRotationInRad) * distance;
  m_needRebuildTranslationMatrix = true;
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

    m_worldMatrix = XMMatrixMultiply(XMMatrixIdentity(), m_rotationMatrix);
    m_worldMatrix = XMMatrixMultiply(m_worldMatrix, m_translationMatrix);
  }

  worldMatrix = m_worldMatrix;
}


