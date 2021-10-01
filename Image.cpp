#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

Image::Image(const char* fileName)
{
	if (!Read(fileName)) {
		//printf_s("Read Failed %s\n", fileName);
		std::cout << "Read Failed " << fileName << std::endl;
		m_size = m_w * m_h * m_channels;
	}
	else {
		std::cout << "Read Success " << fileName << std::endl;
	}
}

Image::Image(int w, int h, int channels)
{
	m_w = w;
	m_h = h;
	m_channels = channels;

	m_size = m_w * m_h * m_channels;
	m_data = new uint8_t[m_size];

	for (int i = 0; i < m_size; i++)
	{
		m_data[i] = 0;
	}
}

Image::Image(const Image& copyImage)
{
	stbi_image_free(m_data);

	m_w = copyImage.m_w;
	m_h = copyImage.m_h;
	m_channels = copyImage.m_channels;

	m_size = m_w * m_h * m_channels;
	m_data = new uint8_t[m_size];

	memcpy(m_data, copyImage.m_data, m_size);
}

Image Image::operator=(const Image& copyImage)
{
	if (&copyImage == this) return *this;

	stbi_image_free(m_data);

	m_w = copyImage.m_w;
	m_h = copyImage.m_h;
	m_channels = copyImage.m_channels;

	m_size = m_w * m_h * m_channels;
	m_data = new uint8_t[m_size];
	
	memcpy(m_data, copyImage.m_data, m_size);

	return *this;
}

/// <summary>
/// Read Image
/// </summary>
/// <param name="fileName"></param>
/// <returns></returns>
bool Image::Read(const char* fileName)
{
	m_data = stbi_load(fileName, &m_w, &m_h, &m_channels, 0);
	
	return m_data != NULL;
}

/// <summary>
/// Write Image
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
bool Image::Write(const char* fileName)
{
	ImageType type = GetFileType(fileName);
	int success = 0;

	switch (type)
	{
	case ImageType::PNG:
		success = stbi_write_png(fileName, m_w, m_h, m_channels, m_data, m_w * m_channels);
		break;

	case ImageType::JPG:
		success = stbi_write_jpg(fileName, m_w, m_h, m_channels, m_data, 100);
		break;

	case ImageType::BMP:
		success = stbi_write_bmp(fileName, m_w, m_h, m_channels, m_data);
		break;
		
	case ImageType::TGA:
		success = stbi_write_tga(fileName, m_w, m_h, m_channels, m_data);
		break;
	}

	if (success != 0)
	{
		std::cout << "Write Success " << fileName << std::endl;
	}
	else
	{
		std::cout << "Write Fail " << fileName << std::endl;
	}

	return success != 0;
}

int Image::GetRow()
{
	return m_w * m_channels;
}

int Image::GetIndex(int x, int y)
{
	return (x + y * m_w) * m_channels;
}
size_t Image::GetSize()
{
	return m_size;
}

uint8_t Image::GetData(int index)
{
	return m_data[index];
}

void Image::SetData(int index, uint8_t data)
{
	m_data[index] = data;
}

Image::~Image()
{
	stbi_image_free(m_data);
}

ImageType Image::GetFileType(const char* fileName)
{
	const char* ext = strrchr(fileName, '.');

	if (ext != nullptr)
	{
		if (strcmp(ext, ".png") == 0)
		{
			return ImageType::PNG;
		}
		else if (strcmp(ext, ".jpg") == 0)
		{
			return ImageType::JPG;
		}
		else if (strcmp(ext, ".bmp") == 0)
		{
			return ImageType::BMP;
		}
		else if (strcmp(ext, ".tga") == 0)
		{
			return ImageType::TGA;
		}
	}

	return ImageType::PNG;
}
