
#include "D3DConfigurer.h"

const int D3DConfigurer::SHADOW_MAP_SIZE = 1024.0f;

D3DConfigurer::D3DConfigurer()
{
  m_swapChain = nullptr;
  m_device = nullptr;
  m_deviceContext = nullptr;
  m_renderTargetView = nullptr;
  m_depthStencilBuffer = nullptr;
  m_depthStencilState = nullptr;
  m_depthStencilView = nullptr;
  
  m_depthDisabledStencilState = nullptr;
  m_alphaEnableBlendingState = nullptr;
  m_alphaDisableBlendingState = nullptr;
  m_additiveBlendingState = nullptr;

  m_cullNoneRasterState = nullptr;
  m_cullFrontRasterState = nullptr;
  m_cullBackRasterState = nullptr;

  m_depthStencilLightVolumeState = nullptr;
  m_depthStencilDefferedLightState = nullptr;

  m_gbuffer = nullptr;

  m_pointLightShadowRS = nullptr;
  m_pointLightShadowDepthBuffer = nullptr;
  m_pointLightShadowDSV = nullptr;
  m_pointLightShadowSRV = nullptr;
}


D3DConfigurer::~D3DConfigurer()
{
  Shutdown();
}

bool D3DConfigurer::Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen)
{
  HRESULT result;
  IDXGIFactory* factory;
  IDXGIAdapter* adapter;
  IDXGIOutput* adapterOutput;
  unsigned int numModes, i, numerator, denominator;
  size_t stringLength;
  DXGI_MODE_DESC* displayModeList;
  DXGI_ADAPTER_DESC adapterDesc;
  int error;
  DXGI_SWAP_CHAIN_DESC swapChainDesc;
  D3D_FEATURE_LEVEL featureLevel;
  ID3D11Texture2D* backBufferPtr;
  D3D11_TEXTURE2D_DESC depthBufferDesc;
  D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
  D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
  D3D11_RASTERIZER_DESC rasterDesc;
  D3D11_VIEWPORT viewport;
  D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
  D3D11_BLEND_DESC blendStateDescription;

  const int byteToMegaByteMultiplier = 1048576; //TODO FHolod: Bytes converter can be realised later

  // Store the vsync setting.
  m_vsync_enabled = vsync;

  // Create a DirectX graphics interface factory.
  result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
  if (FAILED(result))
  {
    Logger::get().LogMessage("can't create dxgi factory", __FILE__, __LINE__);
    return false;
  }

  // Use the factory to create an adapter for the primary graphics interface (video card).
  result = factory->EnumAdapters(0, &adapter);
  if (FAILED(result))
  {
    Logger::get().LogMessage("cant create an adapter for the primary graphics interface", __FILE__, __LINE__);
    return false;
  }

  // Enumerate the primary adapter output (monitor).
  result = adapter->EnumOutputs(0, &adapterOutput);
  if (FAILED(result))
  {
    Logger::get().LogMessage("cant Enumerate the primary adapter output", __FILE__, __LINE__);
    return false;
  }

  // Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
  result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
  if (FAILED(result))
  {
    Logger::get().LogMessage("cant get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM", __FILE__, __LINE__);
    return false;
  }

  // Create a list to hold all the possible display modes for this monitor/video card combination.
  displayModeList = new DXGI_MODE_DESC[numModes];
  if (!displayModeList)
  {
    Logger::get().LogMessage("cant create a list to hold all the possible display modes for this monitor/video card combination", __FILE__, __LINE__);
    return false;
  }

  // Now fill the display mode list structures.
  result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
  if (FAILED(result))
  {
    Logger::get().LogMessage("cant fill the display mode list structures", __FILE__, __LINE__);
    return false;
  }

  // Now go through all the display modes and find the one that matches the screen width and height.
  // When a match is found store the numerator and denominator of the refresh rate for that monitor.
  for (i = 0; i < numModes; i++)
  {
    if (displayModeList[i].Width == (unsigned int)screenWidth &&
      displayModeList[i].Height == (unsigned int)screenHeight)
    {
      numerator = displayModeList[i].RefreshRate.Numerator;
      denominator = displayModeList[i].RefreshRate.Denominator;
    }
  }

  // Get the adapter (video card) description.
  result = adapter->GetDesc(&adapterDesc);
  if (FAILED(result))
  {
    Logger::get().LogMessage("cant get the adapter (video card) description", __FILE__, __LINE__);
    return false;
  }

  // Store the dedicated video card memory in megabytes.
  m_videoCardMemorySize = (int)(adapterDesc.DedicatedVideoMemory / byteToMegaByteMultiplier);


  // Convert the name of the video card to a character array and store it.
  m_videoCardDescription = adapterDesc.Description;

  // Release the display mode list.
  delete[] displayModeList;
  displayModeList = nullptr;

  // Release the adapter output.
  adapterOutput->Release();
  adapterOutput = nullptr;

  // Release the adapter.
  adapter->Release();
  adapter = nullptr;

  // Release the factory.
  factory->Release();
  factory = nullptr;

  // Initialize the swap chain description.
  ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

  // Set to a single back buffer.
  swapChainDesc.BufferCount = 1;

  // Set the width and height of the back buffer.
  swapChainDesc.BufferDesc.Width = screenWidth;
  swapChainDesc.BufferDesc.Height = screenHeight;

  // Set regular 32-bit surface for the back buffer.
  swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

  // Set the refresh rate of the back buffer.
  if (m_vsync_enabled)
  {
    swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
  }
  else
  {
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
  }

  // Set the usage of the back buffer.
  swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

  // Set the handle for the window to render to.
  swapChainDesc.OutputWindow = hwnd;

  // Turn multisampling off.
  swapChainDesc.SampleDesc.Count = 1;
  swapChainDesc.SampleDesc.Quality = 0;

  // Set to full screen or windowed mode.
  if (fullscreen)
  {
    swapChainDesc.Windowed = false;
  }
  else
  {
    swapChainDesc.Windowed = true;
  }

  // Set the scan line ordering and scaling to unspecified.
  swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

  // Discard the back buffer contents after presenting.
  swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  // Don't set the advanced flags.
  swapChainDesc.Flags = 0;

  // Set the feature level to DirectX 11.
  featureLevel = D3D_FEATURE_LEVEL_11_0;

  // Create the swap chain, Direct3D device, and Direct3D device context.
  result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1,
    D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContext);
  if (FAILED(result))
  {
    return false;
  }

  // Get the pointer to the back buffer.
  result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
  if (FAILED(result))
  {
    return false;
  }

  // Create the render target view with the back buffer pointer.
  result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
  if (FAILED(result))
  {
    return false;
  }

  // Release pointer to the back buffer as we no longer need it.
  backBufferPtr->Release();
  backBufferPtr = nullptr;

  // Initialize the description of the depth buffer.
  ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

  // Set up the description of the depth buffer.
  depthBufferDesc.Width = screenWidth;
  depthBufferDesc.Height = screenHeight;
  depthBufferDesc.MipLevels = 1;
  depthBufferDesc.ArraySize = 1;
  depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthBufferDesc.SampleDesc.Count = 1;
  depthBufferDesc.SampleDesc.Quality = 0;
  depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  depthBufferDesc.CPUAccessFlags = 0;
  depthBufferDesc.MiscFlags = 0;

  // Create the texture for the depth buffer using the filled out description.
  result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
  if (FAILED(result))
  {
    return false;
  }

  // Initialize the description of the stencil state.
  ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

  // Set up the description of the stencil state.
  depthStencilDesc.DepthEnable = true;
  depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
  depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

  depthStencilDesc.StencilEnable = false;
  depthStencilDesc.StencilReadMask = 0xFF;
  depthStencilDesc.StencilWriteMask = 0xFF;

  // Stencil operations if pixel is front-facing.
  depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

  // Stencil operations if pixel is back-facing.
  depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

  // Create the depth stencil state.
  result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
  if (FAILED(result))
  {
    return false;
  }

  // Set the depth stencil state.
  m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 0);

  // Initialize the depth stencil view.
  ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

  // Set up the depth stencil view description.
  depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  depthStencilViewDesc.Texture2D.MipSlice = 0;

  // Create the depth stencil view.
  result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
  if (FAILED(result))
  {
    return false;
  }

  // Bind the render target view and depth stencil buffer to the output render pipeline.
  m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

  // Setup the raster description which will determine how and what polygons will be drawn.
  rasterDesc.AntialiasedLineEnable = true;
  rasterDesc.CullMode = D3D11_CULL_BACK;
  rasterDesc.DepthBias = 0;
  rasterDesc.DepthBiasClamp = 0.0f;
  rasterDesc.DepthClipEnable = true;
  rasterDesc.FillMode = D3D11_FILL_SOLID;
  rasterDesc.FrontCounterClockwise = false;
  rasterDesc.MultisampleEnable = true;
  rasterDesc.ScissorEnable = false;
  rasterDesc.SlopeScaledDepthBias = 0.0f;

  result = m_device->CreateRasterizerState(&rasterDesc, &m_cullBackRasterState);
  if (FAILED(result))
    RUNTIME_ERROR("Cant create cull back raster state");

  rasterDesc.CullMode = D3D11_CULL_FRONT;
  result = m_device->CreateRasterizerState(&rasterDesc, &m_cullFrontRasterState);
  if (FAILED(result))
    RUNTIME_ERROR("Cant create cull front raster state");

  rasterDesc.CullMode = D3D11_CULL_NONE;
  result = m_device->CreateRasterizerState(&rasterDesc, &m_cullNoneRasterState);
  if (FAILED(result))
    RUNTIME_ERROR("Cant create cull none raster state");

  // Now set the rasterizer state.
  m_deviceContext->RSSetState(m_cullBackRasterState);

  // Clear the second depth stencil state before setting the parameters.
  ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

  // Now create a second depth stencil state which turns off the Z buffer for 2D rendering.  The only difference is 
  // that DepthEnable is set to false, all other parameters are the same as the other depth stencil state.
  depthDisabledStencilDesc.DepthEnable = false;
  depthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
  depthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
  depthDisabledStencilDesc.StencilEnable = false;
  depthDisabledStencilDesc.StencilReadMask = 0xFF;
  depthDisabledStencilDesc.StencilWriteMask = 0xFF;
  depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
  depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
  depthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
  depthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

  // Create the state using the device.
  result = m_device->CreateDepthStencilState(&depthDisabledStencilDesc, &m_depthDisabledStencilState);
  if (FAILED(result))
  {
    return false;
  }

  // Clear the blend state description.
  ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));

  // Create an alpha enabled blend state description.
  blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
  blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
  blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;

  // Create the blend state using the description.
  result = m_device->CreateBlendState(&blendStateDescription, &m_alphaEnableBlendingState);
  if (FAILED(result))
  {
    return false;
  }

  // Modify the description to create an alpha disabled blend state description.
  blendStateDescription.RenderTarget[0].BlendEnable = FALSE;

  // Create the blend state using the description.
  result = m_device->CreateBlendState(&blendStateDescription, &m_alphaDisableBlendingState);
  if (FAILED(result))
  {
    return false;
  }

  blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
  blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
  blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
  blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
  blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;

  result = m_device->CreateBlendState(&blendStateDescription, &m_additiveBlendingState);
  if (FAILED(result))
  {
    return false;
  }

  m_viewport.Width = (float)screenWidth;
  m_viewport.Height = (float)screenHeight;
  m_viewport.MinDepth = 0.0f;
  m_viewport.MaxDepth = 1.0f;
  m_viewport.TopLeftX = 0.0f;
  m_viewport.TopLeftY = 0.0f;

  m_deviceContext->RSSetViewports(1, &m_viewport);

  InitializeDefferedLightingStructures();
  InitializePointLightShadowStructures();

  m_gbuffer = std::unique_ptr<GBuffer>(new GBuffer());
  m_gbuffer->Initialize(m_device, screenWidth, screenHeight);

  return true;
}

