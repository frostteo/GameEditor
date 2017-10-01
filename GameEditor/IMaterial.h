#pragma once

#include <string>
#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

class IMaterial
{
protected:
  std::string m_name;
public:
  IMaterial(const std::string& name) { m_name = name; }
  virtual ~IMaterial();
  virtual const std::string& GetType() = 0;
  virtual ID3D11ShaderResourceView** GetTextures() { return nullptr; }
  virtual int GetTexturesCount() { return 0; }
};

