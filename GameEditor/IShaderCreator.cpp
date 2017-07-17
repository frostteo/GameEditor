#include "IShaderCreator.h"


IShaderCreator::~IShaderCreator()
{
  if (m_shader) {
    delete m_shader;
    m_shader = nullptr;
  }
}
