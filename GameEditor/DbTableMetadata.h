#pragma once

#include <QtSql>
#include <QString>
#include <qvariant.h>
#include <vector>
#include <map>
#include "Logger.h"

#include "GetParameters.h"

struct SelectInfo {
  QString fullColumnName; //имя столбца с префиксом именем таблицы
  QString aliasColumnName; //имя псевдонима
};

struct RelationshipData {
  QString ThisTableForeignKeyName;
  QString OtherTablePrimaryKeyName;
};

template <class T>
class DbTableMetadata
{
protected:
  static const char POINT = '.';
  static const char UNDERSCORE = '_';
  static const QString COMA;
  static const QString AS_STR;

  QString m_tableName;
  std::vector<QString> m_columnNames;
  std::map<QString, SelectInfo> m_columnSelectInfos;
  std::map<QString, RelationshipData> m_relationships; // relation wih other table in format - tableName : RelationshipData
  std::map<QString, QString> m_joinConditions; // in format tableName: joinCondition string
  QString m_selectColumnsStr;
  QString m_insertQueryStr;
  QString m_updateQueryStr;
  QString m_deleteQueryStr;
protected:
  void BuildSelectInfos();
  virtual void BuildSelectColumnsStr();
  void BuildInsertQueryStr();
  void BuildUpdateQueryStr();
  void BuildDeleteQueryStr();
  virtual void BuildJoinConditions();
  virtual void AddRelationShip(QString tableName, QString thisTableForeignKey, QString otherTablePrimaryKey);
  QString JoinOpToString(JoinOperator joinOperator);
public:
  DbTableMetadata() {}
  virtual ~DbTableMetadata() {}

  virtual QString GetTableName() { return m_tableName; };
  virtual std::vector<QString> GetColumnNames() { return m_columnNames; };
  virtual std::map<QString, SelectInfo> GetSelectInfos() { if (m_columnSelectInfos.size() == 0) BuildSelectInfos(); return m_columnSelectInfos; }
  virtual QString GetKeyColumnName() { return "id"; }
  virtual QString GetSelectColumnString(std::vector<QString>* joinTableNames = nullptr) { if (m_selectColumnsStr.isEmpty()) BuildSelectColumnsStr(); return m_selectColumnsStr; };
  virtual QString GetInsertQueryString() { if (m_insertQueryStr.isEmpty()) BuildInsertQueryStr(); return m_insertQueryStr; }
  virtual QString GetUpdateQueryString() { if (m_updateQueryStr.isEmpty()) BuildUpdateQueryStr(); return m_updateQueryStr; }
  virtual QString GetDeleteQueryString() { if (m_deleteQueryStr.isEmpty()) BuildDeleteQueryStr(); return m_deleteQueryStr; }
  virtual QString GetDefaultOrderString() { return GetColumnNames()[0]; }
  virtual std::map<QString, QString> GetJoinConditions() { if (m_joinConditions.size() == 0) BuildJoinConditions(); return m_joinConditions; };
  
  virtual void InitializeFromQuery(T& entity, QSqlQuery* query, std::vector<QString>* joinTableNames = nullptr) = 0;
  virtual QVariant GetFieldByName(const T& entity, QString name) = 0;
  virtual std::map<QString, RelationshipData> GetRelationShips() { return m_relationships; }

  virtual QString GetAlias(int columnIndex) { return GetSelectInfos()[GetColumnNames()[columnIndex]].aliasColumnName; }
  virtual QString GetRelationShipAlias(QString tableName, int columnIndex) { RUNTIME_ERROR("this method not implemented or there are no relationships.") }
};

template <class T>
const QString DbTableMetadata<T>::COMA = ", ";

template <class T>
const QString DbTableMetadata<T>::AS_STR = " AS ";

template <class T>
QString DbTableMetadata<T>::JoinOpToString(JoinOperator joinOperator)
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
    RUNTIME_ERROR("There is such join operator");
  }
}

template <class T>
void DbTableMetadata<T>::AddRelationShip(QString tableName, QString thisTableForeignKey, QString otherTablePrimaryKey)
{
  m_relationships[tableName] = { thisTableForeignKey, otherTablePrimaryKey };
}

template <class T>
void DbTableMetadata<T>::BuildSelectInfos()
{
  SelectInfo selectInfo;
  selectInfo.fullColumnName = m_tableName + POINT + GetKeyColumnName();
  selectInfo.aliasColumnName = m_tableName + UNDERSCORE + GetKeyColumnName();
  m_columnSelectInfos[GetKeyColumnName()] = selectInfo;

  for (auto& columnName : m_columnNames){
    SelectInfo selectInfo;
    selectInfo.fullColumnName = m_tableName + POINT + columnName;
    selectInfo.aliasColumnName = m_tableName + UNDERSCORE + columnName;
    m_columnSelectInfos[columnName] = selectInfo;
  }
}

template <class T>
void DbTableMetadata<T>::BuildSelectColumnsStr()
{
  int index = 0;
  for (auto& m_columnSelectInfo : GetSelectInfos())
  {
    m_selectColumnsStr += m_columnSelectInfo.second.fullColumnName + AS_STR + m_columnSelectInfo.second.aliasColumnName;

    if (index < m_columnSelectInfos.size() - 1)
      m_selectColumnsStr += COMA;

    ++index;
  }
}

template <class T>
void DbTableMetadata<T>::BuildInsertQueryStr()
{
  m_insertQueryStr = "INSERT INTO " + GetTableName() + " (";

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
void DbTableMetadata<T>::BuildUpdateQueryStr()
{
  m_updateQueryStr = QString("UPDATE %1 SET ").arg(GetTableName());
  for (const auto &columnName : m_columnNames)
  {
    m_updateQueryStr += columnName + " = :" + columnName + ", ";
  }
  m_updateQueryStr = m_updateQueryStr.left(m_updateQueryStr.size() - 2);
  m_updateQueryStr += QString(" WHERE %1 = :%1").arg(GetKeyColumnName());
}

template <class T>
void DbTableMetadata<T>::BuildDeleteQueryStr()
{
  m_deleteQueryStr = QString("DELETE FROM %1 WHERE %2 = :%2").arg(GetTableName(), GetKeyColumnName());
}

template <class T>
void DbTableMetadata<T>::BuildJoinConditions()
{
  char space = ' ';
  for (auto& relationship : m_relationships)
  {
    m_joinConditions[relationship.first] = relationship.first + " ON " + GetTableName() + POINT + relationship.second.ThisTableForeignKeyName + " = " + relationship.first + POINT + relationship.second.OtherTablePrimaryKeyName;
  }
}
