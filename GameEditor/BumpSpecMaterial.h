#pragma once

#include "BumpMaterial.h"
#include <directxmath.h>
#include "TextureMaterial.h"

using namespace DirectX;

class BumpSpecMaterial :
  public BumpMaterial
{
private:
  static const int TEXTURES_COUNT = 2;
  ID3D11ShaderResourceView* textures[TEXTURES_COUNT];
public:
  XMFLOAT3 m_specularColor;
  float m_specularPower;
  static const std::string bumpSpecMaterialType;
public:
  BumpSpecMaterial(const std::string& name, Texture* texture, Texture* normalMap, float bumpDepth, XMFLOAT3 specularColor, float specularPower)
    : BumpMaterial(name, texture, normalMap, bumpDepth)
  {
    m_specularColor = specularColor;
    m_specularPower = specularPower;
    textures[0] = m_texture->GetTexture();
    textures[1] = m_normalMap->GetTexture();
  }
  virtual ~BumpSpecMaterial();
  virtual const std::string GetType() const override { return BumpSpecMaterial::bumpSpecMaterialType; }
  virtual ID3D11ShaderResourceView* const* GetTextures() const override { return textures; }
  virtual int GetTexturesCount() const { return TEXTURES_COUNT; }
};

