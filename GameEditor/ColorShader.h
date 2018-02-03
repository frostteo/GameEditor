#pragma once

#include "IShader.h"
#include "ColorMaterial.h"

class ColorShader :
  public IShader
{
protected:
  struct CameraBufferType
  {
    XMFLOAT3 cameraPosition;
    int subtype; //It is here for useability
  };
  struct LightBufferColorType 
  {
    XMVECTOR ambientLightColor;
    XMVECTOR diffuseLightColor;
    XMFLOAT3 lightDirection;
  };
  struct ColorMaterialBufferType
  {
    XMVECTOR diffuseColor;
    XMVECTOR specularColor;
    XMVECTOR selfIluminationColor;
    float specularPower;
    float opacity;
    int subtype;
  };
protected:
  ID3D11Buffer* m_matrixBuffer;
  ID3D11Buffer* m_cameraBuffer;
  ID3D11Buffer* m_lightBuffer;
  ID3D11Buffer* m_materialBuffer;
protected:
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) override;
  virtual void ShutdownShader();
  void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);
  void SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, XMFLOAT3 lightDirection, XMVECTOR ambientLightColor,
    XMVECTOR diffuseLightColor, XMVECTOR diffuseColor, XMVECTOR specularColor, XMVECTOR selfIluminationColor, float specularPower, float opacity, XMFLOAT3 cameraPosition, ColorMaterialSubType subtype);
public:
  ColorShader();
  virtual ~ColorShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition) override;
};

