#include "ColorDefferedShader.h"
#include "Logger.h"

ColorDefferedShader::ColorDefferedShader()
{
  m_vertexShader = nullptr;
  m_pixelShader = nullptr;
  m_layout = nullptr;
  m_matrixBuffer = nullptr;
  m_cameraBuffer = nullptr;
  m_materialBuffer = nullptr;
}


ColorDefferedShader::~ColorDefferedShader()
{
  ShutdownShader();
}

void ColorDefferedShader::InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename)
{
  HRESULT result;
  ID3D10Blob* errorMessage;
  ID3D10Blob* vertexShaderBuffer;
  ID3D10Blob* pixelShaderBuffer;

  D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
  unsigned int numElements;
  D3D11_BUFFER_DESC matrixBufferDesc;
  D3D11_BUFFER_DESC cameraBufferDesc;
  D3D11_BUFFER_DESC materialBufferDesc;
  std::string vsFilenameStdStr = Utils::UnicodeStrToByteStr(vsFilename);
  std::string psFilenameStdStr = Utils::UnicodeStrToByteStr(psFilename);

  // Initialize the pointers this function will use to null.
  errorMessage = nullptr;
  vertexShaderBuffer = nullptr;
  pixelShaderBuffer = nullptr;

  // Compile the vertex shader code.
  result = D3DCompileFromFile(vsFilename.c_str(), NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
    &vertexShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, vsFilenameStdStr);
  }

  // Compile the pixel shader code.
  result = D3DCompileFromFile(psFilename.c_str(), NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, psFilenameStdStr);
  }

  // Create the vertex shader from the buffer.
  result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
  if (FAILED(result))
    RUNTIME_ERROR("cant create the vertex shader from the buffer");

  // Create the pixel shader from the buffer.
  result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
  if (FAILED(result))
    RUNTIME_ERROR("cant create the pixel shader from the buffer");

  // Create the vertex input layout description.
  // This setup needs to match the VertexType stucture in the ModelClass and in the shader.
  polygonLayout[0].SemanticName = "POSITION";
  polygonLayout[0].SemanticIndex = 0;
  polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  polygonLayout[0].InputSlot = 0;
  polygonLayout[0].AlignedByteOffset = 0;
  polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[0].InstanceDataStepRate = 0;

  polygonLayout[1].SemanticName = "TEXCOORD"; //TODO FHolod: text Coord may be will be removed
  polygonLayout[1].SemanticIndex = 0;
  polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
  polygonLayout[1].InputSlot = 0;
  polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
  polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[1].InstanceDataStepRate = 0;

  polygonLayout[2].SemanticName = "NORMAL";
  polygonLayout[2].SemanticIndex = 0;
  polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  polygonLayout[2].InputSlot = 0;
  polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
  polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[2].InstanceDataStepRate = 0;

  numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

  // Create the vertex input layout.
  result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(),
    &m_layout);
  if (FAILED(result))
    RUNTIME_ERROR("cant create the vertex input layout");

  // Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
  vertexShaderBuffer->Release();
  vertexShaderBuffer = nullptr;

  pixelShaderBuffer->Release();
  pixelShaderBuffer = nullptr;

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
    RUNTIME_ERROR("cant create the matrix constant buffer pointer");

  // Setup the description of the camera dynamic constant buffer that is in the vertex shader.
  cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  cameraBufferDesc.ByteWidth = sizeof(CameraBufferType);
  cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  cameraBufferDesc.MiscFlags = 0;
  cameraBufferDesc.StructureByteStride = 0;

  // Create the camera constant buffer pointer so we can access the vertex shader constant buffer from within this class.
  result = device->CreateBuffer(&cameraBufferDesc, NULL, &m_cameraBuffer);
  if (FAILED(result))
    RUNTIME_ERROR("cant create the camera constant buffer pointer");

  materialBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  materialBufferDesc.ByteWidth = sizeof(ColorMaterialBufferType);
  materialBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  materialBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  materialBufferDesc.MiscFlags = 0;
  materialBufferDesc.StructureByteStride = 0;

  result = device->CreateBuffer(&materialBufferDesc, NULL, &m_materialBuffer);
  if (FAILED(result))
    RUNTIME_ERROR("cant create the material constant buffer pointer");
}

