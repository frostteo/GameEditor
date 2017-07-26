#pragma once

#include <dinput.h>
#include <string>
#include "InputState.h"

class InputListener
{
protected:
  std::string m_name;
public:
  InputListener();
  virtual ~InputListener();
  virtual void ProcessUserInput(InputState* inputState) = 0;
  bool operator== (const InputListener& other) const { return this->m_name == other.m_name; }
  std::string GetName() { return m_name; }
};

