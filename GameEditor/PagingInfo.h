#pragma once

#include <string>
#include "OrderDirection.h"

struct PagingInfo
{
public:
  int pageNumber;
  int pageCount;
  std::string orderFieldName;
  OrderDirection orderDirection;
public:
  PagingInfo() {}
  virtual ~PagingInfo() {}
};

