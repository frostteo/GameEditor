#include "MapEditorPreferences.h"

const std::string MapEditorPreferences::m_preferencesFileName = "map_editor.ini";

MapEditorPreferences::MapEditorPreferences()
{
  std::string fileInstr;
  FileProcessor::GetFileAsString(m_preferencesFileName, fileInstr);
  if (fileInstr.empty())
    return;

  ReadPreferencesFromStr(fileInstr);
}

void MapEditorPreferences::ReadPreferencesFromStr(std::string& str)
{
  std::string place;
  std::stringstream ss(str);

  ss >> place >> m_objectRotationSpeed;
  ss >> place >> m_objectMoveSpeed;
  ss >> place >> m_cameraRotationSpeed;
  ss >> place >> m_cameraZoomSpeed;
  ss >> place >> m_cameraPanSpeed;
  ss >> place >> m_gridSnapSize;
  ss >> place >> m_angleSnap;
  ss >> place >> std::boolalpha >> m_snapToGrid;
  ss >> place >> std::boolalpha >> m_snapToAngle;
}

MapEditorPreferences::~MapEditorPreferences()
{
  std::ofstream fout(m_preferencesFileName);

  fout << "object_rotation_speed: " << m_objectRotationSpeed << std::endl;
  fout << "object_move_speed: " << m_objectMoveSpeed << std::endl;
  fout << "camera_rotation_speed: " << m_cameraRotationSpeed << std::endl;
  fout << "camera_zoom_speed: " << m_cameraZoomSpeed << std::endl;
  fout << "camera_pan_speed: " << m_cameraPanSpeed << std::endl;
  fout << "grid_snap_size: " << m_gridSnapSize << std::endl;
  fout << "angle_snap: " << m_angleSnap << std::endl;
  fout << "snap_to_grid: " << std::boolalpha << m_snapToGrid << std::endl;
  fout << "snap_to_angle: " << std::boolalpha << m_snapToAngle << std::endl;
}

void MapEditorPreferences::SetAngleSnap(float angle)
{
  if (angle > 0.0f) 
    m_angleSnap = fmod(angle, 360.0f);
}

void MapEditorPreferences::SetGridSnapSize(float size)
{
  if (size > 0.0f)
    m_gridSnapSize = size;
}