void D3DConfigurer::InitializePointLightShadowStructures()
{
  D3D11_RASTERIZER_DESC pointLightShadowRSDesc;
  D3D11_TEXTURE2D_DESC pointLightShadowDepthBufferDesc;
  D3D11_DEPTH_STENCIL_VIEW_DESC pointLightShadowDSVDesc;
  D3D11_SHADER_RESOURCE_VIEW_DESC pointLightShadowSRVDesc;
  bool result;

  pointLightShadowRSDesc.FillMode = D3D11_FILL_SOLID;
  pointLightShadowRSDesc.CullMode = D3D11_CULL_BACK;
  pointLightShadowRSDesc.FrontCounterClockwise = FALSE;
  pointLightShadowRSDesc.DepthBias = 85;
  pointLightShadowRSDesc.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
  pointLightShadowRSDesc.SlopeScaledDepthBias = 15.0f;
  pointLightShadowRSDesc.DepthClipEnable = TRUE;
  pointLightShadowRSDesc.ScissorEnable = FALSE;
  pointLightShadowRSDesc.MultisampleEnable = FALSE;
  pointLightShadowRSDesc.AntialiasedLineEnable = FALSE;

  m_device->CreateRasterizerState(&pointLightShadowRSDesc, &m_pointLightShadowRS);

  ZeroMemory(&pointLightShadowDepthBufferDesc, sizeof(pointLightShadowDepthBufferDesc));
  pointLightShadowDepthBufferDesc.Width = SHADOW_MAP_SIZE;
  pointLightShadowDepthBufferDesc.Height = SHADOW_MAP_SIZE;
  pointLightShadowDepthBufferDesc.MipLevels = 1;
  pointLightShadowDepthBufferDesc.ArraySize = 6;
  pointLightShadowDepthBufferDesc.Format = DXGI_FORMAT_R32_TYPELESS;
  pointLightShadowDepthBufferDesc.SampleDesc.Count = 1;
  pointLightShadowDepthBufferDesc.SampleDesc.Quality = 0;
  pointLightShadowDepthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  pointLightShadowDepthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
  pointLightShadowDepthBufferDesc.CPUAccessFlags = 0;
  pointLightShadowDepthBufferDesc.MiscFlags = D3D10_RESOURCE_MISC_TEXTURECUBE;

  ZeroMemory(&pointLightShadowDSVDesc, sizeof(pointLightShadowDSVDesc));
  pointLightShadowDSVDesc.Format = DXGI_FORMAT_D32_FLOAT;
  pointLightShadowDSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
  pointLightShadowDSVDesc.Flags = 0;
  pointLightShadowDSVDesc.Texture2DArray.MipSlice = 0;
  pointLightShadowDSVDesc.Texture2DArray.FirstArraySlice = 0;
  pointLightShadowDSVDesc.Texture2DArray.ArraySize = 6;

  pointLightShadowSRVDesc.Format = DXGI_FORMAT_R32_FLOAT;
  pointLightShadowSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
  pointLightShadowSRVDesc.Texture2D.MostDetailedMip = 0;
  pointLightShadowSRVDesc.Texture2D.MipLevels = 1;

  result = m_device->CreateTexture2D(&pointLightShadowDepthBufferDesc, nullptr, &m_pointLightShadowDepthBuffer);
  if (FAILED(result))
  {
    RUNTIME_ERROR("Can't create point light shadow depth buffer");
  }

  result = m_device->CreateDepthStencilView(m_pointLightShadowDepthBuffer, &pointLightShadowDSVDesc, &m_pointLightShadowDSV);
  if (FAILED(result))
  {
    RUNTIME_ERROR("Can't create point light shadow depth stencil view");
  }

  result = m_device->CreateShaderResourceView(m_pointLightShadowDepthBuffer, &pointLightShadowSRVDesc, &m_pointLightShadowSRV);
  if (FAILED(result))
  {
    RUNTIME_ERROR("Can't create point light shadow shader resource view");
  }

  for (auto& viewport : m_pointLightShadowViewports)
  {
    viewport = { 0, 0, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, 0.0f, 1.0f };
  }
}

