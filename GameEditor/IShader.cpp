#include "IShader.h"


IShader::IShader()
{
}


IShader::~IShader()
{
  ShutdownShader();
}

void IShader::ShutdownShader()
{
  // Release the layout.
  if (m_layout)
  {
    m_layout->Release();
    m_layout = nullptr;
  }

  // Release the pixel shader.
  if (m_pixelShader)
  {
    m_pixelShader->Release();
    m_pixelShader = nullptr;
  }

  // Release the vertex shader.
  if (m_vertexShader)
  {
    m_vertexShader->Release();
    m_vertexShader = nullptr;
  }
}

void IShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const std::string& shaderFilename)
{
  char* compileErrors;
  unsigned long long bufferSize, i;

  // Get a pointer to the error message text buffer.
  compileErrors = (char*)(errorMessage->GetBufferPointer());

  // Get the length of the message.
  bufferSize = errorMessage->GetBufferSize();

  std::string compilingShaderError(compileErrors, bufferSize);
  Logger::get().LogMessage(compilingShaderError);

  // Release the error message.
  errorMessage->Release();
  errorMessage = 0;
  throw std::runtime_error("Error compiling shader. " + shaderFilename + "  Check " + Logger::get().GetLogFileName() + " for message.");

  return;
}

void IShader::Initialize(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& psFilename)
{
  // Initialize the vertex and pixel shaders.
  InitializeShader(device, hwnd, vsFilename, psFilename);
}


void IShader::EnableShader(ID3D11DeviceContext* deviceContext)
{
  // Set the vertex input layout.
  deviceContext->IASetInputLayout(m_layout);

  // Set the vertex and pixel shaders that will be used to render this triangle.
  deviceContext->VSSetShader(m_vertexShader, NULL, 0);
  deviceContext->PSSetShader(m_pixelShader, NULL, 0);
}

void IShader::SetTextures(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView** textures, int textureCount)
{
  // Set shader texture array resource in the pixel shader.
  deviceContext->PSSetShaderResources(0, textureCount, textures);
}