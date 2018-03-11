#include "IShader.h"
#include "Logger.h"
#include "LightininigSystem.h"

IShader::IShader()
{
  m_vertexShader = nullptr;
  m_geometricShader = nullptr;
  m_hullShader = nullptr;
  m_domainShader = nullptr;
  m_pixelShader = nullptr;
  m_layout = nullptr;
}


IShader::~IShader()
{
  ShutdownShader();
}

void IShader::ShutdownShader()
{
  if (m_layout)
  {
    m_layout->Release();
    m_layout = nullptr;
  }

  if (m_vertexShader)
  {
    m_vertexShader->Release();
    m_vertexShader = nullptr;
  }

  if (m_geometricShader)
  {
    m_geometricShader->Release();
    m_geometricShader = nullptr;
  }

  if (m_hullShader)
  {
    m_hullShader->Release();
    m_hullShader = nullptr;
  }

  if (m_domainShader)
  {
    m_domainShader->Release();
    m_domainShader = nullptr;
  }

  if (m_pixelShader)
  {
    m_pixelShader->Release();
    m_pixelShader = nullptr;
  }
}

void IShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, const std::string& shaderFilename)
{
  if (errorMessage)
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
    RUNTIME_ERROR("Error compiling shader. " + shaderFilename + "  Check " + Logger::get().GetLogFileName() + " for message.");
  }
  else
  {
    RUNTIME_ERROR("Missing Shader File " + shaderFilename);
  }

}

void IShader::Initialize(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename)
{
  // Initialize the vertex and pixel shaders.
  InitializeShader(device, hwnd, vsFilename, gsFilename, hlFilename, dmShaderFileName, psFilename);
}


void IShader::EnableShader(ID3D11DeviceContext* deviceContext)
{
  deviceContext->IASetInputLayout(m_layout);
  deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
  deviceContext->GSSetShader(nullptr, nullptr, 0);
  deviceContext->HSSetShader(nullptr, nullptr, 0);
  deviceContext->DSSetShader(nullptr, nullptr, 0);
  deviceContext->PSSetShader(m_pixelShader, nullptr, 0);
}

void IShader::SetTextures(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* const* textures, int textureCount)
{
  // Set shader texture array resource in the pixel shader.
  deviceContext->PSSetShaderResources(0, textureCount, textures);
}