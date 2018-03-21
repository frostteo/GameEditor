#pragma once

#include <cstdlib>
#include <math.h>
#include "InputListener.h"
#include "MapEditorPreferences.h"

class Logger;
class Camera;
class StaticGameObject;

class PreviewGameObject :
  public InputListener
{
protected:
  const float m_rotateCoef = 0.01f;
  const float m_autoRotateYAngle = 50.0f;
  MapEditorPreferences* m_preferences;
  Camera* m_camera;
  StaticGameObject* m_sgo;
  bool m_autoRotateSwicher;
  float m_timeInSecondsBetweenFrames;
public:
  PreviewGameObject(Camera* camera, StaticGameObject* sgo, MapEditorPreferences* preferences);
  virtual ~PreviewGameObject();
  void SetCamera(Camera* camera) { m_camera = camera; }
  void SetSGO(StaticGameObject* sgo) { m_sgo = sgo; }
  void SetMapEditorPreferences(MapEditorPreferences* preferences) { m_preferences = preferences; }
  virtual void ProcessUserInput(const InputState* inputState) override;
};

