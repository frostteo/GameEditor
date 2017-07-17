#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <string>
#include "IMaterial.h"
#include "Logger.h"
#include "FileProcessor.h"
#include "LightininigSystem.h"

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
  void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const std::wstring& shaderFilename);
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& psFilename) = 0;
public:
  IShader();
  virtual ~IShader();
  virtual bool Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition) = 0;
  void Initialize(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& psFilename);
};

