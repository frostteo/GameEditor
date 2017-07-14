#pragma once

#include <string>

class IMaterial
{
protected:
  std::string m_name;
  std::string m_type;
public:
  IMaterial(const std::string& name, const std::string& type) { m_name = name; m_type = type; }
  virtual ~IMaterial();
  const std::string& GetType() { return m_type; }
};