void ColorDefferedShader::ShutdownShader()
{
  IShader::ShutdownShader();

  // Release the matrix constant buffer
  if (m_matrixBuffer)
  {
    m_matrixBuffer->Release();
    m_matrixBuffer = nullptr;
  }

  if (m_cameraBuffer)
  {
    m_cameraBuffer->Release();
    m_cameraBuffer = nullptr;
  }

  if (m_materialBuffer)
  {
    m_materialBuffer->Release();
    m_materialBuffer = nullptr;
  }
}

void ColorDefferedShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
  deviceContext->DrawIndexed(indexCount, 0, 0);
}

void ColorDefferedShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
  XMMATRIX projectionMatrix, XMVECTOR diffuseColor, XMVECTOR specularColor, XMVECTOR selfIluminationColor, float specularPower, float opacity, XMFLOAT3 cameraPosition, ColorMaterialSubType subtype)
{
  HRESULT result;
  D3D11_MAPPED_SUBRESOURCE mappedResource;
  unsigned int bufferNumber;
  MatrixBufferType* matrixBufferPtr;
  CameraBufferType* cameraBufferPtr;
  ColorMaterialBufferType* materialBufferPtr;

  // Transpose the matrices to prepare them for the shader.
  worldMatrix = XMMatrixTranspose(worldMatrix);
  viewMatrix = XMMatrixTranspose(viewMatrix);
  projectionMatrix = XMMatrixTranspose(projectionMatrix);

  // Lock the constant buffer so it can be written to.
  result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("cant lock the constant buffer");

  // Get a pointer to the data in the constant buffer.
  matrixBufferPtr = (MatrixBufferType*)mappedResource.pData;

  // Copy the matrices into the constant buffer.
  matrixBufferPtr->world = worldMatrix;
  matrixBufferPtr->view = viewMatrix;
  matrixBufferPtr->projection = projectionMatrix;

  // Unlock the constant buffer.
  deviceContext->Unmap(m_matrixBuffer, 0);

  // Set the position of the constant buffer in the vertex shader.
  bufferNumber = 0;

  // Now set the constant buffer in the vertex shader with the updated values.
  deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

  // Lock the camera constant buffer so it can be written to.
  result = deviceContext->Map(m_cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("cant lock the camera constant buffer ");

  // Get a pointer to the data in the constant buffer.
  cameraBufferPtr = (CameraBufferType*)mappedResource.pData;

  // Copy the camera position into the constant buffer.
  cameraBufferPtr->cameraPosition = cameraPosition;
  cameraBufferPtr->subtype = (int)subtype;

  // Unlock the camera constant buffer.
  deviceContext->Unmap(m_cameraBuffer, 0);

  // Set the position of the camera constant buffer in the vertex shader.
  bufferNumber = 1;

  // Now set the camera constant buffer in the vertex shader with the updated values.
  deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_cameraBuffer);

  // Lock the material constant buffer so it can be written to.
  result = deviceContext->Map(m_materialBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("cant lock the material constant buffer");

  // Get a pointer to the data in the constant buffer.
  materialBufferPtr = (ColorMaterialBufferType*)mappedResource.pData;

  // Copy the material variables into the constant buffer.
  materialBufferPtr->diffuseColor = diffuseColor;
  materialBufferPtr->specularColor = specularColor;
  materialBufferPtr->selfIluminationColor = selfIluminationColor;
  materialBufferPtr->specularPower = specularPower;
  materialBufferPtr->opacity = opacity;
  materialBufferPtr->subtype = static_cast<int>(subtype);

  // Unlock the constant buffer.
  deviceContext->Unmap(m_materialBuffer, 0);

  // Set the position of the material constant buffer in the pixel shader.
  bufferNumber = 0;

  // Finally set the light constant buffer in the pixel shader with the updated values.
  deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_materialBuffer);
}

void ColorDefferedShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
  XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition)
{
  ColorMaterial* colorMaterial = (ColorMaterial *)material;

  SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, colorMaterial->m_diffuseColor, colorMaterial->m_specularColor, colorMaterial->m_selfIluminationColor, colorMaterial->m_specularPower, colorMaterial->m_opacity, cameraPosition, colorMaterial->m_subType);

  RenderShader(deviceContext, indexCount);
}