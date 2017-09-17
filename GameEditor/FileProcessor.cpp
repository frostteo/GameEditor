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

bool FileProcessor::FileExists(const std::string& filename)
{
  if (std::fstream(filename))
    return true;

  return false;
}

std::string FileProcessor::GetFileNameWithoutExtension(const std::string& fileName)
{
  int lastPointOccurenceIndex = fileName.rfind('.');
  return fileName.substr(0, lastPointOccurenceIndex);
}

std::string FileProcessor::GetFileExtension(const std::string& fileName)
{
  int lastPointOccurenceIndex = fileName.rfind('.');
  return fileName.substr(lastPointOccurenceIndex + 1);
}