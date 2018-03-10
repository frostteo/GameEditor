#include "BumpDefferedShader.h"
#include "Logger.h"

BumpDefferedShader::BumpDefferedShader()
{
  m_materialBuffer = nullptr;
}


BumpDefferedShader::~BumpDefferedShader()
{
  ShutdownShader();
}

void BumpDefferedShader::InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename)
{
  HRESULT result;
  ID3D10Blob* errorMessage;
  ID3D10Blob* vertexShaderBuffer;
  ID3D10Blob* pixelShaderBuffer;

  D3D11_INPUT_ELEMENT_DESC polygonLayout[5];
  unsigned int numElements;
  D3D11_BUFFER_DESC matrixBufferDesc;
  D3D11_SAMPLER_DESC samplerDesc;
  D3D11_BUFFER_DESC materialBufferDesc;
  std::string vsFilenameStdStr = Utils::UnicodeStrToByteStr(vsFilename);
  std::string psFilenameStdStr = Utils::UnicodeStrToByteStr(psFilename);

  // Initialize the pointers this function will use to null.
  errorMessage = nullptr;
  vertexShaderBuffer = nullptr;
  pixelShaderBuffer = nullptr;

  // Compile the vertex shader code.
  result = D3DCompileFromFile(vsFilename.c_str(), NULL, NULL, "BumpMapVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS,
    0, &vertexShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, vsFilenameStdStr);
  }

  // Compile the pixel shader code.
  result = D3DCompileFromFile(psFilename.c_str(), NULL, NULL, "BumpMapPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS,
    0, &pixelShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, psFilenameStdStr);
  }

  // Create the vertex shader from the buffer.
  result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL,
    &m_vertexShader);
  if (FAILED(result))
    RUNTIME_ERROR("failed vertex shader creation " + vsFilenameStdStr);

  // Create the vertex shader from the buffer.
  result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL,
    &m_pixelShader);
  if (FAILED(result))
    RUNTIME_ERROR("failed pixel shader creation " + psFilenameStdStr);

  // Create the vertex input layout description.
  // This setup needs to match the VertexType stucture in the ModelClass and in the shader.
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

  polygonLayout[2].SemanticName = "NORMAL";
  polygonLayout[2].SemanticIndex = 0;
  polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  polygonLayout[2].InputSlot = 0;
  polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
  polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[2].InstanceDataStepRate = 0;

  polygonLayout[3].SemanticName = "TANGENT";
  polygonLayout[3].SemanticIndex = 0;
  polygonLayout[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  polygonLayout[3].InputSlot = 0;
  polygonLayout[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
  polygonLayout[3].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[3].InstanceDataStepRate = 0;

  polygonLayout[4].SemanticName = "BINORMAL";
  polygonLayout[4].SemanticIndex = 0;
  polygonLayout[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  polygonLayout[4].InputSlot = 0;
  polygonLayout[4].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
  polygonLayout[4].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[4].InstanceDataStepRate = 0;

  // Get a count of the elements in the layout.
  numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

  // Create the vertex input layout.
  result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
    vertexShaderBuffer->GetBufferSize(), &m_layout);
  if (FAILED(result))
    RUNTIME_ERROR("failed input layout creation " + vsFilenameStdStr);

  // Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
  vertexShaderBuffer->Release();
  vertexShaderBuffer = nullptr;

  pixelShaderBuffer->Release();
  pixelShaderBuffer = nullptr;

  // Setup the description of the matrix dynamic constant buffer that is in the vertex shader.
  matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
  matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  matrixBufferDesc.MiscFlags = 0;
  matrixBufferDesc.StructureByteStride = 0;

  // Create the matrix constant buffer pointer so we can access the vertex shader constant buffer from within this class.
  result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
  if (FAILED(result))
    RUNTIME_ERROR("failed input create matrix buffer " + vsFilenameStdStr);

  // Create a texture sampler state description.
  samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
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
    RUNTIME_ERROR("failed create sample state for texture " + vsFilenameStdStr);

  // Setup the description of the light dynamic constant buffer that is in the pixel shader.
  materialBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  materialBufferDesc.ByteWidth = sizeof(MaterialBufferType);
  materialBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  materialBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  materialBufferDesc.MiscFlags = 0;
  materialBufferDesc.StructureByteStride = 0;

  // Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
  result = device->CreateBuffer(&materialBufferDesc, NULL, &m_materialBuffer);
  if (FAILED(result))
    RUNTIME_ERROR("failed create buffer for material " + vsFilenameStdStr);
}

void BumpDefferedShader::ShutdownShader()
{
  TextureShader::ShutdownShader();

  if (m_materialBuffer)
  {
    m_materialBuffer->Release();
    m_materialBuffer = nullptr;
  }
}

void BumpDefferedShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix,
  XMMATRIX viewMatrix, XMMATRIX projectionMatrix, float bumpDepth)
{
  HRESULT result;
  D3D11_MAPPED_SUBRESOURCE mappedResource;
  MatrixBufferType* matrixBufferPtr;
  unsigned int bufferNumber;
  MaterialBufferType* materialBufferPtr;


  // Transpose the matrices to prepare them for the shader.
  worldMatrix = XMMatrixTranspose(worldMatrix);
  viewMatrix = XMMatrixTranspose(viewMatrix);
  projectionMatrix = XMMatrixTranspose(projectionMatrix);

  // Lock the matrix constant buffer so it can be written to.
  result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("cant lock the matrix constant buffer");

  // Get a pointer to the data in the constant buffer.
  matrixBufferPtr = (MatrixBufferType*)mappedResource.pData;

  // Copy the matrices into the constant buffer.
  matrixBufferPtr->world = worldMatrix;
  matrixBufferPtr->view = viewMatrix;
  matrixBufferPtr->projection = projectionMatrix;

  // Unlock the matrix constant buffer.
  deviceContext->Unmap(m_matrixBuffer, 0);

  // Set the position of the matrix constant buffer in the vertex shader.
  bufferNumber = 0;

  // Now set the matrix constant buffer in the vertex shader with the updated values.
  deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

  // Lock the light constant buffer so it can be written to.
  result = deviceContext->Map(m_materialBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("cant lock the light constant buffer ");

  // Get a pointer to the data in the constant buffer.
  materialBufferPtr = (MaterialBufferType*)mappedResource.pData;

  // Copy the lighting variables into the constant buffer.
  materialBufferPtr->bumpDepth = bumpDepth;

  // Unlock the constant buffer.
  deviceContext->Unmap(m_materialBuffer, 0);

  // Set the position of the light constant buffer in the pixel shader.
  bufferNumber = 0;

  // Finally set the light constant buffer in the pixel shader with the updated values.
  deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_materialBuffer);
}

void BumpDefferedShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
  XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition)
{
  BumpMaterial* bumpMaterial = (BumpMaterial*)material;

  SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, bumpMaterial->m_bumpDepth);

  RenderShader(deviceContext, indexCount);
}