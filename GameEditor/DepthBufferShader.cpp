#include "DepthBufferShader.h"


DepthBufferShader::DepthBufferShader()
{
  m_matrixBuffer = nullptr;
  m_layout = nullptr;
  m_vertexShader = nullptr;
  m_pixelShader = nullptr;
}


DepthBufferShader::~DepthBufferShader()
{
  ShutdownShader();
}

void DepthBufferShader::InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& psFilename)
{
  HRESULT result;
  ID3D10Blob* errorMessage;
  ID3D10Blob* vertexShaderBuffer;
  D3D11_INPUT_ELEMENT_DESC polygonLayout[1];
  unsigned int numElements;
  D3D11_BUFFER_DESC matrixBufferDesc;
  std::string vsFilenameStdStr = Utils::UnicodeStrToByteStr(vsFilename);
  std::string psFilenameStdStr = Utils::UnicodeStrToByteStr(psFilename);

  // Initialize the pointers this function will use to null.
  errorMessage = nullptr;
  vertexShaderBuffer = nullptr;

  // Compile the vertex shader code.
  result = D3DCompileFromFile(vsFilename.c_str(), NULL, NULL, "TextureVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
    &vertexShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    // If the shader failed to compile it should have writen something to the error message.
    if (errorMessage)
      OutputShaderErrorMessage(errorMessage, hwnd, vsFilenameStdStr);

    // If there was nothing in the error message then it simply could not find the shader file itself.
    else
      throw std::runtime_error("Missing Shader File " + vsFilenameStdStr);
  }

  // Create the vertex shader from the buffer.
  result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
  if (FAILED(result))
  {
    throw std::runtime_error("failed vertex shader creation " + vsFilenameStdStr);
  }

  // Create the vertex input layout description.
  // This setup needs to match the VertexType stucture in the ModelClass and in the shader.
  polygonLayout[0].SemanticName = "POSITION";
  polygonLayout[0].SemanticIndex = 0;
  polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  polygonLayout[0].InputSlot = 0;
  polygonLayout[0].AlignedByteOffset = 0;
  polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[0].InstanceDataStepRate = 0;

  // Get a count of the elements in the layout.
  numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

  // Create the vertex input layout.
  result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
    vertexShaderBuffer->GetBufferSize(), &m_layout);
  if (FAILED(result))
  {
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("failed input layout creation " + vsFilenameStdStr, __FILE__, __LINE__));
  }

  // Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
  vertexShaderBuffer->Release();
  vertexShaderBuffer = nullptr;

  // Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
  matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
  matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  matrixBufferDesc.MiscFlags = 0;
  matrixBufferDesc.StructureByteStride = 0;

  // Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
  result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
  if (FAILED(result))
  {
    throw std::runtime_error("failed input create matrix buffer " + vsFilenameStdStr);
  }
}

void DepthBufferShader::ShutdownShader()
{
  IShader::ShutdownShader();

  if (m_matrixBuffer)
  {
    m_matrixBuffer->Release();
    m_matrixBuffer = nullptr;
  }
}

void DepthBufferShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
  XMMATRIX projectionMatrix)
{
  HRESULT result;
  D3D11_MAPPED_SUBRESOURCE mappedResource;
  MatrixBufferType* dataPtr;
  unsigned int bufferNumber;

  // Transpose the matrices to prepare them for the shader.
  worldMatrix = XMMatrixTranspose(worldMatrix);
  viewMatrix = XMMatrixTranspose(viewMatrix);
  projectionMatrix = XMMatrixTranspose(projectionMatrix);

  // Lock the constant buffer so it can be written to.
  result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("cant lock the matrix constant buffer", __FILE__, __LINE__));

  // Get a pointer to the data in the constant buffer.
  dataPtr = (MatrixBufferType*)mappedResource.pData;

  // Copy the matrices into the constant buffer.
  dataPtr->world = worldMatrix;
  dataPtr->view = viewMatrix;
  dataPtr->projection = projectionMatrix;

  // Unlock the constant buffer.
  deviceContext->Unmap(m_matrixBuffer, 0);

  // Set the position of the constant buffer in the vertex shader.
  bufferNumber = 0;

  // Finanly set the constant buffer in the vertex shader with the updated values.
  deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
}

void DepthBufferShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
  XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition)
{
  SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
  deviceContext->DrawIndexed(indexCount, 0, 0);
}

void DepthBufferShader::EnableShader(ID3D11DeviceContext* deviceContext)
{
  deviceContext->IASetInputLayout(m_layout);
  deviceContext->VSSetShader(m_vertexShader, NULL, 0);
  deviceContext->PSSetShader(nullptr, NULL, 0);
}