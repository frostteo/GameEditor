#pragma once

#include <algorithm>
#include <initializer_list>
#include <math.h>
#include "GameObject.h"
#include "PointLightShadowDirection.h"
#include "D3DConfigurer.h"

class PointLight :
  public GameObject
{
protected:
  static const float SHADOW_NEAR_PLANE;

  float m_linerarAttenuation = 0.0f;
  float m_quadraticAttenuation = 0.0f;
  XMFLOAT3 m_color;
  float m_radius = 0;

  mutable XMMATRIX m_cubeViewProjection[6];
  XMFLOAT2 m_lightPerspectiveValues;
  mutable XMFLOAT3 m_oldWorldPosition;

  PointLightShadowDirection m_shadowDirections;
  int m_shadowDirectionsArr[6];
  int m_shadowDirectionsArrSize;

  mutable XMMATRIX m_20percentLightVolumeMatrix;

  ID3D11Texture2D* m_pointLightShadowDepthBuffer = nullptr;
  ID3D11DepthStencilView* m_pointLightShadowDSV = nullptr;
  ID3D11ShaderResourceView* m_pointLightShadowSRV = nullptr;
protected:
  void RebuildPerspectiveValues();
  void RebuildCubeViewProjection(XMFLOAT3 worldPosition) const;
  void SetShadowDirections(PointLightShadowDirection shadowDirections);
  virtual void RebuildBBInWorldCoord() const override;
  virtual void RebuildWorldMatrix() const override;
public:
  bool castShadows = false;
public:
  PointLight() = default;
  void virtual SetPosition(float x, float y, float z) override;
  void Initialize(float linearAttenuation, float quadraticAttenuation, XMFLOAT3 position, XMFLOAT3 color, GameObject* parent, bool castShadows = false, PointLightShadowDirection shadowDirections = static_cast<PointLightShadowDirection>(63));

  void InitializeShadowResources(ID3D11Device* device);
  void PrepareToShadowGeneration(ID3D11DeviceContext* deviceContext);
  ID3D11ShaderResourceView** GetPointLightShadowBuffer() { return &m_pointLightShadowSRV; }

  void SetAttenuation(float linearAttenuation, float quadraticAttenuation);
  float GetLinearAttenuation() const { return m_linerarAttenuation; }
  float GetQuadraticAttenuation() const { return m_quadraticAttenuation; }

  void SetColor(XMFLOAT3 color) { m_color = color; }
  XMFLOAT3 GetColor() const { return m_color; }
  
  float GetRadius() const { return m_radius; }
  virtual ~PointLight();

  XMMATRIX* GetCubeViewProjection() const;
  XMFLOAT2 GetLightPerspectiveValues() const;

  const int* const GetShaderShadowDirectionsArr() const;
  const int GetShaderShadowDirectionsArrSize() const;

  void Get20PercentLightVolumeMatrix(XMMATRIX& lightVolume) const;
  const BoundingBox* GetAABBBoundingBox() const;
};

