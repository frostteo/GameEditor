#pragma once 

#include "IConverter.h"

class IMeshConverter : public IConverter {
public:
  IMeshConverter() {}
  virtual ~IMeshConverter() { }

  bool virtual ConvertModel(const std::string& sourceFileName, const std::string& destinationFileName) = 0;
};