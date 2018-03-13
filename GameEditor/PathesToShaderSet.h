#pragma once

#include <string>

struct PathesToShaderSet
{
  std::string pathToVertexShader;
  std::string pathToGeometricShader;
  std::string pathToHullShader;
  std::string pathToDomainShader;
  std::string pathToPixelShader;

  std::string shaderNameParam;
};