#include "PreviewGameObject.h"
#include "Logger.h"
#include "Camera.h"
#include "StaticGameObject.h"

PreviewGameObject::PreviewGameObject(Camera* camera, StaticGameObject* sgo, MapEditorPreferences* preferences)
{
  m_name = "preview game object";
  m_autoRotateSwicher = false;
  SetCamera(camera);
  SetSGO(sgo);
  SetMapEditorPreferences(preferences);
}


PreviewGameObject::~PreviewGameObject()
{
}

void PreviewGameObject::ProcessUserInput(const InputState* inputState)
{
  m_timeInSecondsBetweenFrames = inputState->time * 0.001f;
  if (m_camera) 
  {
    int deltaZ = inputState->m_mouseState.lZ;
    XMFLOAT3 position = m_camera->GetPosition();
    m_camera->SetPosition(position.x, position.y, position.z + deltaZ * m_preferences->GetCameraZoomSpeed() * m_timeInSecondsBetweenFrames);
  }

  if (inputState->IsKeyDown(DIK_TAB))
  {
    m_autoRotateSwicher = false;
    m_sgo->SetWorldMatrix(XMMatrixIdentity());
  }
  
  
  if (inputState->IsKeyPressed(DIK_SPACE))
    m_autoRotateSwicher = !m_autoRotateSwicher;


  if (m_autoRotateSwicher)
  {
    m_sgo->ChangeYRotation(m_autoRotateYAngle);
    return;
  }

  if (inputState->IsMouseBtnDown(MouseButtons::LeftMouseBtn))
  {
    int deltaX = inputState->m_mouseState.lX;
    int deltaY = inputState->m_mouseState.lY;

    XMMATRIX worldMatrix;
    m_sgo->GetWorldMatrix(worldMatrix);

    if (abs(deltaX) > abs(deltaY)) {
      worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(deltaX * m_rotateCoef));
    }
    else {
      worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationX(deltaY * m_rotateCoef));
    }

    m_sgo->SetWorldMatrix(worldMatrix);
  }
}