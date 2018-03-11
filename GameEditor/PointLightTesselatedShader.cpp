#include "PointLightTesselatedShader.h"
#include "Logger.h"
#include "LightininigSystem.h"
#include "PointLight.h"

PointLightTesselatedShader::PointLightTesselatedShader()
{
  m_lightProjectionBuffer = nullptr;
  m_worldCoordsUnpackBuffer = nullptr;
  m_pointLightBuffer = nullptr;
}


PointLightTesselatedShader::~PointLightTesselatedShader()
{
  ShutdownShader();
}

void PointLightTesselatedShader::ShutdownShader()
{
  IShader::ShutdownShader();

  if (m_lightProjectionBuffer)
  {
    m_lightProjectionBuffer->Release();
    m_lightProjectionBuffer = nullptr;
  }

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

void PointLightTesselatedShader::InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hsFilename, const std::wstring& dsFileName, const std::wstring& psFilename)
{
  HRESULT result;
  ID3D10Blob* errorMessage;
  ID3D10Blob* vertexShaderBuffer;
  ID3D10Blob* hullShaderBuffer;
  ID3D10Blob* domainShaderBuffer;
  ID3D10Blob* pixelShaderBuffer;
  D3D11_BUFFER_DESC lightProjectionBufferDesc;
  D3D11_BUFFER_DESC worldCoordsUnpackBufferDesc;
  D3D11_BUFFER_DESC pointLightBufferDesc;
  unsigned int numElements;
  std::string vsFilenameStdStr = Utils::UnicodeStrToByteStr(vsFilename);
  std::string hsFilenameStdStr = Utils::UnicodeStrToByteStr(hsFilename);
  std::string dsFilenameStdStr = Utils::UnicodeStrToByteStr(dsFileName);
  std::string psFilenameStdStr = Utils::UnicodeStrToByteStr(psFilename);

  errorMessage = nullptr;
  vertexShaderBuffer = nullptr;
  hullShaderBuffer = nullptr;
  domainShaderBuffer = nullptr;
  pixelShaderBuffer = nullptr;

  result = D3DCompileFromFile(vsFilename.c_str(), nullptr, nullptr, "PointLightVS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
    &vertexShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
      OutputShaderErrorMessage(errorMessage, vsFilenameStdStr);
  }

  result = D3DCompileFromFile(hsFilename.c_str(), nullptr, nullptr, "PointLightHS", "hs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &hullShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, hsFilenameStdStr);
  }

  result = D3DCompileFromFile(dsFileName.c_str(), nullptr, nullptr, "PointLightDS", "ds_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &domainShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, dsFilenameStdStr);
  }

  result = D3DCompileFromFile(psFilename.c_str(), nullptr, nullptr, "PointLightPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
    &pixelShaderBuffer, &errorMessage);
  if (FAILED(result))
  {
    OutputShaderErrorMessage(errorMessage, psFilenameStdStr);
  }

  result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_vertexShader);
  if (FAILED(result))
    RUNTIME_ERROR("failed vertex shader creation " + vsFilenameStdStr);

  result = device->CreateHullShader(hullShaderBuffer->GetBufferPointer(), hullShaderBuffer->GetBufferSize(), nullptr, &m_hullShader);
  if (FAILED(result))
    RUNTIME_ERROR("failed vertex shader creation " + hsFilenameStdStr);

  result = device->CreateDomainShader(domainShaderBuffer->GetBufferPointer(), domainShaderBuffer->GetBufferSize(), nullptr, &m_domainShader);
  if (FAILED(result))
    RUNTIME_ERROR("failed vertex shader creation " + dsFilenameStdStr);

  result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_pixelShader);
  if (FAILED(result))
    RUNTIME_ERROR("failed pixel shader creation " + psFilenameStdStr);

  vertexShaderBuffer->Release();
  vertexShaderBuffer = nullptr;

  hullShaderBuffer->Release();
  hullShaderBuffer = nullptr;

  domainShaderBuffer->Release();
  domainShaderBuffer = nullptr;

  pixelShaderBuffer->Release();
  pixelShaderBuffer = nullptr;

  lightProjectionBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  lightProjectionBufferDesc.ByteWidth = sizeof(LightProjectionBuffer);
  lightProjectionBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  lightProjectionBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  lightProjectionBufferDesc.MiscFlags = 0;
  lightProjectionBufferDesc.StructureByteStride = 0;

  result = device->CreateBuffer(&lightProjectionBufferDesc, nullptr, &m_lightProjectionBuffer);
  if (FAILED(result))
    RUNTIME_ERROR("failed input create light projection buffer " + dsFilenameStdStr);

  worldCoordsUnpackBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  worldCoordsUnpackBufferDesc.ByteWidth = sizeof(WorldCoordsUnpackBuffer);
  worldCoordsUnpackBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  worldCoordsUnpackBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  worldCoordsUnpackBufferDesc.MiscFlags = 0;
  worldCoordsUnpackBufferDesc.StructureByteStride = 0;

  result = device->CreateBuffer(&worldCoordsUnpackBufferDesc, nullptr, &m_worldCoordsUnpackBuffer);
  if (FAILED(result))
  {
    RUNTIME_ERROR("failed create buffer for world coord unpack data " + psFilenameStdStr);
  }

  pointLightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  pointLightBufferDesc.ByteWidth = sizeof(PointLightBuffer);
  pointLightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  pointLightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  pointLightBufferDesc.MiscFlags = 0;
  pointLightBufferDesc.StructureByteStride = 0;

  result = device->CreateBuffer(&pointLightBufferDesc, nullptr, &m_pointLightBuffer);
  if (FAILED(result))
  {
    RUNTIME_ERROR("failed create buffer for lights " + psFilenameStdStr);
  }
}

void PointLightTesselatedShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX lightProjection, XMFLOAT3 pointLightColor, XMFLOAT3 pointLightPosition, float linearAttenuation, float quadraticAttenuation, XMVECTOR perspectiveValues, XMMATRIX viewMatrixInv)
{
  HRESULT result;
  D3D11_MAPPED_SUBRESOURCE mappedResource;
  unsigned int bufferNumber;
  LightProjectionBuffer* lightProjectionBufferDataPtr;
  WorldCoordsUnpackBuffer* worldCoordsUnpackBufferDataPtr;
  PointLightBuffer* pointLightBufferDataPtr;

  result = deviceContext->Map(m_lightProjectionBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("can't lock the light projection constant buffer");

  lightProjectionBufferDataPtr = (LightProjectionBuffer*)mappedResource.pData;
  lightProjectionBufferDataPtr->LightProjection = XMMatrixTranspose(lightProjection);

  deviceContext->Unmap(m_lightProjectionBuffer, 0);

  bufferNumber = 0;

  deviceContext->DSSetConstantBuffers(bufferNumber, 1, &m_lightProjectionBuffer);

  result = deviceContext->Map(m_worldCoordsUnpackBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("can't lock the world pos unpack data constant buffer ");

  worldCoordsUnpackBufferDataPtr = (WorldCoordsUnpackBuffer*)mappedResource.pData;
  worldCoordsUnpackBufferDataPtr->perspectiveValues = perspectiveValues;
  worldCoordsUnpackBufferDataPtr->viewMatrixInverse = XMMatrixTranspose(viewMatrixInv);

  deviceContext->Unmap(m_worldCoordsUnpackBuffer, 0);

  bufferNumber = 0;

  deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_worldCoordsUnpackBuffer);

  result = deviceContext->Map(m_pointLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
  if (FAILED(result))
    RUNTIME_ERROR("can't lock the light constant buffer ");

  pointLightBufferDataPtr = (PointLightBuffer*)mappedResource.pData;
  pointLightBufferDataPtr->color = pointLightColor;
  pointLightBufferDataPtr->linearAttenuation = linearAttenuation;
  pointLightBufferDataPtr->position = pointLightPosition;
  pointLightBufferDataPtr->quadraticAttenuation = quadraticAttenuation;

  deviceContext->Unmap(m_pointLightBuffer, 0);

  bufferNumber = 1;

  deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_pointLightBuffer);
}

void PointLightTesselatedShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, const IMaterial* material, LightininigSystem* lightining, const XMFLOAT3& cameraPosition)
{
  XMMATRIX pointLightWorldMatrix;
  XMMATRIX pointLightProjection;
  XMFLOAT3 worldPosition;

  auto pointLightDefferedParameters = (PointLightDefferedParameters *) material;

  auto pointLight = lightining->GetPointLightToRender();
  pointLight->GetWorldMatrix(pointLightWorldMatrix);
  pointLightProjection = pointLightWorldMatrix * viewMatrix * projectionMatrix;
  
  worldPosition = pointLight->GetWorldPosition();

  SetShaderParameters(deviceContext, pointLightProjection, pointLight->GetColor(), worldPosition, pointLight->GetLinearAttenuation(), pointLight->GetQuadraticAttenuation(), pointLightDefferedParameters->GetPerspectiveValues(), pointLightDefferedParameters->GetViewMatrixInverse());

  deviceContext->Draw(2, 0);
}

void PointLightTesselatedShader::EnableShader(ID3D11DeviceContext* deviceContext)
{
  deviceContext->IASetInputLayout(nullptr);
  deviceContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST);

  deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
  deviceContext->GSSetShader(nullptr, nullptr, 0);
  deviceContext->HSSetShader(m_hullShader, nullptr, 0);
  deviceContext->DSSetShader(m_domainShader, nullptr, 0);
  deviceContext->PSSetShader(m_pixelShader, nullptr, 0);
}