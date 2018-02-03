#include "PointLight.h"


PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}

void PointLight::Initialize(float linearAttenuation, float quadraticAttenuation, XMFLOAT3 position, XMFLOAT3 color, GameObject* parent)
{
  SetColor(color);
  SetAttenuation(linearAttenuation, quadraticAttenuation);
  SetPosition(position.x, position.y, position.z);
  SetParent(parent);
}

void PointLight::SetAttenuation(float linearAttenuation, float quadraticAttenuation)
{
  m_linerarAttenuation = linearAttenuation;
  m_quadraticAttenuation = quadraticAttenuation;

  float maxColorPart = (std::max)({ m_color.x, m_color.y, m_color.z });
  float D = pow(m_linerarAttenuation, 2) - 4 * m_quadraticAttenuation * (1 - 256.0f * maxColorPart);

  if (D < 0)
  {
    this->SetScale(0.0f);
    return;
  }

  if (D == 0)
  {
    m_radius = -m_linerarAttenuation / (2 * m_quadraticAttenuation);
  }
  else if (D > 0)
  {
    float x1 = (-m_linerarAttenuation + sqrtf(D)) / (2 * m_quadraticAttenuation);
    float x2 = (-m_linerarAttenuation - sqrtf(D)) / (2 * m_quadraticAttenuation);
    m_radius = max(x1, x2);
  }
  m_radius *= 100.0f;
  this->SetScale(m_radius);
}

void PointLight::GetWorldMatrix(XMMATRIX& worldMatrix)
{
  m_needRebuildRotationMatrix = false;
  if (NeedRebuildWorldMatrix())
  {
    needRebuildDependOnWorldMatrix = true;

    if (m_needRebuildTranslationMatrix) {
      m_translationMatrix = XMMatrixTranslation(m_positionX, m_positionY, m_positionZ);
      m_needRebuildTranslationMatrix = false;
    }

    if (m_needRebuildScaleMatrix) {
      m_scaleMatrix = XMMatrixScaling(m_scale, m_scale, m_scale);
      m_needRebuildScaleMatrix = false;
    }

    m_worldMatrix = XMMatrixMultiply(m_scaleMatrix, m_translationMatrix);
  }

  if (m_parent)
  {
    XMMATRIX parentMatrix;
    GetParentMatrix(parentMatrix);

    worldMatrix = XMMatrixMultiply(m_worldMatrix, parentMatrix);
  }
  else
  {
    worldMatrix = m_worldMatrix;
  }
}