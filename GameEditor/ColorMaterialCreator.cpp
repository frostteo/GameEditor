#include "ColorMaterialCreator.h"

ColorMaterialCreator::~ColorMaterialCreator()
{
}

IMaterial* ColorMaterialCreator::Get(const std::string& fileInStr, const std::string& fileName)
{
  char input;
  std::string type;
  std::string texturePath;
  std::stringstream fileStrStream(fileInStr);
  float dr, dg, db, da;
  float sr, sg, sb, sa;
  float ir, ig, ib, ia;
  float specularPower;
  float opacity;
  int subType;

  do {
    fileStrStream.get(input);
  } while (input != ':');
  fileStrStream >> type;

  if (type != m_type)
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("It is not material with color type", __FILE__, __LINE__));

  do {
    fileStrStream.get(input);
  } while (input != ':');
  fileStrStream >> dr >> dg >> db >> da;

  do {
    fileStrStream.get(input);
  } while (input != ':');
  fileStrStream >> sr >> sg >> sb >> sa;

  do {
    fileStrStream.get(input);
  } while (input != ':');
  fileStrStream >> ir >> ig >> ib >> ia;

  do {
    fileStrStream.get(input);
  } while (input != ':');
  fileStrStream >> specularPower;

  do {
    fileStrStream.get(input);
  } while (input != ':');
  fileStrStream >> opacity;

  do {
    fileStrStream.get(input);
  } while (input != ':');
  fileStrStream >> subType;

  ColorMaterial* material = new ColorMaterial(
    fileName, 
    XMVectorSet(dr, dg, db, da),
    XMVectorSet(sr, sg, sb, sa),
    XMVectorSet(ir, ig, ib, ia), 
    specularPower,
    opacity,
    static_cast<ColorMaterialSubType>(subType));

  return material;
}