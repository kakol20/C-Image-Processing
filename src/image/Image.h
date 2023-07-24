#pragma once

#include <cstdint>

#include "Color.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

class Image {
public:
	enum class Interpolation { Linear, Closest, Cubic };
	enum class Extrapolation { Repeat, Extend, Clip };
	//enum class ColorSpace { Non_Color, sRGB };

	enum class FileType { PNG, JPG, BMP, TGA, NONE };

public:
	//Image(const char* file, const Interpolation interpolation = Interpolation::Linear, const Extrapolation exterapolation = Extrapolation::Repeat);
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="channels">1 = Grayscale, 2 = Grayscale with Alpha, 3 = RGB, 4 = RGB with Alpha</param>
	/// <param name="interpolation"></param>
	/// <param name="exterapolation"></param>
	Image(const unsigned int w = 0, const unsigned int h = 0, const uint8_t channels = 4, const Interpolation interpolation = Interpolation::Linear, const Extrapolation extrapolation = Extrapolation::Repeat);

	Image(const Image& other);

	// ----- ASSIGNMENT -----

	Image& operator=(const Image& other);

	// ----- GETTERS & SETTERS -----

	Color GetPixel(const float x, const float y) const;
	void SetPixel(const Color& col, const float x, const float y);

	// ----- READ & WRITE -----

	bool Write(const char* file);

	~Image();

private:
	unsigned int m_w, m_h;
	uint8_t m_channels;
	size_t m_size;

	Interpolation m_interpolation;
	Extrapolation m_extrapolation;

	Color* m_data;

	// ----- OTHER -----

	FileType GetFileType(const char* file);
	size_t GetIndex(unsigned int x, unsigned int y);
};