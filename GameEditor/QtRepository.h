#pragma once

#include <QtSql>
#include "IRepository.h"
#include "qstring.h"
#include "Logger.h"
#include "QtUtils.h"
#include <math.h>
#include <map>
#include <vector>
#include <memory>
#include "DbTableMetadata.h"

template <class T>
class QtRepository :
  public IRepository<T>
{
protected:
  static const QString INNER_JOIN_OP_STR;
  static const QString LEFT_JOIN_OP_STR;
  static const QString RIGHT_JOIN_OP_STR;

  static bool m_foreignKeyEnabled;

  std::string m_connectionName;
  QString m_defaultOrderField = "id";
protected:
  static std::unique_ptr<DbTableMetadata<T>> m_tableMetadata;
protected:
  QSqlDatabase GetDatabase();
  virtual std::vector<T> QueryToEntities(QSqlQuery* query, std::vector<QString>* joinTableNames = nullptr);
  QString ToString(JoinOperator joinOperator);
  QString GetAllJoinsConditionStr(const std::vector<JoinInfo>& joinInfos);
  std::vector<QString> GetJoinTableNames(const std::vector<JoinInfo>& joinInfos);
public:
  QtRepository<T>() { }
  virtual ~QtRepository<T>() {}

  virtual IRepository<T>* Initialize(std::string connectionName);
  virtual std::vector<T> GetAll(std::vector<JoinInfo>* joinInfos = nullptr) override;
  virtual std::vector<T> GetAll(GetParameters& parameters, PagingInfo& pagingInfo) override;
  virtual T Get(int id, std::vector<JoinInfo>* joinInfos = nullptr) override;
  virtual void Delete(int id) override;
  virtual void Update(T& entity) override;
  virtual int Create(T& entity) override;
  virtual void DeleteWhere(std::string& whereCondition);
  virtual void ExecuteQuery(std::string queryStr) override;
};

template <class T>
bool QtRepository<T>::m_foreignKeyEnabled = false;

template <class T>
std::unique_ptr<DbTableMetadata<T>> QtRepository<T>::m_tableMetadata = std::unique_ptr<DbTableMetadata<T>>();

template <class T>
const QString QtRepository<T>::INNER_JOIN_OP_STR = "INNER JOIN";

template <class T>
const QString QtRepository<T>::LEFT_JOIN_OP_STR = "LEFT JOIN";

template <class T>
const QString QtRepository<T>::RIGHT_JOIN_OP_STR = "RIGHT JOIN";

template <class T>
QString QtRepository<T>::ToString(JoinOperator joinOperator)
{
  switch (joinOperator)
  {
    case JoinOperator::INNER_JOIN:
        return INNER_JOIN_OP_STR;
        break;
    case JoinOperator::LEFT_JOIN:
      return LEFT_JOIN_OP_STR;
      break;
    case JoinOperator::RIGHT_JOIN:
      return RIGHT_JOIN_OP_STR;
      break;
    default:
      throw std::runtime_error(Logger::get().GetErrorTraceMessage("There is such join operator", __FILE__, __LINE__));
  }
}

template <class T>
IRepository<T>* QtRepository<T>::Initialize(std::string connectionName)
{
  m_connectionName = connectionName; 

  if (!m_foreignKeyEnabled) {
    QSqlQuery query(GetDatabase());
    query.prepare("PRAGMA foreign_keys=on;"); //foreign key constrains enable
    if (!query.exec())
      RUNTIME_ERROR(query.lastError().text().toStdString())
      m_foreignKeyEnabled = true;
  }
  
  return this;
}

template <class T>
void QtRepository<T>::ExecuteQuery(std::string queryStr)
{
  QSqlQuery query(GetDatabase());
  query.prepare(QString::fromStdString(queryStr));
  if (!query.exec())
    RUNTIME_ERROR(query.lastError().text().toStdString())
}

template <class T>
QSqlDatabase QtRepository<T>::GetDatabase()
{
  return QSqlDatabase::database(m_connectionName.c_str());
}

