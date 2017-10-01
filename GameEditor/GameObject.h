#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

class GameObject
{
private:
  XMMATRIX m_translationMatrix;
  XMMATRIX m_rotationMatrix;
  XMMATRIX m_worldMatrix;
  bool m_needRebuildTranslationMatrix;
  bool m_needRebuildRotationMatrix;
  float m_positionX, m_positionY, m_positionZ;
  float m_rotationX, m_rotationY, m_rotationZ;
public:
  GameObject();
  virtual ~GameObject();

  void SetPosition(float x, float y, float z);
  void SetRotation(float x, float y, float z);
  XMFLOAT3 GetPosition();
  XMFLOAT3 GetRotation();
  void ChangeXRotation(float angle);
  void ChangeYRotation(float angle);
  void ChangeZRotation(float angle);
  void MoveVerticalInLocalCord(float distance);
  void MoveForwardBackwardInLocalCord(float distance);
  void MoveLeftRightInLocalCord(float distance);
  void virtual GetWorldMatrix(XMMATRIX& worldMatrix);
  void SetWorldMatrix(XMMATRIX worldMatrix);
};

