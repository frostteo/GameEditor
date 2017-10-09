#pragma once

#include <string>
#include <vector>
#include "OrderDirection.h"

enum JoinOperator {
  INNER_JOIN = 1,
  LEFT_JOIN = 2,
  RIGHT_JOIN = 3
};

struct JoinInfo {
  std::string tableName;
  JoinOperator joinOpeator;
};

struct GetParameters
{
public:
  std::string whereCondition = "1";
  std::string orderFieldName = "";
  OrderDirection orderDirection = OrderDirection::ASC;
  int pageNumber = 1;
  int onPage = 10;
  std::vector<JoinInfo> joinInfos;
public:
  GetParameters() {}
  virtual ~GetParameters() {}
};

