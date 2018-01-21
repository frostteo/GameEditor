#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include "Logger.h"

using namespace DirectX;

enum GBufferType
{
  POSITION = 0,
  DIFFUSE = 1,
  NORMAL = 2,
  SPECULAR = 3,
  VIEW_DIRECTION = 4,
  SELF_ILUM = 5
};

class GBuffer
{
public:
  const static int BUFFER_COUNT = 6;

private:
  int m_textureWidth, m_textureHeight;
  ID3D11Texture2D* m_renderTargetTextureArray[BUFFER_COUNT];
  ID3D11RenderTargetView* m_renderTargetViewArray[BUFFER_COUNT];
  ID3D11ShaderResourceView* m_shaderResourceViewArray[BUFFER_COUNT];
  ID3D11Texture2D* m_depthStencilBuffer;
  ID3D11DepthStencilView* m_depthStencilView;
  D3D11_VIEWPORT m_viewport;
public:
  GBuffer();
  virtual ~GBuffer();

  void Initialize(ID3D11Device* device, int textureWidth, int textureHeight);
  void Shutdown();

  void SetRenderTargets(ID3D11DeviceContext* deviceContext);
  void ClearRenderTargets(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha);

  ID3D11ShaderResourceView* GetShaderResourceView(int index);
  ID3D11ShaderResourceView** GetShaderResourceViewes() { return m_shaderResourceViewArray; }

  ID3D11DepthStencilView* GetDepthBuffer() { return m_depthStencilView; }
  void ClearStencil(ID3D11DeviceContext* deviceContext) { deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_STENCIL, 1.0f, 0); }
};

