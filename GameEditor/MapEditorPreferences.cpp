#include "MapEditorPreferences.h"


MapEditorPreferences::MapEditorPreferences()
{
}


MapEditorPreferences::~MapEditorPreferences()
{
}

void MapEditorPreferences::SetAngleSnap(float angle)
{
  if (angle > 0.0f) 
    m_angleSnap = fmod(angle, 360.0f);
}

void MapEditorPreferences::SetGridSnapSize(float size)
{
  if (size > 0.0f)
    m_gridSnap = size;
}