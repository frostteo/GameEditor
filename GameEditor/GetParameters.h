#pragma once

#include <string>
#include "OrderDirection.h"

struct GetParameters
{
public:
  std::string whereCondition = "1";
  std::string orderFieldName = "";
  OrderDirection orderDirection = OrderDirection::ASC;
  int pageNumber = 1;
  int onPage = 10;
public:
  GetParameters() {}
  virtual ~GetParameters() {}
};

