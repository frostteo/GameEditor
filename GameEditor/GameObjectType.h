#pragma once

#include <string>

enum GameObjectType
{
  ALL = -1,
  STATIC_GAME_OBJECT = 0,
  POINT_LIGHT = 1
};

std::string GameObjectTypeToString(const GameObjectType& type);