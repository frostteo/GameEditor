#pragma once

#include "TextureShader.h"
#include "BumpSpecMaterial.h"

class BumpSpecSingleLightSh :
  public TextureShader
{
protected:
  struct CameraBufferType
  {
    XMFLOAT3 cameraPosition;
    float padding;
  };
  struct LightBufferType
  {
    XMVECTOR ambientColor;
    XMVECTOR diffuseColor;
    XMFLOAT3 lightDirection;
  };
  struct MaterialBufferType
  {
    XMFLOAT3 specularColor;
    float specularPower;
    float bumpDepth;
  };
protected:
  ID3D11Buffer* m_lightBuffer;
  ID3D11Buffer* m_cameraBuffer;
  ID3D11Buffer* m_materialBuffer;
protected:
  virtual void ShutdownShader() override;
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) override;
  void SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, XMFLOAT3 lightDirection, XMVECTOR ambientColor,
    XMVECTOR diffuseColor, XMFLOAT3 specularColor, float specularPower, XMFLOAT3 cameraPosition, float bumpDepth);
public:
  BumpSpecSingleLightSh();
  virtual ~BumpSpecSingleLightSh();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition) override;
};