void D3DConfigurer::PrepareToPointLightShadowGeneration()
{
  this->EnableDepthTest();
  // Set raster state with bias
  m_deviceContext->RSSetState(m_pointLightShadowRS);
  
  m_deviceContext->RSSetViewports(6, m_pointLightShadowViewports);
  m_deviceContext->OMSetRenderTargets(0, nullptr, m_pointLightShadowDSV);
  m_deviceContext->ClearDepthStencilView(m_pointLightShadowDSV, D3D11_CLEAR_DEPTH, 1.0, 0);
}

void D3DConfigurer::InitializeDefferedLightingStructures()
{
  bool result;
  D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

  ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

  depthStencilDesc.DepthEnable = true;
  depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
  depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

  depthStencilDesc.StencilEnable = true;
  depthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
  depthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

  depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
  depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

  depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
  depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

  result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilLightVolumeState);
  if (FAILED(result))
  {
    RUNTIME_ERROR("Can't create light volume depth stencil state");
  }

  depthStencilDesc.StencilEnable = false;
  depthStencilDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
  
  result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_greaterEqualReadonlyDepthStensilState);
  if (FAILED(result))
  {
    RUNTIME_ERROR("Can't create deffered light tesselated depth stencil state");
  }

  depthStencilDesc.DepthEnable = false;
  depthStencilDesc.StencilEnable = true;
  depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_NOT_EQUAL;
  depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_NOT_EQUAL;

  result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilDefferedLightState);
  if (FAILED(result))
  {
    RUNTIME_ERROR("Can't create defferred light depth stencil state");
  }

}

