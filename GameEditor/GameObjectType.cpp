#include "GameObjectType.h"

std::string GameObjectTypeToString(const GameObjectType& type)
{
  switch (type)
  {
  case STATIC_GAME_OBJECT:
    return "static game object";
    break;
  case POINT_LIGHT:
    return "point light";
    break;
  }
  return "";
}