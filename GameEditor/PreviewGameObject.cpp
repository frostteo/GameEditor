#include "PreviewGameObject.h"

PreviewGameObject::PreviewGameObject()
{
  m_name = "preview game object";
  m_rotateSwicher = false;
}


PreviewGameObject::~PreviewGameObject()
{
}

void PreviewGameObject::ProcessUserInput(InputState* inputState)
{
  if (m_camera) 
  {
    int deltaZ = inputState->m_mouseState.lZ;
    XMFLOAT3 position = m_camera->GetPosition();
    m_camera->SetPosition(position.x, position.y, position.z + deltaZ * m_scaleCoef);
  }

  if (inputState->IsKeyDown(DIK_TAB))
  {
    m_rotateSwicher = false;
    m_model->SetWorldMatrix(XMMatrixIdentity());
  }
  
  
  if (inputState->IsKeyPressed(DIK_SPACE))
    m_rotateSwicher = !m_rotateSwicher;


  if (m_rotateSwicher)
  {
    m_model->ChangeYRotation(0.5);
    return;
  }

  if (inputState->IsMouseBtnDown(MouseButtons::LeftMouseBtn))
  {
    int deltaX = inputState->m_mouseState.lX;
    int deltaY = inputState->m_mouseState.lY;

    XMMATRIX worldMatrix;
    m_model->GetWorldMatrix(worldMatrix);

    if (abs(deltaX) > abs(deltaY)) {
      worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationNormal(XMVectorSet(0, 1, 0, 1), deltaX * m_rotateCoef));
    }
    else {
      worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationNormal(XMVectorSet(1, 0, 0, 1), deltaY * m_rotateCoef));
    }

    m_model->SetWorldMatrix(worldMatrix);
  }
}