void D3DConfigurer::EnableDepthStencilLightVolumeState()
{
  m_deviceContext->OMSetDepthStencilState(m_depthStencilLightVolumeState, 0);
}

void D3DConfigurer::EnableDepthStencilDefferedLightState()
{
  m_deviceContext->OMSetDepthStencilState(m_depthStencilDefferedLightState, 0);
}

void D3DConfigurer::EnableGreaterEqualReadonlyDepthTest()
{
  m_deviceContext->OMSetDepthStencilState(m_greaterEqualReadonlyDepthStensilState, 0);
}

void D3DConfigurer::SetCullBackRasterState()
{
  m_deviceContext->RSSetState(m_cullBackRasterState);
}

void D3DConfigurer::SetCullFrontRasterState()
{
  m_deviceContext->RSSetState(m_cullFrontRasterState);
}

void D3DConfigurer::SetCullNoneRasterState()
{
  m_deviceContext->RSSetState(m_cullNoneRasterState);
}

void D3DConfigurer::Shutdown()
{
  // Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
  if (m_swapChain)
  {
    m_swapChain->SetFullscreenState(false, nullptr);
  }

  if (m_alphaEnableBlendingState)
  {
    m_alphaEnableBlendingState->Release();
    m_alphaEnableBlendingState = nullptr;
  }

  if (m_alphaDisableBlendingState)
  {
    m_alphaDisableBlendingState->Release();
    m_alphaDisableBlendingState = nullptr;
  }

  if (m_additiveBlendingState)
  {
    m_additiveBlendingState->Release();
    m_additiveBlendingState = nullptr;
  }

  if (m_depthDisabledStencilState)
  {
    m_depthDisabledStencilState->Release();
    m_depthDisabledStencilState = nullptr;
  }

  if (m_depthStencilView)
  {
    m_depthStencilView->Release();
    m_depthStencilView = nullptr;
  }

  if (m_depthStencilState)
  {
    m_depthStencilState->Release();
    m_depthStencilState = nullptr;
  }

  if (m_depthStencilBuffer)
  {
    m_depthStencilBuffer->Release();
    m_depthStencilBuffer = nullptr;
  }

  if (m_renderTargetView)
  {
    m_renderTargetView->Release();
    m_renderTargetView = nullptr;
  }

  if (m_deviceContext)
  {
    m_deviceContext->Release();
    m_deviceContext = nullptr;
  }

  if (m_device)
  {
    m_device->Release();
    m_device = nullptr;
  }

  if (m_swapChain)
  {
    m_swapChain->Release();
    m_swapChain = nullptr;
  }

  if (m_cullNoneRasterState)
  {
    m_cullNoneRasterState->Release();
    m_cullNoneRasterState = nullptr;
  }

  if (m_cullFrontRasterState)
  {
    m_cullFrontRasterState->Release();
    m_cullFrontRasterState = nullptr;
  }

  if (m_cullBackRasterState)
  {
    m_cullBackRasterState->Release();
    m_cullBackRasterState = nullptr;
  }

  if (m_depthStencilLightVolumeState)
  {
    m_depthStencilLightVolumeState->Release();
    m_depthStencilLightVolumeState = nullptr;
  }

  if (m_depthStencilDefferedLightState)
  {
    m_depthStencilDefferedLightState->Release();
    m_depthStencilDefferedLightState = nullptr;
  }
  
  if (m_gbuffer)
  {
    m_gbuffer->Shutdown();
    m_gbuffer = nullptr;
  }

  if (m_pointLightShadowDepthBuffer)
  {
    m_pointLightShadowDepthBuffer->Release();
    m_pointLightShadowDepthBuffer = nullptr;
  }

  if (m_pointLightShadowDSV)
  {
    m_pointLightShadowDSV->Release();
    m_pointLightShadowDSV = nullptr;
  }

  if (m_pointLightShadowSRV)
  {
    m_pointLightShadowSRV->Release();
    m_pointLightShadowSRV = nullptr;
  }

  if (m_pointLightShadowRS)
  {
    m_pointLightShadowRS->Release();
    m_pointLightShadowRS = nullptr;
  }
}

