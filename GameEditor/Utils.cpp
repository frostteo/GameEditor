#include "Utils.h"


Utils::Utils()
{
}


Utils::~Utils()
{
}

std::string Utils::UnicodeStrToByteStr(const std::wstring& unicodeStr)
{
  std::string byteStr(unicodeStr.begin(), unicodeStr.end());
  return byteStr;
}

std::string Utils::Trim(const std::string& str)
{
  const std::string whiteCharacters = " \t\n\v\f\r";
  const auto trimmedStrBegin = str.find_first_not_of(whiteCharacters);
  const auto trimmedStrEnd = str.find_last_not_of(whiteCharacters);
  const auto trimedStrLength = trimmedStrEnd - trimmedStrBegin + 1;
  return str.substr(trimmedStrBegin, trimedStrLength);
}