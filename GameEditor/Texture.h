#pragma once

#include <d3d11.h>
#include <string>
#include <memory>
#include <sstream>
#include "FileProcessor.h"

class Logger;

class Texture
{
private:
  struct TargaHeader
  {
    unsigned char data1[12];
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char data2;
  };
private:
  const static int countOfByteForPixel = 4;
  unsigned char* m_targaData;
  ID3D11Texture2D* m_texture;
  ID3D11ShaderResourceView* m_textureView;
  std::string m_filename;
protected:
  bool LoadTarga(int& height, int& width);
public:
  Texture();
  virtual ~Texture();
  bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::string& filename);
  void Shutdown();
  ID3D11ShaderResourceView* GetTexture();
};

