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
  IMaterial(const std::string& name) : m_name(name) { }
  virtual ~IMaterial() = default;
 
  virtual const std::string GetType() const = 0;
  const std::string GetName() const { return m_name; }

  virtual ID3D11ShaderResourceView* const* GetTextures() const { return nullptr; }
  virtual int GetTexturesCount() const { return 0; }
};

