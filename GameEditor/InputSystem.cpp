#include "InputSystem.h"
#include "Logger.h"
#include "HighPerformanceTimer.h"

InputSystem::InputSystem()
  : m_listenersList(),
  m_directInput(nullptr),
  m_keyboard(nullptr),
  m_mouse(nullptr),
  m_inputState(),
  m_timer(new HighPerformanceTimer)
{
}

InputSystem::~InputSystem()
{
  Shutdown();
}

void InputSystem::Initialize(HINSTANCE hinstance , HWND hwnd)
{
  HRESULT result;
  m_hwnd = hwnd;

  m_timer->Initialize();

  // Initialize the main direct input interface.
  result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
  if (FAILED(result))
    RUNTIME_ERROR("cannot create direct input object.");

  // Initialize the direct input interface for the keyboard.
  result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
  if (FAILED(result))
    RUNTIME_ERROR("cant initialize direct input interface for the keybord.");

  // Set the data format.  In this case since it is a keyboard we can use the predefined data format.
  result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
  if (FAILED(result))
    RUNTIME_ERROR("cant set data format.");

  // Set the cooperative level of the keyboard to not share with other programs.
  result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
  if (FAILED(result))
    RUNTIME_ERROR("cant set cooperative lvl.");

  // Initialize the direct input interface for the mouse.
  result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
  if (FAILED(result))
    RUNTIME_ERROR("cant create direct input mouse.");

  // Set the data format for the mouse using the pre-defined mouse data format.
  result = m_mouse->SetDataFormat(&c_dfDIMouse);
  if (FAILED(result))
    RUNTIME_ERROR("cant set mouse data format.");

  // Set the cooperative level of the mouse to share with other programs.
  result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
  if (FAILED(result))
    RUNTIME_ERROR("cant set cooperative lvl.");
}

void InputSystem::Shutdown()
{
  // Release the mouse.
  if (m_mouse)
  {
    m_mouse->Unacquire();
    m_mouse->Release();
    m_mouse = 0;
  }

  // Release the keyboard.
  if (m_keyboard)
  {
    m_keyboard->Unacquire();
    m_keyboard->Release();
    m_keyboard = 0;
  }

  // Release the main interface to direct input.
  if (m_directInput)
  {
    m_directInput->Release();
    m_directInput = 0;
  }

  ClearListenersList();
}

bool InputSystem::ReadKeyboard()
{
  HRESULT result;

  // Read the keyboard device.
  result = m_keyboard->GetDeviceState(sizeof(m_inputState.m_keyboardState), (LPVOID)&m_inputState.m_keyboardState);
  if (FAILED(result))
  {
    // If the keyboard lost focus or was not acquired then try to get control back.
    if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
    {
      m_keyboard->Acquire();
    }
    //TODO FHolod: не уведомляю пользователя о не получении клавиатуры
    return false;
  }
  return true;
}

bool InputSystem::ReadMouse()
{
  HRESULT result;

  POINT cursorPos;

  if (GetCursorPos(&cursorPos) && ScreenToClient(m_hwnd, &cursorPos))
  {
    m_inputState.mouseXCoor = cursorPos.x;
    m_inputState.mouseYCoor = cursorPos.y;
  }

  // Read the mouse device.
  result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_inputState.m_mouseState);
  if (FAILED(result))
  {
    // If the mouse lost focus or was not acquired then try to get control back.
    if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
    {
      m_mouse->Acquire();
    }
    //TODO FHolod: пользователь не уведомляется о не получении устройства мыши
    return false;
  }
  return true;
}

void InputSystem::Frame()
{
  m_timer->Frame();
  m_inputState.time = m_timer->GetTime();
  if (ReadKeyboard() && ReadMouse())
  {
    for (auto listener : m_listenersList)
    {
      if (listener)
        listener->ProcessUserInput(&m_inputState);
    }
  }
  memcpy(m_inputState.m_previousKeyboardState, m_inputState.m_keyboardState, InputState::countOfKeyboardKeys);
  memcpy(m_inputState.m_previousMouseBtnState, m_inputState.m_mouseState.rgbButtons, InputState::countOfMouseKeys);
}

void InputSystem::RemoveInputListener(const std::string name)
{
  auto lambda = [name](std::shared_ptr<InputListener> listener) -> bool { return listener->GetName() == name; };
  m_listenersList.remove_if(lambda);
}

void InputSystem::RemoveInputListener(std::shared_ptr<InputListener> inputListener)
{
  m_listenersList.remove(inputListener);
}

void InputSystem::ClearListenersList()
{
  m_listenersList.clear();
}