#pragma once

#include "StaticGameObject.h"
#include "Camera.h"

class LookAtObjectFromHelper
{
protected:
  static void LookToObjectFromHelper(StaticGameObject* gameObject, float& newWidth, float& newHeight, float& newDepth, XMVECTOR& newObjectCenter);
public:
  LookAtObjectFromHelper();
  virtual ~LookAtObjectFromHelper();
  static void LookToObjectFromWorldFront(Camera* camera, StaticGameObject* gameObject);
  static void LookToObjectFromWorldUp(Camera* camera, StaticGameObject* gameObject);
};

