#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>
#include "BoundingBox.h"

class Logger;

using namespace DirectX;

class GameObject
{
protected:
  mutable XMMATRIX m_scaleMatrix;
  mutable XMMATRIX m_translationMatrix;
  mutable XMMATRIX m_rotationMatrix;
  mutable XMMATRIX m_worldMatrix;
  mutable bool m_needRebuildTranslationMatrix = true;
  mutable bool m_needRebuildRotationMatrix = true;
  mutable bool m_needRebuildScaleMatrix = true;
  float m_positionX = 0.0f, m_positionY = 0.0f, m_positionZ = 0.0f;
  float m_rotationX = 0.0f, m_rotationY= 0.0f, m_rotationZ = 0.0f;
  float m_scale = 1.0f;
  GameObject* m_parent = nullptr;
  mutable XMFLOAT3 m_worldPosition;

  mutable bool m_needRebuildBBInWorldCoords;
  mutable BoundingBox m_bbInWorldCoord;
protected:
  virtual void RebuildWorldMatrix() const;
  virtual void RebuildBBInWorldCoord() const = 0;
public:
  GameObject() = default;
  virtual ~GameObject() = default;

  void virtual SetPosition(float x, float y, float z);
  const XMFLOAT3 GetPosition() const;

  void SetRotation(float x, float y, float z);
  const XMFLOAT3 GetRotation() const;

  void ChangeXRotation(float angle);
  void ChangeYRotation(float angle);
  void ChangeZRotation(float angle);

  void SetScale(float scale);
  float GetScale() const { return m_scale; }

  void virtual GetWorldMatrix(XMMATRIX& worldMatrix) const;
  void SetWorldMatrix(XMMATRIX worldMatrix);

  const XMVECTOR GetRight() const;
  const XMVECTOR GetUp() const;
  const XMVECTOR GetForward() const;

  void MoveRight(float distance);
  void MoveUp(float distance);
  void MoveForward(float distance);

  inline bool NeedRebuildWorldMatrix() const { return m_needRebuildTranslationMatrix || m_needRebuildRotationMatrix || m_needRebuildScaleMatrix; }

  void SetParent(GameObject* gameObject) { m_parent = gameObject; }
  const GameObject* GetParent() const { return m_parent; }
  void GetParentMatrix(XMMATRIX& parentMatrix) const;

  const XMFLOAT3 GetWorldPosition() const;
  const BoundingBox* GetBBInWorldCoords() const;
};

