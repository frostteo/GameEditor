#include "MapEditorPreferences.h"

const std::string MapEditorPreferences::m_preferencesFileName = "map_editor.ini";

MapEditorPreferences::MapEditorPreferences()
{
  std::string fileInstr;
  FileProcessor::GetFileAsString(m_preferencesFileName, fileInstr);
  if (fileInstr.empty())
    return;

  ReadPreferencesFromStr(fileInstr);

  m_testLightiningSystem = std::unique_ptr<LightininigSystem>(new LightininigSystem());
  m_testLightiningSystem->SetAmbientColor(m_redAmbientTestLightColor, m_greenAmbientTestLightColor, m_blueAmbientTestLightColor, 1.0f);
  m_testLightiningSystem->SetDirectLightColor(m_redDirectTestLightColor, m_greenDirectTestLightColor, m_blueDirectTestLightColor, 1.0f);
  m_testLightiningSystem->SetDirectLightDirection(m_xDirectTestLightDirection, m_yDirectTestLightDirection, m_zDirectTestLightDirection);
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

  ss >> place >> m_redAmbientTestLightColor;
  ss >> place >> m_blueAmbientTestLightColor;
  ss >> place >> m_greenAmbientTestLightColor;

  ss >> place >> m_redDirectTestLightColor;
  ss >> place >> m_blueDirectTestLightColor;
  ss >> place >> m_greenDirectTestLightColor;

  ss >> place >> m_xDirectTestLightDirection;
  ss >> place >> m_yDirectTestLightDirection;
  ss >> place >> m_zDirectTestLightDirection;

  ss >> place >> std::boolalpha >> m_useTestLightining;
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

  fout << "red_ambient_test_light_color: " << m_redAmbientTestLightColor << std::endl;
  fout << "green_ambient_test_light_color: " << m_greenAmbientTestLightColor << std::endl;
  fout << "blue_ambient_test_light_color: " << m_blueAmbientTestLightColor << std::endl;

  fout << "red_direct_test_light_color: " << m_redDirectTestLightColor << std::endl;
  fout << "green_direct_test_light_color: " << m_greenDirectTestLightColor << std::endl;
  fout << "blue_direct_test_light_color: " << m_blueDirectTestLightColor << std::endl;

  fout << "x_direct_test_light_direction: " << m_xDirectTestLightDirection << std::endl;
  fout << "y_direct_test_light_direction: " << m_yDirectTestLightDirection << std::endl;
  fout << "z_direct_test_light_direction: " << m_zDirectTestLightDirection << std::endl;

  fout << "use_test_lightining: " << std::boolalpha << m_useTestLightining << std::endl;
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

void MapEditorPreferences::SetAmbientTestLightColor(float red, float green, float blue)
{
  if (red >= 0.0f && red <= 1.0f)
    m_redAmbientTestLightColor = red;

  if (green >= 0.0f && green <= 1.0f)
    m_greenAmbientTestLightColor = green;

  if (blue >= 0.0f && blue <= 1.0f)
    m_blueAmbientTestLightColor = blue;

  m_testLightiningSystem->SetAmbientColor(m_redAmbientTestLightColor, m_greenAmbientTestLightColor, m_blueAmbientTestLightColor, 1.0f);
}

void MapEditorPreferences::SetDirectTestLightColor(float red, float green, float blue)
{
  if (red >= 0.0f && red <= 1.0f)
    m_redDirectTestLightColor = red;

  if (green >= 0.0f && green <= 1.0f)
    m_greenDirectTestLightColor = green;

  if (blue >= 0.0f && blue <= 1.0f)
    m_blueDirectTestLightColor = blue;

  m_testLightiningSystem->SetDirectLightColor(m_redDirectTestLightColor, m_greenDirectTestLightColor, m_blueDirectTestLightColor, 1.0f);
}

void MapEditorPreferences::SetDirectTestLightDirection(float x, float y, float z)
{
  m_xDirectTestLightDirection = x;
  m_yDirectTestLightDirection = y;
  m_zDirectTestLightDirection = z;

  m_testLightiningSystem->SetDirectLightDirection(m_xDirectTestLightDirection, m_yDirectTestLightDirection, m_zDirectTestLightDirection);
}