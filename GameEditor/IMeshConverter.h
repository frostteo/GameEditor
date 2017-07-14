#pragma once 

#include <string>
#include <fstream>
#include "FileProcessor.h"

class IMeshConverter {
protected:
  std::string m_fileExtension;
protected:
  bool GetFileAsString(const std::string& sourceFileName, std::string& fileInstr);
public:
  const std::string& GetFileExtension() { return m_fileExtension; }
  IMeshConverter() {}
  virtual ~IMeshConverter() { }

  bool CanConvert(const std::string& sourceFileName) const;
  bool virtual ConvertModel(const std::string& sourceFileName, const std::string& destinationFileName) = 0;
};