template <class T>
std::vector<T> QtRepository<T>::GetAll(std::vector<JoinInfo>* joinInfos = nullptr)
{
  QSqlQuery query(GetDatabase());
  QString allJoinConditionStr = "";
  std::vector<QString> joinTableNames;
  if (joinInfos) {
    allJoinConditionStr = GetAllJoinsConditionStr((*joinInfos));
    joinTableNames = GetJoinTableNames((*joinInfos));
  }

  QString selectAllStr = QString("SELECT %1 FROM %2 %3").arg(m_tableMetadata->GetSelectColumnString(&joinTableNames), m_tableMetadata->GetTableName(), allJoinConditionStr);
  query.prepare(selectAllStr);

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(query.lastError().text().toStdString(), __FILE__, __LINE__));

  return QueryToEntities(&query, &joinTableNames);
}

template <class T>
QString QtRepository<T>::GetAllJoinsConditionStr(const std::vector<JoinInfo>& joinInfos)
{
  char space = ' ';
  QString joinConditionString = "";
  for (auto& joinInfo : joinInfos)
  {
    joinConditionString += ToString(joinInfo.joinOpeator) + space + (m_tableMetadata->GetJoinConditions())[QString::fromStdString(joinInfo.tableName)] + space;
  }

  return joinConditionString;
}

template <class T>
std::vector<QString> QtRepository<T>::GetJoinTableNames(const std::vector<JoinInfo>& joinInfos)
{
  std::vector<QString> joinTableNames;
  for (auto& joinInfo : joinInfos)
    joinTableNames.push_back(QString::fromStdString(joinInfo.tableName));

  return joinTableNames;
}

template <class T>
std::vector<T> QtRepository<T>::GetAll(GetParameters& parameters, PagingInfo& pagingInfo)
{
  QString orderField;
  QString orderDirection = parameters.orderDirection == OrderDirection::ASC ? "ASC" : "DESC";
  QString whereCondition = QString::fromStdString(parameters.whereCondition);
  QString allJoinCondition = GetAllJoinsConditionStr(parameters.joinInfos);
  std::vector<QString> joinTableNames = GetJoinTableNames(parameters.joinInfos);
  QSqlQuery countQuery(GetDatabase());
  QSqlQuery selectQuery(GetDatabase());
  int allRowCount;
  int offset;
  QString selectColumnStr = m_tableMetadata->GetSelectColumnString(&joinTableNames);
  QString selectQueryString;

  if (parameters.orderFieldName.empty())
  {
    orderField = m_defaultOrderField;
    pagingInfo.orderFieldName = m_defaultOrderField.toStdString();
  }
  else
  {
    orderField = QString::fromStdString(parameters.orderFieldName);
    pagingInfo.orderFieldName = parameters.orderFieldName;
  }

  QString countQueryString = QString("SELECT COUNT(*), %1 FROM %2 %3 WHERE %4").arg(selectColumnStr, m_tableMetadata->GetTableName(), allJoinCondition, whereCondition);
  countQuery.prepare(countQueryString);
  if (countQuery.exec()) {
    countQuery.next();
    allRowCount = countQuery.value(0).toInt();
  }
   
  else {
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(countQuery.lastError().text().toStdString(), __FILE__, __LINE__));
  }

  pagingInfo.pageCount = ceil((float) allRowCount / (float) parameters.onPage);

  if (pagingInfo.pageCount == 0) pagingInfo.pageCount = 1;
  if ((parameters.pageNumber - 1) * parameters.onPage >= allRowCount) parameters.pageNumber = pagingInfo.pageCount;
  if (parameters.pageNumber - 1 < 0) parameters.pageNumber = 1;
  offset = (parameters.pageNumber - 1) * parameters.onPage;
 
  pagingInfo.pageNumber = parameters.pageNumber;
  pagingInfo.orderDirection = parameters.orderDirection;

  selectQueryString = QString("SELECT %1 FROM %2 %3 WHERE %4 ORDER BY %5 %6 LIMIT %7, %8").arg(selectColumnStr, m_tableMetadata->GetTableName(), allJoinCondition, whereCondition, orderField, orderDirection, QString::number(offset), QString::number(parameters.onPage));
   selectQuery.prepare(selectQueryString);

  if (!selectQuery.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(selectQuery.lastError().text().toStdString(), __FILE__, __LINE__));

  return QueryToEntities(&selectQuery, &joinTableNames);
}

