#include "StaticGORepository.h"

StaticGORepository::StaticGORepository()
{
}


StaticGORepository::~StaticGORepository()
{
}

IRepository<StaticGameObject>* StaticGORepository::Initialize(std::string connectionName)
{
  m_connectionName = connectionName;
  m_tableName = "StaticGameObject";
  m_columnNames.push_back("name");
  m_columnNames.push_back("modelFileName");
  m_columnNames.push_back("materialFileName");
  m_defaultOrderField = "name";

  QSqlQuery query(GetDatabase());

  query.prepare(QString("CREATE TABLE IF NOT EXISTS %1 (%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 TEXT UNIQUE, %4 TEXT, %5 TEXT)").
    arg(m_tableName, m_keyColumnName, m_columnNames[0], m_columnNames[1], m_columnNames[2]));

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(query.lastError().text().toStdString(), __FILE__, __LINE__));
  
  return this;
}

std::vector<StaticGameObject> StaticGORepository::QueryToEntities(QSqlQuery* query)
{
  QSqlRecord record = query->record();

  std::vector<StaticGameObject> result;
  while (query->next())
  {
    StaticGameObject gameObject;

    gameObject.id = query->value(record.indexOf(m_keyColumnName)).toInt();
    gameObject.name = query->value(record.indexOf(m_columnNames[0])).toString();
    gameObject.modelFileName = query->value(record.indexOf(m_columnNames[1])).toString();
    gameObject.materialFileName = query->value(record.indexOf(m_columnNames[2])).toString();

    result.push_back(gameObject);
  }
  return result;
}

QString StaticGORepository::GetFieldByName(const StaticGameObject& entity, QString name)
{
  if (name == m_columnNames[0])
    return entity.name;

  if (name == m_columnNames[1])
    return entity.modelFileName;

  if (name == m_columnNames[2])
    return entity.materialFileName;

  if (name == m_keyColumnName)
    return QString::number(entity.id);

  throw std::runtime_error(Logger::get().GetErrorTraceMessage(("There is no field with name = " + name + " in entity").toStdString(), __FILE__, __LINE__));
}