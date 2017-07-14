#include "Texture.h"


Texture::Texture()
{
  m_targaData = nullptr;
  m_texture = nullptr;
  m_textureView = nullptr;
}


Texture::~Texture()
{
  Shutdown();
}

bool Texture::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::string& filename)
{
  bool result;
  int height, width;
  D3D11_TEXTURE2D_DESC textureDesc;
  HRESULT hResult;
  unsigned int rowPitch;
  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
  m_filename = filename;

  // Load the targa image data into memory.
  result = LoadTarga(height, width);
  if (!result)
  {
    return false;
  }

  // Setup the description of the texture.
  textureDesc.Height = height;
  textureDesc.Width = width;
  textureDesc.MipLevels = 0;
  textureDesc.ArraySize = 1;
  textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  textureDesc.SampleDesc.Count = 1;
  textureDesc.SampleDesc.Quality = 0;
  textureDesc.Usage = D3D11_USAGE_DEFAULT;
  textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
  textureDesc.CPUAccessFlags = 0;
  textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

  // Create the empty texture.
  hResult = device->CreateTexture2D(&textureDesc, NULL, &m_texture);
  if (FAILED(hResult))
  {
    return false;
  }

  // Setup the description of the texture.
  textureDesc.Height = height;
  textureDesc.Width = width;
  textureDesc.MipLevels = 0;
  textureDesc.ArraySize = 1;
  textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  textureDesc.SampleDesc.Count = 1;
  textureDesc.SampleDesc.Quality = 0;
  textureDesc.Usage = D3D11_USAGE_DEFAULT;
  textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
  textureDesc.CPUAccessFlags = 0;
  textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

  // Create the empty texture.
  hResult = device->CreateTexture2D(&textureDesc, NULL, &m_texture);
  if (FAILED(hResult))
  {
    return false;
  }

  // Set the row pitch of the targa image data.
  rowPitch = (width * Texture::countOfByteForPixel) * sizeof(unsigned char);

  // Copy the targa image data into the texture.
  deviceContext->UpdateSubresource(m_texture, 0, NULL, m_targaData, rowPitch, 0);

  // Setup the shader resource view description.
  srvDesc.Format = textureDesc.Format;
  srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  srvDesc.Texture2D.MostDetailedMip = 0;
  srvDesc.Texture2D.MipLevels = -1;

  // Create the shader resource view for the texture.
  hResult = device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView);
  if (FAILED(hResult))
  {
    return false;
  }

  // Generate mipmaps for this texture.
  deviceContext->GenerateMips(m_textureView);

  // Release the targa image data now that the image data has been loaded into the texture.
  delete[] m_targaData;
  m_targaData = 0;

  return true;
}

void Texture::Shutdown()
{
  // Release the texture view resource.
  if (m_textureView)
  {
    m_textureView->Release();
    m_textureView = 0;
  }

  // Release the texture.
  if (m_texture)
  {
    m_texture->Release();
    m_texture = 0;
  }

  // Release the targa data.
  if (m_targaData)
  {
    delete[] m_targaData;
    m_targaData = 0;
  }

  return;
}

ID3D11ShaderResourceView* Texture::GetTexture()
{
  return m_textureView;
}

bool Texture::LoadTarga(int& height, int& width)
{
  const int tgbFormatBitCount = 32;
  const int doubleCountOfByteForPixel = Texture::countOfByteForPixel * 2;

  int bpp, imageSize, index, i, j, k;
  bool result;
  unsigned int count;
  TargaHeader targaFileHeader;
  std::unique_ptr<char []> targaImage;
  std::string fileInStr;


  result = FileProcessor::GetFileAsString(m_filename, fileInStr);
  if (!result)
  {
    return false;
  }

  std::stringstream fileStrStream(fileInStr);
  fileStrStream.read(reinterpret_cast<char *>(&targaFileHeader), sizeof(TargaHeader));

  // Get the important information from the header.
  height = (int)targaFileHeader.height;
  width = (int)targaFileHeader.width;
  bpp = (int)targaFileHeader.bpp;

  // Check that it is 32 bit and not 24 bit.
  if (bpp != tgbFormatBitCount)
  {
    return false;
  }

  // Calculate the size of the 32 bit image data.
  imageSize = width * height * Texture::countOfByteForPixel;

  // Allocate memory for the targa image data.
  targaImage = std::unique_ptr<char []>(new char[imageSize]);
  if (!targaImage)
  {
    return false;
  }

  fileStrStream.read(targaImage.get(), imageSize);

  if (!fileStrStream)
  {
    return false;
  }

  // Allocate memory for the targa destination data.
  m_targaData = new unsigned char[imageSize];
  if (!m_targaData)
  {
    return false;
  }

  // Initialize the index into the targa destination data array.
  index = 0;

  // Initialize the index into the targa image data.
  k = (width * height * Texture::countOfByteForPixel) - (width * Texture::countOfByteForPixel);

  // Now copy the targa image data into the targa destination array in the correct order since the targa format is stored upside down.
  for (j = 0; j < height; j++)
  {
    for (i = 0; i < width; i++)
    {
      m_targaData[index + 0] = targaImage[k + 2];  // Red.
      m_targaData[index + 1] = targaImage[k + 1];  // Green.
      m_targaData[index + 2] = targaImage[k + 0];  // Blue
      m_targaData[index + 3] = targaImage[k + 3];  // Alpha

      // Increment the indexes into the targa data.
      k += Texture::countOfByteForPixel;
      index += Texture::countOfByteForPixel;
    }

    // Set the targa image data index back to the preceding row at the beginning of the column since its reading it in upside down.
    k -= (width * doubleCountOfByteForPixel);
  }

  return true;
}