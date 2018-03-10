#include "AmbientDefferedShader.h"
#include "Logger.h"

AmbientDefferedShader::AmbientDefferedShader()
{
  m_vertexShader = nullptr;
  m_pixelShader = nullptr;
  m_layout = nullptr;
  m_sampleState = nullptr;
  m_lightBuffer = nullptr;
}


AmbientDefferedShader::~AmbientDefferedShader()
{
  ShutdownShader();
}

void AmbientDefferedShader::InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename)
{
  HRESULT result;
  ID3D10Blob* errorMessage;
  ID3D10Blob* vertexShaderBuffer;
  ID3D10Blob* pixelShaderBuffer;
  D3D11_BUFFER_DESC lightBufferDesc;
  D3D11_SAMPLER_DESC samplerDesc;
  std::string vsFilenameStdStr = Utils::UnicodeStrToByteStr(vsFilename);
  std::string psFilenameStdStr = Utils::UnicodeStrToByteStr(psFilename);

  // Initialize the pointers this function will use to null.
  errorMessage = nullptr;
  vertexShaderBuffer = nullptr;
  pixelShaderBuffer = nullptr;

  // Compile the vertex shader code.
  result = D3DCompileFromFile(vsFilename.c_str(), NULL, NULL, "AmbientVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
    &vertexShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, vsFilenameStdStr);
  }

  // Compile the pixel shader code.
  result = D3DCompileFromFile(psFilename.c_str(), NULL, NULL, "AmbientPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
    &pixelShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, psFilenameStdStr);
  }

  // Create the vertex shader from the buffer.
  result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
  if (FAILED(result))
  {
    RUNTIME_ERROR("failed vertex shader creation " + vsFilenameStdStr);
  }

  // Create the pixel shader from the buffer.
  result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
  if (FAILED(result))
    RUNTIME_ERROR("failed pixel shader creation " + psFilenameStdStr);

  // Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
  vertexShaderBuffer->Release();
  vertexShaderBuffer = nullptr;

  pixelShaderBuffer->Release();
  pixelShaderBuffer = nullptr;

  // Setup the description of the light dynamic constant buffer that is in the pixel shader.
  // Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
  lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  lightBufferDesc.ByteWidth = sizeof(LightBufferType);
  lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  lightBufferDesc.MiscFlags = 0;
  lightBufferDesc.StructureByteStride = 0;

  // Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
  result = device->CreateBuffer(&lightBufferDesc, NULL, &m_lightBuffer);
  if (FAILED(result))
  {
    RUNTIME_ERROR("failed create buffer for lights " + vsFilenameStdStr);
  }
}

void AmbientDefferedShader::ShutdownShader()
{
  IShader::ShutdownShader();

  // Release the sampler state.
  if (m_sampleState)
  {
    m_sampleState->Release();
    m_sampleState = nullptr;
  }

  if (m_lightBuffer)
  {
    m_lightBuffer->Release();
    m_lightBuffer = nullptr;
  }
}

void AmbientDefferedShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMVECTOR ambientColor)
{
  HRESULT result;
  D3D11_MAPPED_SUBRESOURCE mappedResource;
  unsigned int bufferNumber;
  LightBufferType* lightBufferDataPtr;

  // Lock the light constant buffer so it can be written to.
  result = deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("cant lock the light constant buffer "); 

  // Get a pointer to the data in the constant buffer.
  lightBufferDataPtr = (LightBufferType*)mappedResource.pData;

  // Copy the lighting variables into the constant buffer.
  lightBufferDataPtr->ambientColor = ambientColor;

  // Unlock the constant buffer.
  deviceContext->Unmap(m_lightBuffer, 0);

  // Set the position of the light constant buffer in the pixel shader.
  bufferNumber = 0;

  // Finally set the light constant buffer in the pixel shader with the updated values.
  deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);
}

void AmbientDefferedShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
  XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition)
{
  SetShaderParameters(deviceContext, lightining->GetAmbientColor());
  deviceContext->Draw(4, 0);
}

void AmbientDefferedShader::EnableShader(ID3D11DeviceContext* deviceContext)
{
  deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
  deviceContext->HSSetShader(nullptr, nullptr, 0);
  deviceContext->DSSetShader(nullptr, nullptr, 0);
  deviceContext->GSSetShader(nullptr, nullptr, 0);
  deviceContext->PSSetShader(m_pixelShader, nullptr, 0);
}