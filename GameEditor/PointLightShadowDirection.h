#pragma once

enum PointLightShadowDirection : int {
  PLUS_X  = 1,
  MINUS_X = 2,
  PLUS_Y = 4,
  MINUS_Y = 8,
  PLUS_Z = 16,
  MINUS_Z = 32
};

inline PointLightShadowDirection operator |(PointLightShadowDirection a, PointLightShadowDirection b)
{
  return a | b;
}

inline PointLightShadowDirection operator &(PointLightShadowDirection a, PointLightShadowDirection b)
{
  return a & b;
}

inline PointLightShadowDirection& operator |=(PointLightShadowDirection& a, PointLightShadowDirection b)
{
  return a = a | b;
}