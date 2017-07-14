#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <d3d11.h>
#include <directxmath.h>
#include <fstream>
#include "Mesh.h"
#include "Texture.h"
#include "MeshFactory.h"
#include "TextureFactory.h"

using namespace DirectX;
using namespace std;

class ModelClass
{
private:
  struct VertexType
  {
    XMFLOAT3 position;
    XMFLOAT2 texture;
    XMFLOAT3 normal;
    XMFLOAT3 tangent;
    XMFLOAT3 binormal;
  };

  struct ModelType
  {
    float x, y, z;
    float tu, tv;
    float nx, ny, nz;
    float tx, ty, tz;
    float bx, by, bz;
  };

  struct TempVertexType
  {
    float x, y, z;
    float tu, tv;
    float nx, ny, nz;
  };

  struct VectorType
  {
    float x, y, z;
  };

public:
  ModelClass();
  ModelClass(const ModelClass&);
  ~ModelClass();
  bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char*, char*);
  void Shutdown();
  void Render(ID3D11DeviceContext*);

  int GetIndexCount();
  ID3D11ShaderResourceView* GetTexture();

private:
  void RenderBuffers(ID3D11DeviceContext*);

private:
  Mesh* m_Mesh;
  Texture* m_Texture;
};

#endif
