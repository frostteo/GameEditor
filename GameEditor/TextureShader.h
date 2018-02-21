#pragma once

#include "IShader.h"
#include "TextureMaterial.h"

class TextureShader : public IShader
{
protected:
  ID3D11Buffer* m_matrixBuffer;
  ID3D11SamplerState* m_sampleState;
protected:
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) override;
  virtual void ShutdownShader();
  void SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix);
  void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);
public:
  TextureShader();
  virtual ~TextureShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition) override;
  virtual void EnableShader(ID3D11DeviceContext* deviceContext) override;
};

