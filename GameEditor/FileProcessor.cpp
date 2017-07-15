#include "FileProcessor.h"


FileProcessor::FileProcessor()
{
}


FileProcessor::~FileProcessor()
{
}


bool FileProcessor::GetFileAsString(const std::string& sourceFileName, std::string& fileInstr)
{
  std::ifstream in(sourceFileName.c_str(), std::ios::binary);
  if (in.fail())
    return false;

  std::istreambuf_iterator<char> begin(in), end;
  fileInstr = std::string(begin, end);
  in.close();
  return true;
}

std::string FileProcessor::UnicodeStrToByteStr(const std::wstring& unicodeStr)
{
  std::string byteStr(unicodeStr.begin(), unicodeStr.end());
  return byteStr;
}