#pragma once

#include "IShader.h"

class PLShadowGenerationShader :
  public IShader
{
protected:
  struct WorldMatrixBuffer
  {
    XMMATRIX worldMatrix;
  };
  struct CubeViewProjectionsBuffer
  {
    XMMATRIX cubeViewProjections[6];
  };
protected:
  ID3D11Buffer* m_worldMatrixBuffer;
  ID3D11Buffer* m_shadowMapCubeBuffer;
protected:
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) override;
  virtual void ShutdownShader() override;
  void SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX* cubeViewProjections);
public:
  PLShadowGenerationShader();
  virtual ~PLShadowGenerationShader();
  virtual void EnableShader(ID3D11DeviceContext* deviceContext);
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition) override;
};

