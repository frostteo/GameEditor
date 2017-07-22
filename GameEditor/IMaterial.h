#pragma once

#include <string>

class IMaterial
{
protected:
  std::string m_name;
public:
  IMaterial(const std::string& name) { m_name = name; }
  virtual ~IMaterial();
  virtual const std::string& GetType() = 0;
  virtual int GetTextureCount() { return 0; }
};

