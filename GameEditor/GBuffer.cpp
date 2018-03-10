#include "GBuffer.h"
#include "Logger.h"

GBuffer::GBuffer()
{
  for (int i = 0; i < BUFFER_COUNT; ++i)
  {
    m_renderTargetTextureArray[i] = nullptr;
    m_renderTargetViewArray[i] = nullptr;
  }

  for (int i = 0; i < SHADER_RESOURCE_VIEW_COUNT; ++i)
  {
    m_shaderResourceViewArray[i] = nullptr;
  }

  m_depthStencilBuffer = nullptr;
  m_depthStencilViewWriteable = nullptr;
  m_depthStencilViewReadonly = nullptr;
}


GBuffer::~GBuffer()
{
  Shutdown();
}

void GBuffer::Initialize(ID3D11Device* device, int textureWidth, int textureHeight)
{
  D3D11_TEXTURE2D_DESC textureDesc;
  HRESULT result;
  D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
  D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
  D3D11_TEXTURE2D_DESC depthBufferDesc;
  D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
  int normalBufferIndex = static_cast<int>(GBufferType::NORMAL);
  int i;

  // Store the width and height of the render texture.
  m_textureWidth = textureWidth;
  m_textureHeight = textureHeight;

  // Initialize the render target texture description.
  ZeroMemory(&textureDesc, sizeof(textureDesc));

  // Setup the render target texture description.
  textureDesc.Width = textureWidth;
  textureDesc.Height = textureHeight;
  textureDesc.MipLevels = 1;
  textureDesc.ArraySize = 1;
  textureDesc.Format = DXGI_FORMAT_R11G11B10_FLOAT;
  textureDesc.SampleDesc.Count = 1;
  textureDesc.Usage = D3D11_USAGE_DEFAULT;
  textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
  textureDesc.CPUAccessFlags = 0;
  textureDesc.MiscFlags = 0;

  result = device->CreateTexture2D(&textureDesc, NULL, &m_renderTargetTextureArray[normalBufferIndex]);
  if (FAILED(result))
    RUNTIME_ERROR("Creation of buffer texture failed!");

  textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

  // Create the render target textures.
  for (i = 1; i < BUFFER_COUNT; ++i)
  {
    result = device->CreateTexture2D(&textureDesc, NULL, &m_renderTargetTextureArray[i]);
    if (FAILED(result))
      RUNTIME_ERROR("Creation of buffer texture failed!");
  }

  // Setup the description of the render target view.
  renderTargetViewDesc.Format = DXGI_FORMAT_R11G11B10_FLOAT;
  renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
  renderTargetViewDesc.Texture2D.MipSlice = 0;

  result = device->CreateRenderTargetView(m_renderTargetTextureArray[normalBufferIndex], &renderTargetViewDesc, &m_renderTargetViewArray[normalBufferIndex]);
  if (FAILED(result))
    RUNTIME_ERROR("Creation of render target view failed!");

  renderTargetViewDesc.Format = textureDesc.Format;

  // Create the render target views.
  for (i = 1; i < BUFFER_COUNT; ++i)
  {
    result = device->CreateRenderTargetView(m_renderTargetTextureArray[i], &renderTargetViewDesc, &m_renderTargetViewArray[i]);
    if (FAILED(result))
      RUNTIME_ERROR("Creation of render target view failed!");
  }

  // Setup the description of the shader resource view.
  shaderResourceViewDesc.Format = DXGI_FORMAT_R11G11B10_FLOAT;
  shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
  shaderResourceViewDesc.Texture2D.MipLevels = 1;

  result = device->CreateShaderResourceView(m_renderTargetTextureArray[normalBufferIndex], &shaderResourceViewDesc, &m_shaderResourceViewArray[normalBufferIndex]);
  if (FAILED(result))
    RUNTIME_ERROR("Creation of shader resource view failed!");

  shaderResourceViewDesc.Format = textureDesc.Format;

  // Create the shader resource views.
  for (i = 1; i < BUFFER_COUNT; ++i)
  {
    result = device->CreateShaderResourceView(m_renderTargetTextureArray[i], &shaderResourceViewDesc, &m_shaderResourceViewArray[i]);
    if (FAILED(result))
      RUNTIME_ERROR("Creation of shader resource view failed!");
  }

  // Initialize the description of the depth buffer.
  ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

  // Set up the description of the depth buffer.
  depthBufferDesc.Width = textureWidth;
  depthBufferDesc.Height = textureHeight;
  depthBufferDesc.MipLevels = 1;
  depthBufferDesc.ArraySize = 1;
  depthBufferDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
  depthBufferDesc.SampleDesc.Count = 1;
  depthBufferDesc.SampleDesc.Quality = 0;
  depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
  depthBufferDesc.CPUAccessFlags = 0;
  depthBufferDesc.MiscFlags = 0;

  // Create the texture for the depth buffer using the filled out description.
  result = device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
  if (FAILED(result))
  {
    RUNTIME_ERROR("Creation of the texture for depth stencil buffer failed!");
  }

  // Initailze the depth stencil view description.
  ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

  // Set up the depth stencil view description.
  depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  depthStencilViewDesc.Texture2D.MipSlice = 0;

  // Create the depth stencil view.
  result = device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilViewWriteable);
  if (FAILED(result))
    RUNTIME_ERROR("Creation of the depth stencil view failed!");

  depthStencilViewDesc.Flags = D3D11_DSV_READ_ONLY_DEPTH | D3D11_DSV_READ_ONLY_STENCIL;
  result = device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilViewReadonly);

  shaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
  shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
  shaderResourceViewDesc.Texture2D.MipLevels = -1;

  result = device->CreateShaderResourceView(m_depthStencilBuffer, &shaderResourceViewDesc, &m_shaderResourceViewArray[SHADER_RESOURCE_VIEW_COUNT - 1]);
  if (FAILED(result))
    RUNTIME_ERROR("Creation of depth buffer shader resource view failed!");

  // Setup the viewport for rendering.
  m_viewport.Width = (float)textureWidth;
  m_viewport.Height = (float)textureHeight;
  m_viewport.MinDepth = 0.0f;
  m_viewport.MaxDepth = 1.0f;
  m_viewport.TopLeftX = 0.0f;
  m_viewport.TopLeftY = 0.0f;
}

