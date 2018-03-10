#pragma once

#include "TextureShader.h"
#include "BumpMaterial.h"

class Logger;

class BumpDefferedShader :
  public TextureShader
{
protected:
  struct MaterialBufferType
  {
    float bumpDepth;
    float padding[3];
  };
protected:
  ID3D11Buffer* m_materialBuffer;
protected:
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) override;
  virtual void ShutdownShader() override;
  void SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix,
    XMMATRIX viewMatrix, XMMATRIX projectionMatrix, float bumpDepth);
public:
  BumpDefferedShader();
  virtual ~BumpDefferedShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, const XMFLOAT3& cameraPosition) override;
};

