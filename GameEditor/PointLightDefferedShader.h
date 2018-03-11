#pragma once

#include "TextureShader.h"
#include "PointLightDefferedParameters.h"

class PointLightDefferedShader :
  public TextureShader
{
protected:
  struct WorldCoordsUnpackBuffer
  {
    XMVECTOR perspectiveValues;
    XMMATRIX viewMatrixInverse;
  };
  struct PointLightBuffer
  {
    XMFLOAT3 color;
    float linearAttenuation;
    XMFLOAT3 position;
    float quadraticAttenuation;
  };
protected:
  ID3D11Buffer* m_worldCoordsUnpackBuffer;
  ID3D11Buffer* m_pointLightBuffer;
protected:
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) override;
  virtual void ShutdownShader() override;
  void SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, XMFLOAT3 pointLightColor, XMFLOAT3 pointLightPosition, float linearAttenuation, float quadraticAttenuation, XMVECTOR perspectiveValues, XMMATRIX viewMatrixInv);
public:
  PointLightDefferedShader();
  virtual ~PointLightDefferedShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, const IMaterial* material, LightininigSystem* lightining, const XMFLOAT3& cameraPosition) override;
};

