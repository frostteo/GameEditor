#include "ConfigurePLRelPosControl.h"
#include "ConfigurePLRelativePosWidget.h"
#include "Logger.h"
#include "Camera.h"
#include "StaticGameObject.h"

ConfigurePLRelPosControl::ConfigurePLRelPosControl(ConfigurePLRelativePosWidget* configurePLRelativePosWidget, Camera* camera, StaticGameObject* pointLightSgo, MapEditorPreferences* preferences)
{
  m_camera = camera;
  m_pointLightSgo = pointLightSgo;
  m_preferences = preferences;
  m_configurePLRelativePosWidget = configurePLRelativePosWidget;
}

ConfigurePLRelPosControl::~ConfigurePLRelPosControl()
{
}

void ConfigurePLRelPosControl::ProcessUserInput(const InputState* inputState)
{
  m_timeInSecondsBetweenFrames = inputState->time * 0.001f;
  if (m_camera)
  {
    ZoomCamera(inputState);
  }

  if (inputState->IsMouseBtnDown(MouseButtons::LeftMouseBtn))
  {
    MovePointLight(inputState);
  }

  if (inputState->IsMouseBtnDown(MouseButtons::RightMouseBtn))
  {
    RotateCameraAroundSGO(inputState);
  }

  if (inputState->IsMouseBtnReleased(MouseButtons::LeftMouseBtn))
  {
    m_configurePLRelativePosWidget->EmitPointLightPositionChanged();
  }
}

void ConfigurePLRelPosControl::RotateCameraAroundSGO(const InputState* inputState)
{
  float deltaXRadians = XMConvertToRadians(inputState->m_mouseState.lX * m_preferences->GetCameraRotationSpeed() * m_timeInSecondsBetweenFrames);
  float deltaYRadians = XMConvertToRadians(inputState->m_mouseState.lY * m_preferences->GetCameraRotationSpeed() * m_timeInSecondsBetweenFrames);

  XMVECTOR helper;
  XMFLOAT3 cameraPosition = m_camera->GetPosition();
  XMVECTOR rightCamera = m_camera->GetRight();
  XMVECTOR cameraPositionXm = XMLoadFloat3(&cameraPosition);
  XMMATRIX newCameraMatrix = GEMath::GetCameraMatrixRotateAroundTarget(cameraPositionXm, XMVECTOR(), deltaXRadians, deltaYRadians, rightCamera);
  m_camera->SetWorldMatrix(XMMatrixInverse(&helper, newCameraMatrix));
}

void ConfigurePLRelPosControl::MovePointLight(const InputState* inputState)
{
  float deltaX = inputState->m_mouseState.lX * m_preferences->GetObjectMoveSpeed() * m_timeInSecondsBetweenFrames;
  float deltaY = inputState->m_mouseState.lY * m_preferences->GetObjectMoveSpeed() * m_timeInSecondsBetweenFrames;

  if (deltaX == 0.0f && deltaY == 0.0f)
    return;

  bool needMoveYAxis = inputState->IsKeyDown(DIK_Z);
  bool needMoveXAxis = inputState->IsKeyDown(DIK_X);
  bool needMoveZAxis = inputState->IsKeyDown(DIK_Y);

  XMFLOAT3 plPosition = m_pointLightSgo->GetPosition();
  XMVECTOR rightCamera = m_camera->GetRight();
  XMVECTOR forwardMoveVector = XMVector3Normalize(XMVector3Cross(rightCamera, GEMath::UpWorld));

  if (needMoveZAxis == needMoveXAxis)
  {
    needMoveXAxis = true;
    needMoveZAxis = true;
  }

  if (needMoveYAxis)
  {
    plPosition.y -= deltaY;
  }
  else 
  {
    if (needMoveXAxis) {
      plPosition.x += deltaX * XMVectorGetX(rightCamera);
      plPosition.x += deltaY * XMVectorGetX(forwardMoveVector);
    }

    if (needMoveZAxis) {
      plPosition.z += deltaX * XMVectorGetZ(rightCamera);
      plPosition.z += deltaY * XMVectorGetZ(forwardMoveVector);
    }
  }

  m_pointLightSgo->SetPosition(plPosition.x, plPosition.y, plPosition.z);
}

void ConfigurePLRelPosControl::ZoomCamera(const InputState* inputState)
{
  int deltaZ = inputState->m_mouseState.lZ;
  XMFLOAT3 position = m_camera->GetPosition();
  m_camera->MoveForward(deltaZ * m_preferences->GetCameraZoomSpeed() * m_timeInSecondsBetweenFrames);
}