#pragma once

#include <string>
#include "IMaterial.h"

class IMaterialCreator
{
protected:
  std::string m_type;
public:
  IMaterialCreator();
  virtual ~IMaterialCreator();
  bool CanCreate(const std::string& type) { return m_type == type; }
  virtual IMaterial* Get(const std::string& fileInStr, const std::string& fileName) {
    return nullptr;
  }
};

