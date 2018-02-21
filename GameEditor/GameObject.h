#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

class GameObject
{
protected:
  XMMATRIX m_scaleMatrix;
  XMMATRIX m_translationMatrix;
  XMMATRIX m_rotationMatrix;
  XMMATRIX m_worldMatrix;
  bool m_needRebuildTranslationMatrix;
  bool m_needRebuildRotationMatrix;
  bool m_needRebuildScaleMatrix;
  float m_positionX, m_positionY, m_positionZ;
  float m_rotationX, m_rotationY, m_rotationZ;
  float m_scale = 1.0f;
  GameObject* m_parent;
  XMFLOAT3 m_worldPosition;
public :
  bool needRebuildDependOnWorldMatrix = true; // Для обозначения что нужно перестроить объекты в наследниках зависящие от изменения матрицы мировых координат, например bounding box
protected:
  virtual void RebuildWorldMatrix();
public:
  GameObject();
  virtual ~GameObject();

  void virtual SetPosition(float x, float y, float z);
  void SetRotation(float x, float y, float z);
  XMFLOAT3 GetPosition();
  XMFLOAT3 GetRotation();
  void ChangeXRotation(float angle);
  void ChangeYRotation(float angle);
  void ChangeZRotation(float angle);

  void SetScale(float scale) { m_scale = scale; m_needRebuildScaleMatrix = true; }
  float GetScale() { return m_scale; }

  void virtual GetWorldMatrix(XMMATRIX& worldMatrix);
  void SetWorldMatrix(XMMATRIX worldMatrix);

  XMVECTOR GetRight();
  XMVECTOR GetUp();
  XMVECTOR GetForward();

  void MoveRight(float distance);
  void MoveUp(float distance);
  void MoveForward(float distance);

  inline bool NeedRebuildWorldMatrix() { return m_needRebuildTranslationMatrix || m_needRebuildRotationMatrix || m_needRebuildScaleMatrix; }

  void SetParent(GameObject* gameObject) { m_parent = gameObject; }
  GameObject* GetParent() { return m_parent; }
  void GetParentMatrix(XMMATRIX& parentMatrix) const;

  XMFLOAT3 GetWorldPosition();
};

