
#include "IMeshConverter.h"

bool IMeshConverter::CanConvert(const std::string& sourceFileName) const
{
  int fileExtensionLength = m_fileExtension.length();
  return sourceFileName.substr(sourceFileName.length() - fileExtensionLength, fileExtensionLength) == m_fileExtension;
}

bool IMeshConverter::GetFileAsString(const std::string& sourceFileName, std::string& fileInstr)
{
  return FileProcessor::GetFileAsString(sourceFileName, fileInstr);
}