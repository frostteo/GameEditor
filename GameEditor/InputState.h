#pragma once

#include <dinput.h>

enum MouseButtons
{
  LeftMouseBtn = 0,
  RightMouseBtn = 1,
  WheelMouseBtn = 2
};

struct InputState
{
  friend class InputSystem;
protected:
  static const int countOfKeyboardKeys = 256;
  unsigned char m_keyboardState[countOfKeyboardKeys];
  unsigned char m_previousKeyboardState[countOfKeyboardKeys];

  static const int countOfMouseKeys = 4;
  unsigned char m_previousMouseBtnState[countOfMouseKeys];

public:
  DIMOUSESTATE m_mouseState;
  bool IsKeyDown(BYTE key) { return m_keyboardState[key] & 0x80; }
  bool IsMouseBtnDown(MouseButtons btn) { return m_mouseState.rgbButtons[btn]; }
  bool IsKeyPressed(BYTE key)
  {
    if (m_keyboardState[key] & 0x80 && !(m_previousKeyboardState[key] & 0x80))
      return true;

    return false;
  }
  bool IsMouseBtnPressed(MouseButtons btn)
  {
    if (m_mouseState.rgbButtons[btn] && !(m_previousMouseBtnState[btn]))
      return true;

    return false;
  }
  bool IsKeyReleased(BYTE key)
  {
    if (!(m_keyboardState[key] & 0x80) && m_previousKeyboardState[key] & 0x80)
      return true;

    return false;
  }
  bool IsMouseBtnReleased(MouseButtons btn)
  {
    if (!(m_mouseState.rgbButtons[btn]) && m_previousMouseBtnState[btn])
      return true;

    return false;
  }
  InputState() {}
  virtual ~InputState();
};
