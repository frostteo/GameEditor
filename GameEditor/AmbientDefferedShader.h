#pragma once

#include "IShader.h"

class AmbientDefferedShader :
  public IShader
{
private:
  struct LightBufferType
  {
    XMVECTOR ambientColor;
  };
protected:
  ID3D11SamplerState* m_sampleState;
  ID3D11Buffer* m_lightBuffer;
protected:
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) override;
  virtual void ShutdownShader() override;
  void SetShaderParameters(ID3D11DeviceContext* deviceContext, XMVECTOR ambientColor);
public:
  AmbientDefferedShader();
  virtual ~AmbientDefferedShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition) override;
  virtual void EnableShader(ID3D11DeviceContext* deviceContext) override;
};

