#pragma once
#include "IShader.h"
#include "BoundingBox.h"
class GridShader :
  public IShader
{
protected:
  ID3D11Buffer* m_matrixBuffer;
protected:
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) override;
  virtual void ShutdownShader();
  void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);
  void SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix);
public:
  GridShader();
  virtual ~GridShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition) override;
};