void D3DConfigurer::EnableTransparencyBlending()
{
  float blendFactor[4];

  // Setup the blend factor.
  blendFactor[0] = 0.0f;
  blendFactor[1] = 0.0f;
  blendFactor[2] = 0.0f;
  blendFactor[3] = 0.0f;

  // Turn on the alpha blending.
  m_deviceContext->OMSetBlendState(m_alphaEnableBlendingState, blendFactor, 0xffffffff);
}

void D3DConfigurer::DisableBlending()
{
  float blendFactor[4];

  // Setup the blend factor.
  blendFactor[0] = 0.0f;
  blendFactor[1] = 0.0f;
  blendFactor[2] = 0.0f;
  blendFactor[3] = 0.0f;

  // Turn off the alpha blending.
  m_deviceContext->OMSetBlendState(m_alphaDisableBlendingState, blendFactor, 0xffffffff);
}

void D3DConfigurer::EnableAditiveBlending()
{
  float blendFactor[4];

  // Setup the blend factor.
  blendFactor[0] = 0.0f;
  blendFactor[1] = 0.0f;
  blendFactor[2] = 0.0f;
  blendFactor[3] = 0.0f;

  // Turn on the alpha blending.
  m_deviceContext->OMSetBlendState(m_additiveBlendingState, blendFactor, 0xffffffff);
}

