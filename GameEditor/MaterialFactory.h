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

class MaterialFactory : public SharedResourcesFactory<IMaterial>, public Singleton<MaterialFactory>
{
  friend class Singleton<MaterialFactory>;
private:
  std::vector<IMaterialCreator* > m_materialCreators;
protected:
  MaterialFactory();
  virtual ~MaterialFactory();
  IMaterial* GetNewResource(const std::string& filename) override;
public:
  void Initialize();
};

