#pragma once

template<typename T> class Singleton
{
public:
  static T& get()
  {
    static T theSingleInstance; // class T must have default constructor
    return theSingleInstance;
  }
};

