#pragma once

#include <string>
#include <fstream>

class FileProcessor
{
public:
  FileProcessor();
  virtual ~FileProcessor();
  static bool GetFileAsString(const std::string& sourceFileName, std::string& fileInstr);
};

