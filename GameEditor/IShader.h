#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <string>
#include "IMaterial.h"
#include "Logger.h"
#include "FileProcessor.h"
#include "LightininigSystem.h"
#include "Utils.h"

using namespace DirectX;

class IShader
{
protected:
  struct MatrixBufferType
  {
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX projection;
  };
protected:
  ID3D11VertexShader* m_vertexShader;
  ID3D11HullShader* m_hullShader;
  ID3D11DomainShader* m_domainShader;
  ID3D11PixelShader* m_pixelShader;
  ID3D11InputLayout* m_layout;
protected:
  void OutputShaderErrorMessage(ID3D10Blob* errorMessage, const std::string& shaderFilename);
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) = 0;
  virtual void ShutdownShader();
public:
  IShader();
  virtual ~IShader();
  virtual void EnableShader(ID3D11DeviceContext* deviceContext);
  void SetTextures(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView** textures, int textureCount);
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition) = 0;
  void Initialize(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename);
};