void GBuffer::Shutdown()
{
  int i;

  if (m_depthStencilViewReadonly)
  {
    m_depthStencilViewReadonly->Release();
    m_depthStencilViewReadonly = nullptr;
  }

  if (m_depthStencilViewWriteable)
  {
    m_depthStencilViewWriteable->Release();
    m_depthStencilViewWriteable = nullptr;
  }

  if (m_depthStencilBuffer)
  {
    m_depthStencilBuffer->Release();
    m_depthStencilBuffer = nullptr;
  }

  for (i = 0; i < SHADER_RESOURCE_VIEW_COUNT; ++i)
  {
    if (m_shaderResourceViewArray[i])
    {
      m_shaderResourceViewArray[i]->Release();
      m_shaderResourceViewArray[i] = nullptr;
    }
  }

  for (i = 0; i < BUFFER_COUNT; ++i)
  {
    if (m_renderTargetViewArray[i])
    {
      m_renderTargetViewArray[i]->Release();
      m_renderTargetViewArray[i] = nullptr;
    }

    if (m_renderTargetTextureArray[i])
    {
      m_renderTargetTextureArray[i]->Release();
      m_renderTargetTextureArray[i] = nullptr;
    }
  }
}

void GBuffer::SetRenderTargets(ID3D11DeviceContext* deviceContext)
{
  // Bind the render target view array and depth stencil buffer to the output render pipeline.
  deviceContext->OMSetRenderTargets(BUFFER_COUNT, m_renderTargetViewArray, m_depthStencilViewWriteable);

  // Set the viewport.
  deviceContext->RSSetViewports(1, &m_viewport);
}

void GBuffer::ClearRenderTargets(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha)
{
  float color[4];
  int i;


  // Setup the color to clear the buffer to.
  color[0] = red;
  color[1] = green;
  color[2] = blue;
  color[3] = alpha;

  // Clear the render target buffers.
  for (i = 0; i < BUFFER_COUNT; ++i)
  {
    deviceContext->ClearRenderTargetView(m_renderTargetViewArray[i], color);
  }

  deviceContext->ClearDepthStencilView(m_depthStencilViewWriteable, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

ID3D11ShaderResourceView* GBuffer::GetShaderResourceView(int index)
{
  return m_shaderResourceViewArray[index];
}