template <class T>
T QtRepository<T>::Get(int id, std::vector<JoinInfo>* joinInfos)
{
  QSqlQuery query(GetDatabase());
  QString allJoinConditionStr = "";
  std::vector<QString> joinTableNames;
  if (joinInfos) {
    allJoinConditionStr = GetAllJoinsConditionStr((*joinInfos));
    joinTableNames = GetJoinTableNames((*joinInfos));
  }
  QString idColumnFullName = m_tableMetadata->GetSelectInfos()[m_tableMetadata->GetKeyColumnName()].fullColumnName;
  QString getSqlStr = QString("SELECT %1 FROM %2 %3 WHERE %4 = :%5").arg(m_tableMetadata->GetSelectColumnString(&joinTableNames), m_tableMetadata->GetTableName(), allJoinConditionStr, idColumnFullName, "id");

  query.prepare(getSqlStr);
  query.bindValue(":id", id);

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(query.lastError().text().toStdString(), __FILE__, __LINE__));

  return QueryToEntities(&query, &joinTableNames)[0];
}

template <class T>
void QtRepository<T>::Delete(int id)
{
  QSqlQuery query(GetDatabase());

  query.prepare(m_tableMetadata->GetDeleteQueryString());
  query.bindValue(":" + m_tableMetadata->GetKeyColumnName(), id);

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(query.lastError().text().toStdString(), __FILE__, __LINE__));
}

template <class T>
void QtRepository<T>::Update(T& entity)
{
  QSqlQuery query(GetDatabase());

  query.prepare(m_tableMetadata->GetUpdateQueryString());
  for (const auto &columnName : m_tableMetadata->GetColumnNames())
  {
    QVariant value = m_tableMetadata->GetFieldByName(entity, columnName);
    query.bindValue(":" + columnName, value);
  }
  QVariant value = m_tableMetadata->GetFieldByName(entity, m_tableMetadata->GetKeyColumnName());
  query.bindValue(":" + m_tableMetadata->GetKeyColumnName(), value);

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(query.lastError().text().toStdString(), __FILE__, __LINE__));
}

template <class T>
int QtRepository<T>::Create(T& entity)
{
  QSqlQuery query(GetDatabase());
  QString insertQueryStr = m_tableMetadata->GetInsertQueryString();

  int lastInsertRowId;
  QString lastInsertRowIdQueryStr = "SELECT last_insert_rowid()";
  QSqlQuery lastInsertRowIdQuery(GetDatabase());

  query.prepare(insertQueryStr);
  for (const auto &columnName : m_tableMetadata->GetColumnNames())
  {
    QVariant value = m_tableMetadata->GetFieldByName(entity, columnName);
    query.bindValue(":" + columnName, value);
  }

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(query.lastError().text().toStdString(), __FILE__, __LINE__));
 
  lastInsertRowIdQuery.prepare(lastInsertRowIdQueryStr);

  if (lastInsertRowIdQuery.exec()) {
    lastInsertRowIdQuery.next();
    lastInsertRowId = lastInsertRowIdQuery.value(0).toInt();
    return lastInsertRowId;
  }

  else {
    RUNTIME_ERROR(lastInsertRowIdQuery.lastError().text().toStdString())
  }

}

template <class T>
std::vector<T> QtRepository<T>::QueryToEntities(QSqlQuery* query, std::vector<QString>* joinTableNames)
{
  QSqlRecord record = query->record();

  std::vector<T> result;
  while (query->next())
  {
    T entity;
    m_tableMetadata->InitializeFromQuery(entity, query, joinTableNames);
    result.push_back(entity);
  }
  return result;
}

template <class T>
void QtRepository<T>::DeleteWhere(std::string& whereCondition)
{
  QSqlQuery query(GetDatabase());
  QString lastInsertRowIdQueryStr = "Test";
}