#include "IConverter.h"

bool IConverter::CanConvert(const std::string& sourceFileName) const
{
  return FileProcessor::GetFileExtension(sourceFileName) == m_fileExtension;
}

bool IConverter::GetFileAsString(const std::string& sourceFileName, std::string& fileInstr)
{
  return FileProcessor::GetFileAsString(sourceFileName, fileInstr);
}