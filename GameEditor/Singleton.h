#pragma once

#include "Uncopyable.h"

template<typename T> class Singleton : private Uncopyable
{
protected:
  Singleton<T>() = default;
  ~Singleton<T>() = default;
public:
  static T& get()
  {
    static T theSingleInstance; // class T must have default constructor
    return theSingleInstance;
  }
};

