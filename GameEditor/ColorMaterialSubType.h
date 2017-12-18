#pragma once

enum class ColorMaterialSubType {
  ONLY_COLOR = 0,
  COLOR_SPECULAR = 1,
  COLOR_SELFILUM = 2,
  COLOR_TRANSPARENT = 4
};

inline ColorMaterialSubType operator|(ColorMaterialSubType a, ColorMaterialSubType b)
{
  return static_cast<ColorMaterialSubType>(static_cast<int>(a) | static_cast<int>(b));
}

inline ColorMaterialSubType operator &(ColorMaterialSubType a, ColorMaterialSubType b)
{
  return static_cast<ColorMaterialSubType>(static_cast<int>(a)& static_cast<int>(b));
}

inline ColorMaterialSubType& operator |=(ColorMaterialSubType& a, ColorMaterialSubType b)
{
  return a = a | b;
}