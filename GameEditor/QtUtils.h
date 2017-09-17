#pragma once

#include <QtSql>
#include <string>
#include <qstring.h>
#include <qtextcodec.h>

class QtUtils //TODO FHolod: maybe later delete this class
{
public:
  QtUtils();
  ~QtUtils();
  static QString ToRussian(const char* str){
    return QTextCodec::codecForName("CP1251")->toUnicode(str);
  }
  static QString QStringToRussian(QString str){
    return QTextCodec::codecForName("CP1251")->toUnicode((str.toLocal8Bit().constData()));
  }
};