void D3DConfigurer::BeginScene(float red, float green, float blue, float alpha)
{
  float color[4];


  // Setup the color to clear the buffer to.
  color[0] = red;
  color[1] = green;
  color[2] = blue;
  color[3] = alpha;

  // Clear the back buffer.
  m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

  // Clear the depth buffer.
  m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

  return;
}

void D3DConfigurer::EndScene()
{
  // Present the back buffer to the screen since rendering is complete.
  if (m_vsync_enabled)
  {
    // Lock to screen refresh rate.
    m_swapChain->Present(1, 0);
  }
  else
  {
    // Present as fast as possible.
    m_swapChain->Present(0, 0);
  }
}

ID3D11Device* D3DConfigurer::GetDevice()
{
  return m_device;
}

ID3D11DeviceContext* D3DConfigurer::GetDeviceContext()
{
  return m_deviceContext;
}

const std::wstring& D3DConfigurer::GetVideoCardInfo()
{
  return m_videoCardDescription;
}

void D3DConfigurer::EnableDepthTest()
{
  m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 0);
}

void D3DConfigurer::DisableDepthTest()
{
  m_deviceContext->OMSetDepthStencilState(m_depthDisabledStencilState, 0);
}

void D3DConfigurer::SetBackBufferRenderTarget()
{
  m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
  m_deviceContext->RSSetViewports(1, &m_viewport);
}

void D3DConfigurer::SetNullAsDepthBuffer()
{
  m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);
}

void D3DConfigurer::SetGBufferRenderTargets()
{
  m_gbuffer->SetRenderTargets(m_deviceContext);
}

ID3D11ShaderResourceView** D3DConfigurer::GetGBufferShaderResourceViewes()
{
  return m_gbuffer->GetShaderResourceViewes();
}

void D3DConfigurer::ClearGBufferRenderTargets()
{
  m_gbuffer->ClearRenderTargets(m_deviceContext, 0.0f, 0.0f, 0.0f, 0.0f);
}

void D3DConfigurer::SetGBufferOnlyWriteableDepthBufferToRenderTargets()
{
  m_deviceContext->OMSetRenderTargets(0, nullptr, m_gbuffer->GetWriteableDepthBuffer());
}

void D3DConfigurer::ClearGBufferStencil()
{
  m_gbuffer->ClearStencil(m_deviceContext);
}

void D3DConfigurer::SetGBufferReadonlyDepthBufferToRenderTargets()
{
  m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_gbuffer->GetReadonlyDepthBuffer());
}

void D3DConfigurer::PrepareToFullScreenDefferedEffect()
{
  unsigned int stride = 0;
  unsigned int offset = 0;
  m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
  m_deviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0);
  m_deviceContext->IASetVertexBuffers(0, 0, nullptr, &stride, &offset);
}