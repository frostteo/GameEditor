#pragma once

#include "TextureShader.h"
#include "BumpSpecMaterial.h"

class BumpSpecDefferedShader :
  public TextureShader
{
protected:
  struct CameraBufferType
  {
    XMFLOAT3 cameraPosition;
    float padding;
  };
  struct MaterialBufferType
  {
    XMFLOAT3 specularColor;
    float specularPower;
    float bumpDepth;
  };
protected:
  ID3D11Buffer* m_cameraBuffer;
  ID3D11Buffer* m_materialBuffer;
protected:
  virtual void ShutdownShader() override;
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) override;
  void SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, XMFLOAT3 specularColor, float specularPower, XMFLOAT3 cameraPosition, float bumpDepth);
public:
  BumpSpecDefferedShader();
  virtual ~BumpSpecDefferedShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, const IMaterial* material, LightininigSystem* lightining, const XMFLOAT3& cameraPosition) override;
};

