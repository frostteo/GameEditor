#pragma once

#include "FileProcessor.h"

class IConverter
{
protected:
  std::string m_fileExtension;
protected:
  bool GetFileAsString(const std::string& sourceFileName, std::string& fileInstr);
public:
  const std::string& GetFileExtension() { return m_fileExtension; }
  IConverter() { }
  virtual ~IConverter() { }
  bool CanConvert(const std::string& sourceFileName) const;
};

