#pragma once

#include <vector>
#include <sstream>
#include "Singleton.h"
#include "SharedResourcesFactory.h"
#include "IMaterial.h"
#include "IMaterialCreator.h"
#include "TextureMaterialCreator.h"
#include "SpecularMaterialCreator.h"
#include "BumpMaterialCreator.h"
#include "BumpSpecMaterialCreator.h"
#include "BumpSpecMapMaterialCreator.h"
#include "FileProcessor.h"
#include "Logger.h"
#include "TextureFactory.h"

class MaterialFactory : public SharedResourcesFactory<IMaterial>
{
private:
  std::vector<IMaterialCreator* > m_materialCreators;
protected:
  IMaterial* GetNewResource(const std::string& filename) override;
public:
  MaterialFactory();
  virtual ~MaterialFactory();
  MaterialFactory* Initialize(TextureFactory* textureFactory);
  void Shutdown();
};

