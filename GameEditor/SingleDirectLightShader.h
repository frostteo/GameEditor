#pragma once

#include "TextureShader.h"
#include "TextureMaterial.h"

class SingleDirectLightShader : public TextureShader
{
protected:
  struct LightBufferType
  {
    XMVECTOR ambientColor;
    XMVECTOR diffuseColor;
    XMFLOAT3 lightDirection;
    float padding;
  };
protected:
  ID3D11Buffer* m_lightBuffer;
protected:
  virtual void ShutdownShader() override;
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& psFilename) override;
  bool SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection, XMVECTOR ambientColor,
    XMVECTOR diffuseColor);
public:
  SingleDirectLightShader();
  virtual ~SingleDirectLightShader();
  virtual bool Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition) override;
};

