#pragma once

#include <dinput.h>
#include <string>
#include "InputState.h"

class InputState;

class InputListener
{
protected:
  std::string m_name;
public:
  InputListener();
  virtual ~InputListener();
  virtual void ProcessUserInput(const InputState* inputState) = 0;
  bool operator== (const InputListener& other) const { return this->m_name == other.m_name; }
  const std::string GetName() const { return m_name; }
};

