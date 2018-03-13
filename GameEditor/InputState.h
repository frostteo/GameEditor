#pragma once

#include <dinput.h>

enum MouseButtons
{
  LeftMouseBtn = 0,
  RightMouseBtn = 1,
  WheelMouseBtn = 2
};

struct InputState final
{
  friend class InputSystem;
protected:
  static const int countOfKeyboardKeys = 256;
  unsigned char m_keyboardState[countOfKeyboardKeys];
  unsigned char m_previousKeyboardState[countOfKeyboardKeys];

  static const int countOfMouseKeys = 4;
  unsigned char m_previousMouseBtnState[countOfMouseKeys];

public:
  float time;
  int mouseXCoor = 0;
  int mouseYCoor = 0;
  DIMOUSESTATE m_mouseState;
  bool IsKeyDown(BYTE key) const { return m_keyboardState[key] & 0x80; }
  bool IsKeyUp(BYTE key) const { return !(m_keyboardState[key] & 0x80); }
  bool IsMouseBtnDown(MouseButtons btn) const { return m_mouseState.rgbButtons[btn]; }
  bool IsMouseBtnUp(MouseButtons btn) const{ return !(m_mouseState.rgbButtons[btn]); }
  bool IsKeyPressed(BYTE key) const
  {
    if (m_keyboardState[key] & 0x80 && !(m_previousKeyboardState[key] & 0x80))
      return true;

    return false;
  }
  bool IsMouseBtnPressed(MouseButtons btn) const
  {
    if (m_mouseState.rgbButtons[btn] && !(m_previousMouseBtnState[btn]))
      return true;

    return false;
  }
  bool IsKeyReleased(BYTE key) const
  {
    if (!(m_keyboardState[key] & 0x80) && m_previousKeyboardState[key] & 0x80)
      return true;

    return false;
  }
  bool IsMouseBtnReleased(MouseButtons btn) const
  {
    if (!(m_mouseState.rgbButtons[btn]) && m_previousMouseBtnState[btn])
      return true;

    return false;
  }
  InputState() = default;
  ~InputState() = default;
};
