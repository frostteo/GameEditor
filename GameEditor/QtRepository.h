#pragma once

#include <QtSql>
#include "IRepository.h"
#include "qstring.h"
#include "Logger.h"
#include "QtUtils.h"
#include <math.h>

template <class T>
class QtRepository :
  public IRepository<T>
{
protected:
  std::string m_connectionName;
  QString m_tableName;
  QString m_keyColumnName;
  QString m_defaultOrderField = "id";
  std::vector<QString> m_columnNames;

  QString m_insertQueryStr = QString();
  QString m_updateQueryStr = QString();
protected:
  QSqlDatabase GetDatabase();
  virtual std::vector<T> QueryToEntities(QSqlQuery* query) = 0;
  virtual QString GetFieldByName(const T& entity, QString name) = 0;
  virtual void BuildInsertQueryStr();
  virtual void BuildUpdateQueryStr();
public:
  QtRepository() { m_keyColumnName = "id"; }
  virtual ~QtRepository() {}

  virtual IRepository<T>* Initialize(std::string connectionName) { m_connectionName = connectionName; return this; }
  virtual std::vector<T> GetAll() override;
  virtual std::vector<T> GetAll(GetParameters& parameters, PagingInfo& pagingInfo) override;
  virtual T Get(int id) override;
  virtual void Delete(int id) override;
  virtual void Update(T& entity) override;
  virtual void Create(T& entity) override;
};

template <class T>
void QtRepository<T>::BuildInsertQueryStr()
{
  m_insertQueryStr = "INSERT INTO %1 (";

  for (const auto &columnName : m_columnNames)
  {
    m_insertQueryStr += columnName + ", ";
  }
  m_insertQueryStr = m_insertQueryStr.left(m_insertQueryStr.size() - 2);

  m_insertQueryStr += ") VALUES(";
  for (const auto &columnName : m_columnNames)
  {
    m_insertQueryStr += ":" + columnName + ", ";
  }
  m_insertQueryStr = m_insertQueryStr.left(m_insertQueryStr.size() - 2);
  m_insertQueryStr += ")";
}


template <class T>
void QtRepository<T>::BuildUpdateQueryStr()
{
  m_updateQueryStr = "UPDATE %1 SET ";
  for (const auto &columnName : m_columnNames)
  {
    m_updateQueryStr += columnName + " = :" + columnName + ", ";
  }
  m_updateQueryStr = m_updateQueryStr.left(m_updateQueryStr.size() - 2);
  m_updateQueryStr += " WHERE %2 = :%2";
}

template <class T>
QSqlDatabase QtRepository<T>::GetDatabase()
{
  return QSqlDatabase::database(m_connectionName.c_str());
}

template <class T>
std::vector<T> QtRepository<T>::GetAll()
{
  QSqlQuery query(GetDatabase());
  query.prepare(QString("SELECT * FROM %1").arg(m_tableName));

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(QtUtils::SqlErrorToStr(query.lastError()), __FILE__, __LINE__));

  return QueryToEntities(&query);
}

template <class T>
std::vector<T> QtRepository<T>::GetAll(GetParameters& parameters, PagingInfo& pagingInfo)
{
  QString orderField;
  QString orderDirection = parameters.orderDirection == OrderDirection::ASC ? "ASC" : "DESC";
  QString whereCondition = QString::fromStdString(parameters.whereCondition);
  QSqlQuery countQuery(GetDatabase());
  QSqlQuery selectQuery(GetDatabase());
  int allRowCount;
  int offset;

  if (parameters.orderFieldName.empty())
  {
    orderField = m_defaultOrderField;
    pagingInfo.orderFieldName = QtUtils::QStringToStdStr(m_defaultOrderField);
  }
  else
  {
    orderField = QString::fromStdString(parameters.orderFieldName);
    pagingInfo.orderFieldName = parameters.orderFieldName;
  }

  countQuery.prepare(QString("SELECT COUNT(*) FROM %1 WHERE %2").arg(m_tableName, whereCondition));
  if (countQuery.exec()) {
    countQuery.next();
    allRowCount = countQuery.value(0).toInt();
  }
   
  else {
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(QtUtils::SqlErrorToStr(countQuery.lastError()), __FILE__, __LINE__));
  }

  pagingInfo.pageCount = ceil(allRowCount / parameters.onPage);

  if (pagingInfo.pageCount == 0) pagingInfo.pageCount = 1;
  if ((parameters.pageNumber - 1) * parameters.onPage >= allRowCount) parameters.pageNumber = pagingInfo.pageCount;
  if (parameters.pageNumber - 1 < 0) parameters.pageNumber = 1;
  offset = (parameters.pageNumber - 1) * parameters.onPage;
 
  pagingInfo.pageNumber = parameters.pageNumber;
  pagingInfo.orderDirection = parameters.orderDirection;

  selectQuery.prepare(QString("SELECT * FROM %1 WHERE %2 ORDER BY %3 %4 LIMIT %5, %6").arg(m_tableName, whereCondition, orderField, orderDirection, QString::number(offset), QString::number(parameters.onPage)));

  if (!selectQuery.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(QtUtils::SqlErrorToStr(selectQuery.lastError()), __FILE__, __LINE__));

  return QueryToEntities(&selectQuery);
}

template <class T>
T QtRepository<T>::Get(int id)
{
  QSqlQuery query(GetDatabase());

  query.prepare(QString("SELECT * FROM %1 WHERE %2 = :%2").arg(m_tableName, m_keyColumnName));
  query.bindValue(":" + m_keyColumnName, id);

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(QtUtils::SqlErrorToStr(query.lastError()), __FILE__, __LINE__));

  return QueryToEntities(&query)[0];
}

template <class T>
void QtRepository<T>::Delete(int id)
{
  QSqlQuery query(GetDatabase());

  query.prepare(QString("DELETE FROM %1 WHERE %2 = :%2").arg(m_tableName, m_keyColumnName));
  query.bindValue(":" + m_keyColumnName, id);

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(QtUtils::SqlErrorToStr(query.lastError()), __FILE__, __LINE__));
}

template <class T>
void QtRepository<T>::Update(T& entity)
{
  QSqlQuery query(GetDatabase());

  if (m_updateQueryStr.isNull())
    BuildUpdateQueryStr();

  QString queryString = m_updateQueryStr;
  query.prepare(queryString.arg(m_tableName, m_keyColumnName));
  for (const auto &columnName : m_columnNames)
  {
    QString value = GetFieldByName(entity, columnName);
    query.bindValue(":" + columnName, value);
  }
  QString value = GetFieldByName(entity, m_keyColumnName);
  query.bindValue(":" + m_keyColumnName, value);

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(QtUtils::SqlErrorToStr(query.lastError()), __FILE__, __LINE__));
}

template <class T>
void  QtRepository<T>::Create(T& entity)
{
  QSqlQuery query(GetDatabase());

  if (m_insertQueryStr.isNull())
    BuildInsertQueryStr();

  QString queryString = m_insertQueryStr;

  query.prepare(queryString.arg(m_tableName));
  for (const auto &columnName : m_columnNames)
  {
    QString value = GetFieldByName(entity, columnName);
    query.bindValue(":" + columnName, value);
  }

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(QtUtils::SqlErrorToStr(query.lastError()), __FILE__, __LINE__));
}