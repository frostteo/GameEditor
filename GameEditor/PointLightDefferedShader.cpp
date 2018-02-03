#include "PointLightDefferedShader.h"


PointLightDefferedShader::PointLightDefferedShader()
{
  m_worldCoordsUnpackBuffer = nullptr;
  m_pointLightBuffer = nullptr;
}


PointLightDefferedShader::~PointLightDefferedShader()
{
  ShutdownShader();
}

void PointLightDefferedShader::InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename)
{
  HRESULT result;
  ID3D10Blob* errorMessage;
  ID3D10Blob* vertexShaderBuffer;
  ID3D10Blob* pixelShaderBuffer;
  D3D11_BUFFER_DESC matrixBufferDesc;
  D3D11_BUFFER_DESC worldCoordsUnpackBufferDesc;
  D3D11_BUFFER_DESC pointLightBufferDesc;
  D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
  unsigned int numElements;
  D3D11_SAMPLER_DESC samplerDesc;
  std::string vsFilenameStdStr = Utils::UnicodeStrToByteStr(vsFilename);
  std::string psFilenameStdStr = Utils::UnicodeStrToByteStr(psFilename);

  errorMessage = nullptr;
  vertexShaderBuffer = nullptr;
  pixelShaderBuffer = nullptr;

  result = D3DCompileFromFile(vsFilename.c_str(), nullptr, nullptr, "PointLightVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
    &vertexShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, vsFilenameStdStr);
  }

  result = D3DCompileFromFile(psFilename.c_str(), NULL, NULL, "PointLightPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
    &pixelShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, psFilenameStdStr);
  }

  result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
  if (FAILED(result))
  {
    throw std::runtime_error("failed vertex shader creation " + vsFilenameStdStr);
  }

  result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
  if (FAILED(result))
  {
    throw std::runtime_error("failed pixel shader creation " + psFilenameStdStr);
  }

  polygonLayout[0].SemanticName = "POSITION";
  polygonLayout[0].SemanticIndex = 0;
  polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  polygonLayout[0].InputSlot = 0;
  polygonLayout[0].AlignedByteOffset = 0;
  polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[0].InstanceDataStepRate = 0;

  polygonLayout[1].SemanticName = "TEXCOORD";
  polygonLayout[1].SemanticIndex = 0;
  polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
  polygonLayout[1].InputSlot = 0;
  polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
  polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[1].InstanceDataStepRate = 0;

  // Get a count of the elements in the layout.
  numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

  // Create the vertex input layout.
  result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
    vertexShaderBuffer->GetBufferSize(), &m_layout);
  if (FAILED(result))
  {
    RUNTIME_ERROR("failed input layout creation " + vsFilenameStdStr);
  }

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
  result = device->CreateBuffer(&matrixBufferDesc, nullptr, &m_matrixBuffer);
  if (FAILED(result))
  {
    throw std::runtime_error("failed input create matrix buffer " + vsFilenameStdStr);
  }

  // Create a texture sampler state description.
  samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
  samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  samplerDesc.MipLODBias = 0.0f;
  samplerDesc.MaxAnisotropy = 1;
  samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
  samplerDesc.BorderColor[0] = 0;
  samplerDesc.BorderColor[1] = 0;
  samplerDesc.BorderColor[2] = 0;
  samplerDesc.BorderColor[3] = 0;
  samplerDesc.MinLOD = 0;
  samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

  // Create the texture sampler state.
  result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
  if (FAILED(result))
  {
    throw std::runtime_error("failed create sample state for texture " + vsFilenameStdStr);
  }

  worldCoordsUnpackBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  worldCoordsUnpackBufferDesc.ByteWidth = sizeof(WorldCoordsUnpackBuffer);
  worldCoordsUnpackBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  worldCoordsUnpackBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  worldCoordsUnpackBufferDesc.MiscFlags = 0;
  worldCoordsUnpackBufferDesc.StructureByteStride = 0;

  result = device->CreateBuffer(&worldCoordsUnpackBufferDesc, NULL, &m_worldCoordsUnpackBuffer);
  if (FAILED(result))
  {
    RUNTIME_ERROR("failed create buffer for world coord unpack data " + psFilenameStdStr);
  }

  // Setup the description of the light dynamic constant buffer that is in the pixel shader.
  // Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
  pointLightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  pointLightBufferDesc.ByteWidth = sizeof(PointLightBuffer);
  pointLightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  pointLightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  pointLightBufferDesc.MiscFlags = 0;
  pointLightBufferDesc.StructureByteStride = 0;

  // Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
  result = device->CreateBuffer(&pointLightBufferDesc, NULL, &m_pointLightBuffer);
  if (FAILED(result))
  {
    RUNTIME_ERROR("failed create buffer for lights " + psFilenameStdStr);
  }
}

