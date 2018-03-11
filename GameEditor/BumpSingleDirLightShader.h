#pragma once

#include "SingleDirectLightShader.h"
#include "BumpMaterial.h"

class BumpSingleDirLightShader
  : public SingleDirectLightShader
{
protected:
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) override;
  void SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix,
    XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 lightDirection,
    XMVECTOR ambientColor, XMVECTOR diffuseColor, float bumpDepth);
public:
  BumpSingleDirLightShader();
  virtual ~BumpSingleDirLightShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, const IMaterial* material, LightininigSystem* lightining, const XMFLOAT3& cameraPosition) override;
};

