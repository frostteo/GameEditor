#include "IShader.h"


IShader::IShader()
{
}


IShader::~IShader()
{
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