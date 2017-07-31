#pragma once

#include <QtSql>
#include <string>
#include <qstring.h>
#include <qtextcodec.h>

class QtUtils
{
public:
  QtUtils();
  ~QtUtils();
  static std::string SqlErrorToStr(QSqlError& error) { return error.text().toLocal8Bit().constData(); }
  static std::string QStringToStdStr(QString str) { return str.toLocal8Bit().constData(); }
  static QString ToRussian(const char* str){
    return QTextCodec::codecForName("CP1251")->toUnicode(str);
  }
  static QString QStringToRussian(QString str){
    return QTextCodec::codecForName("CP1251")->toUnicode((str.toLocal8Bit().constData()));
  }
};

