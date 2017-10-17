#pragma once

#include <string>
#include "OrderDirection.h"

struct PagingInfo
{
public:
  int pageNumber = 1;
  int pageCount = 1;
  std::string orderFieldName;
  OrderDirection orderDirection;
public:
  PagingInfo() { }
  virtual ~PagingInfo() {}
};