void PointLightDefferedShader::ShutdownShader()
{
  TextureShader::ShutdownShader();

  if (m_worldCoordsUnpackBuffer)
  {
    m_worldCoordsUnpackBuffer->Release();
    m_worldCoordsUnpackBuffer = nullptr;
  }

  if (m_pointLightBuffer)
  {
    m_pointLightBuffer->Release();
    m_pointLightBuffer = nullptr;
  }
}

void PointLightDefferedShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
  XMMATRIX projectionMatrix, XMFLOAT3 pointLightColor, XMFLOAT3 pointLightPosition, float linearAttenuation, float quadraticAttenuation, XMVECTOR perspectiveValues, XMMATRIX viewMatrixInv)
{
  HRESULT result;
  D3D11_MAPPED_SUBRESOURCE mappedResource;
  unsigned int bufferNumber;
  MatrixBufferType* matrixBufferDataPtr;
  WorldCoordsUnpackBuffer* worldCoordsUnpackBuffer;
  PointLightBuffer* pointLightBufferDataPtr;

  // Transpose the matrices to prepare them for the shader.
  worldMatrix = XMMatrixTranspose(worldMatrix);
  viewMatrix = XMMatrixTranspose(viewMatrix);
  projectionMatrix = XMMatrixTranspose(projectionMatrix);

  // Lock the constant buffer so it can be written to.
  result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("cant lock the matrix constant buffer");

  // Get a pointer to the data in the constant buffer.
  matrixBufferDataPtr = (MatrixBufferType*)mappedResource.pData;

  // Copy the matrices into the constant buffer.
  matrixBufferDataPtr->world = worldMatrix;
  matrixBufferDataPtr->view = viewMatrix;
  matrixBufferDataPtr->projection = projectionMatrix;

  // Unlock the constant buffer.
  deviceContext->Unmap(m_matrixBuffer, 0);

  // Set the position of the constant buffer in the vertex shader.
  bufferNumber = 0;

  // Finanly set the constant buffer in the vertex shader with the updated values.
  deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

  result = deviceContext->Map(m_worldCoordsUnpackBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("cant lock the world pos unpack data constant buffer ");

  worldCoordsUnpackBuffer = (WorldCoordsUnpackBuffer*)mappedResource.pData;
  worldCoordsUnpackBuffer->perspectiveValues = perspectiveValues;
  worldCoordsUnpackBuffer->viewMatrixInverse = XMMatrixTranspose(viewMatrixInv);

  // Unlock the constant buffer.
  deviceContext->Unmap(m_worldCoordsUnpackBuffer, 0);

  bufferNumber = 0;

  // Finally set the light constant buffer in the pixel shader with the updated values.
  deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_worldCoordsUnpackBuffer);

  // Lock the light constant buffer so it can be written to.
  result = deviceContext->Map(m_pointLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("cant lock the light constant buffer ");

  // Get a pointer to the data in the constant buffer.
  pointLightBufferDataPtr = (PointLightBuffer*)mappedResource.pData;

  // Copy the lighting variables into the constant buffer.
  pointLightBufferDataPtr->color = pointLightColor;
  pointLightBufferDataPtr->linearAttenuation = linearAttenuation;
  pointLightBufferDataPtr->position = pointLightPosition;
  pointLightBufferDataPtr->quadraticAttenuation = quadraticAttenuation;

  // Unlock the constant buffer.
  deviceContext->Unmap(m_pointLightBuffer, 0);

  // Set the position of the light constant buffer in the pixel shader.
  bufferNumber = 1;

  // Finally set the light constant buffer in the pixel shader with the updated values.
  deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_pointLightBuffer);
}

void PointLightDefferedShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition)
{
  XMMATRIX pointLightWorldMatrix;
  XMVECTOR scale, rotation, position;
  XMFLOAT3 positionFloat3;

  auto pointLightDefferedParameters = (PointLightDefferedParameters *)material;

  auto pointLight = (*lightining->GetPointLights())[0];
  pointLight->GetWorldMatrix(pointLightWorldMatrix);
  XMMatrixDecompose(&scale, &rotation, &position, pointLightWorldMatrix);
  XMStoreFloat3(&positionFloat3, position);

  SetShaderParameters(deviceContext, pointLightWorldMatrix, viewMatrix, projectionMatrix, pointLight->GetColor(), positionFloat3, pointLight->GetLinearAttenuation(), pointLight->GetQuadraticAttenuation(), pointLightDefferedParameters->GetPerspectiveValues(), pointLightDefferedParameters->GetViewMatrixInverse());

  RenderShader(deviceContext, indexCount);
}