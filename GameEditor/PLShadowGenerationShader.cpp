#include "PLShadowGenerationShader.h"
#include "Logger.h"
#include "LightininigSystem.h"
#include "PointLight.h"

PLShadowGenerationShader::PLShadowGenerationShader()
{
  m_worldMatrixBuffer = nullptr;
  m_geometricShaderShadowBuffer = nullptr;
}


PLShadowGenerationShader::~PLShadowGenerationShader()
{
  ShutdownShader();
}

void PLShadowGenerationShader::InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename)
{
  HRESULT result;
  ID3D10Blob* errorMessage;
  ID3D10Blob* vertexShaderBuffer;
  ID3D10Blob* geometryShaderBuffer;
  D3D11_INPUT_ELEMENT_DESC polygonLayout[1];
  D3D11_BUFFER_DESC worldMatrixBufferDesc;
  D3D11_BUFFER_DESC shadowMapCubeBufferDesc;
  unsigned int numElements;
  std::string vsFilenameStdStr = Utils::UnicodeStrToByteStr(vsFilename);
  std::string gsFilenameStdStr = Utils::UnicodeStrToByteStr(gsFilename);

  errorMessage = nullptr;
  vertexShaderBuffer = nullptr;
  geometryShaderBuffer = nullptr;

  result = D3DCompileFromFile(vsFilename.c_str(), nullptr, nullptr, "PointShadowGenVS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
    &vertexShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, vsFilenameStdStr);
  }

  result = D3DCompileFromFile(gsFilename.c_str(), nullptr, nullptr, "PointShadowGenGS", "gs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &geometryShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, gsFilenameStdStr);
  }

  result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_vertexShader);
  if (FAILED(result))
    RUNTIME_ERROR("failed vertex shader creation " + vsFilenameStdStr);

  result = device->CreateGeometryShader(geometryShaderBuffer->GetBufferPointer(), geometryShaderBuffer->GetBufferSize(), nullptr, &m_geometricShader);
  if (FAILED(result))
    RUNTIME_ERROR("failed geometry shader creation " + gsFilenameStdStr);

  polygonLayout[0].SemanticName = "POSITION";
  polygonLayout[0].SemanticIndex = 0;
  polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
  polygonLayout[0].InputSlot = 0;
  polygonLayout[0].AlignedByteOffset = 0;
  polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
  polygonLayout[0].InstanceDataStepRate = 0;

  numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

  result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
    vertexShaderBuffer->GetBufferSize(), &m_layout);
  if (FAILED(result))
  {
    RUNTIME_ERROR("failed input layout creation " + vsFilenameStdStr);
  }

  vertexShaderBuffer->Release();
  vertexShaderBuffer = nullptr;

  geometryShaderBuffer->Release();
  geometryShaderBuffer = nullptr;

  worldMatrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  worldMatrixBufferDesc.ByteWidth = sizeof(WorldMatrixBuffer);
  worldMatrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  worldMatrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  worldMatrixBufferDesc.MiscFlags = 0;
  worldMatrixBufferDesc.StructureByteStride = 0;

  result = device->CreateBuffer(&worldMatrixBufferDesc, nullptr, &m_worldMatrixBuffer);
  if (FAILED(result))
    RUNTIME_ERROR("failed input create world matrix buffer " + vsFilenameStdStr);

  shadowMapCubeBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  shadowMapCubeBufferDesc.ByteWidth = sizeof(CubeViewProjectionsBuffer);
  shadowMapCubeBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  shadowMapCubeBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  shadowMapCubeBufferDesc.MiscFlags = 0;
  shadowMapCubeBufferDesc.StructureByteStride = 0;

  result = device->CreateBuffer(&shadowMapCubeBufferDesc, nullptr, &m_geometricShaderShadowBuffer);
  if (FAILED(result))
  {
    RUNTIME_ERROR("failed create shadow map cube buffer " + gsFilenameStdStr);
  }
}

void PLShadowGenerationShader::ShutdownShader()
{
  IShader::ShutdownShader();

  if (m_worldMatrixBuffer)
  {
    m_worldMatrixBuffer->Release();
    m_worldMatrixBuffer = nullptr;
  }

  if (m_geometricShaderShadowBuffer)
  {
    m_geometricShaderShadowBuffer->Release();
    m_geometricShaderShadowBuffer = nullptr;
  }
}

void PLShadowGenerationShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX* cubeViewProjections, const int* const shadowDirectionsArr, const int shadowDirectionsArrSize)
{
  HRESULT result;
  D3D11_MAPPED_SUBRESOURCE mappedResource;
  unsigned int bufferNumber;
  WorldMatrixBuffer* worldMatrixBufferDataPtr;
  CubeViewProjectionsBuffer* shadowMapCubeBufferDataPtr;

  result = deviceContext->Map(m_worldMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("can't lock the world matrix constant buffer");

  worldMatrixBufferDataPtr = (WorldMatrixBuffer*)mappedResource.pData;
  worldMatrixBufferDataPtr->worldMatrix = XMMatrixTranspose(worldMatrix);

  deviceContext->Unmap(m_worldMatrixBuffer, 0);

  bufferNumber = 0;

  deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_worldMatrixBuffer);

  result = deviceContext->Map(m_geometricShaderShadowBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("can't lock the geometric shader shadow constant buffer ");

  shadowMapCubeBufferDataPtr = (CubeViewProjectionsBuffer*)mappedResource.pData;
  for (int i = 0; i < 6; ++i)
  {
    shadowMapCubeBufferDataPtr->cubeViewProjections[i] = cubeViewProjections[i];
  }
  for (int i = 0; i < shadowDirectionsArrSize; ++i)
  {
    shadowMapCubeBufferDataPtr->shadowDirections[i].x = shadowDirectionsArr[i];
  }
  shadowMapCubeBufferDataPtr->shadowDirectionsSize.x = shadowDirectionsArrSize;

  deviceContext->Unmap(m_geometricShaderShadowBuffer, 0);
  bufferNumber = 0;
  deviceContext->GSSetConstantBuffers(bufferNumber, 1, &m_geometricShaderShadowBuffer);
}

void PLShadowGenerationShader::EnableShader(ID3D11DeviceContext* deviceContext)
{
  deviceContext->IASetInputLayout(m_layout);
  deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
  deviceContext->GSSetShader(m_geometricShader, nullptr, 0);
  deviceContext->HSSetShader(nullptr, nullptr, 0);
  deviceContext->DSSetShader(nullptr, nullptr, 0);
  deviceContext->PSSetShader(nullptr, nullptr, 0);
}

void PLShadowGenerationShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, const XMFLOAT3& cameraPosition)
{
  auto pointLight = lightining->GetPointLightToRender();
  SetShaderParameters(deviceContext, worldMatrix, pointLight->GetCubeViewProjection(), pointLight->GetShaderShadowDirectionsArr(), pointLight->GetShaderShadowDirectionsArrSize());
  deviceContext->DrawIndexed(indexCount, 0, 0);
}