#pragma once

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <memory>
#include <algorithm>
#include <list>
#include <cstring>
#include <dinput.h>

#include "InputListener.h"
#include "InputState.h"
#include "windows.h"
#include "HighPerformanceTimer.h"

class Logger;

class InputSystem
{
private:
  HWND m_hwnd;
  std::list<InputListener *> m_listenersList;
  IDirectInput8* m_directInput;
  IDirectInputDevice8* m_keyboard;
  IDirectInputDevice8* m_mouse;
  InputState m_inputState;
  std::unique_ptr<HighPerformanceTimer> m_timer;
protected:
  bool ReadKeyboard();
  bool ReadMouse();

public:
  InputSystem();
  virtual ~InputSystem();
  void Initialize(HINSTANCE hinstance, HWND hwnd);
  void Shutdown();
  void Frame();
  void ClearListenersList();
  void AddInputListener(InputListener* inputListener) {  m_listenersList.push_back(inputListener); }
  void RemoveInputListener(InputListener* inputListener);
  void RemoveInputListener(const std::string name);
};

