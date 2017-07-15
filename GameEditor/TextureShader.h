#pragma once
#include <d3dcompiler.h>
#include <fstream>
#include <string>
#include "IShader.h"
#include "TextureMaterial.h"
#include "Logger.h"
#include "FileProcessor.h"

class TextureShader : public IShader
{
private:
  struct MatrixBufferType
  {
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX projection;
  };
private:
  ID3D11VertexShader* m_vertexShader;
  ID3D11PixelShader* m_pixelShader;
  ID3D11InputLayout* m_layout;
  ID3D11Buffer* m_matrixBuffer;
  ID3D11SamplerState* m_sampleState;
protected:
  bool InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& psFilename);
  void ShutdownShader();
  void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const std::wstring& shaderFilename); 
  bool SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture);
  void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);
public:
  TextureShader();
  ~TextureShader();

  bool Initialize(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& psFilename);
  void Shutdown();
  virtual bool Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material) override;
};

