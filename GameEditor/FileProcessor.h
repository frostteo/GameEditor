#pragma once

#include <string>
#include <fstream>

class FileProcessor
{
public:
  static const char FILE_SEPARATOR = '/';
public:
  FileProcessor();
  virtual ~FileProcessor();
  static bool GetFileAsString(const std::string& sourceFileName, std::string& fileInstr);
  static bool FileExists(const std::string& filename);
  static std::string GetFileNameWithoutExtension(const std::string& fileName);
  static std::string GetFileExtension(const std::string& fileName);
};

