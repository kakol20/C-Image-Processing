#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

#include "Image.h"

#include "../../ext/stb/stb_image.h"
#include "../../ext/stb/stb_image_write.h"

Image::Image(const unsigned int w, const unsigned int h, const int channels, const Interpolation interpolation, const Extrapolation extrapolation) {
	m_w = w;
	m_h = h;
	m_channels = channels;
	m_interpolation = interpolation;
	m_extrapolation = extrapolation;

	delete[] m_data;
	m_data = nullptr;

	m_size = (size_t)m_w * m_h;
	m_data = new Color[m_size];

	for (size_t i = 0; i < m_size; i++) {
		m_data[i] = Color(0.f, 0.f, 0.f, 1.f);
	}
}

Image::Image(const Image& other) {
	m_w = other.m_w;
	m_h = other.m_h;
	m_channels = other.m_channels;
	m_interpolation = other.m_interpolation;
	m_extrapolation = other.m_extrapolation;

	delete[] m_data;
	m_data = nullptr;

	m_size = (size_t)m_w * m_h;
	m_data = new Color[m_size];

	memcpy(m_data, other.m_data, m_size);
}

Image& Image::operator=(const Image& other) {
	if (this == &other) return *this;

	m_w = other.m_w;
	m_h = other.m_h;
	m_channels = other.m_channels;
	m_interpolation = other.m_interpolation;
	m_extrapolation = other.m_extrapolation;

	delete[] m_data;
	m_data = nullptr;

	m_size = (size_t)m_w * m_h;
	m_data = new Color[m_size];

	memcpy(m_data, other.m_data, m_size);

	return *this;
}

Color Image::GetPixel(const float x, const float y) const {
	return Color();
}
void Image::SetPixel(const Color& col, const float x, const float y) {
	unsigned int l_x = 0, l_y = 0;

	int x_r = 0, y_r = 0;

	switch (m_extrapolation) {
	case Image::Extrapolation::Repeat:
		x_r = (int)std::roundf(x * (float)m_w);
		y_r = (int)std::roundf(y * (float)m_h);

		x_r = ((x_r % (int)m_w) + (int)m_w) % (int)m_w;
		y_r = ((y_r % (int)m_h) + (int)m_h) % (int)m_h;

		x_r = std::clamp(x_r, 0, (int)m_w - 1);
		y_r = std::clamp(y_r, 0, (int)m_h - 1);

		l_x = (unsigned int)x_r;
		l_y = (unsigned int)y_r;
		break;
	case Image::Extrapolation::Extend:
		x_r = (int)std::roundf(x * (float)m_w);
		y_r = (int)std::roundf(y * (float)m_h);

		x_r = std::clamp(x_r, 0, (int)m_w - 1);
		y_r = std::clamp(y_r, 0, (int)m_h - 1);

		l_x = (unsigned int)x_r;
		l_y = (unsigned int)y_r;
		break;
	case Image::Extrapolation::Clip:
		break;
	default:
		x_r = (int)std::roundf(x * (float)m_w);
		y_r = (int)std::roundf(y * (float)m_h);

		x_r = ((x_r % (int)m_w) + (int)m_w) % (int)m_w;
		y_r = ((y_r % (int)m_h) + (int)m_h) % (int)m_h;

		x_r = std::clamp(x_r, 0, (int)m_w - 1);
		y_r = std::clamp(y_r, 0, (int)m_h - 1);

		l_x = (unsigned int)x_r;
		l_y = (unsigned int)y_r;
		break;
	}

	if (m_extrapolation != Extrapolation::Clip) {
		size_t index = GetIndex(l_x, l_y);

		m_data[index] = col;
	}
}

bool Image::Read(const char* file, const int forceChannels) {
	uint8_t* data = NULL;
	if (forceChannels <= 0 && forceChannels > 4) {
		data = stbi_load(file, &m_w, &m_h, &m_channels, 0);
	}
	else {
		data = stbi_load(file, &m_w, &m_h, &m_channels, forceChannels);

	}

	if (data == NULL) return false;

	stbi_image_free(data);
	return true;
}

bool Image::Write(const char* file) {
	FileType type = GetFileType(file);

	// Create data that stb_image can read
	size_t size = (size_t)(m_w * m_h) * (size_t)m_channels;
	uint8_t* data = new uint8_t[size];

	for (unsigned int y = 0; y < m_w; y++) {
		for (unsigned int x = 0; x < m_h; x++) {
			size_t stb_index = (size_t)(x + y * m_w) * (size_t)m_channels;
			size_t data_index = GetIndex(x, y);

			Color col = m_data[data_index].GetClamp();
			col *= 255.f;

			if (m_channels == 1) {
				// grayscale
				data[stb_index] = (uint8_t)std::roundf(col.GetR());
			}
			else if (m_channels == 2) {
				// grayscale with alpha
				data[stb_index] = (uint8_t)std::roundf(col.GetR());
				data[stb_index + 1] = (uint8_t)std::roundf(col.GetA());
			}
			else if (m_channels == 3) {
				// rgb
				data[stb_index] = (uint8_t)std::roundf(col.GetR());
				data[stb_index + 1] = (uint8_t)std::roundf(col.GetG());
				data[stb_index + 2] = (uint8_t)std::roundf(col.GetB());
			}
			else {
				// rgb with alpha
				data[stb_index] = (uint8_t)std::roundf(col.GetR());
				data[stb_index + 1] = (uint8_t)std::roundf(col.GetG());
				data[stb_index + 2] = (uint8_t)std::roundf(col.GetB());
				data[stb_index + 3] = (uint8_t)std::roundf(col.GetA());
			}
		}
	}

	int success = 0;
	const int w = (int)m_w;
	const int h = (int)m_h;
	const int channels = (int)m_channels;
	switch (type) {
	case Image::FileType::PNG:
		success = stbi_write_png(file, w, h, channels, data, w * channels);
		break;
	case Image::FileType::JPG:
		success = stbi_write_jpg(file, w, h, channels, data, 100);
		break;
	case Image::FileType::BMP:
		success = stbi_write_bmp(file, w, h, channels, data);
		break;
	case Image::FileType::TGA:
		success = stbi_write_tga(file, w, h, channels, data);
		break;
	case Image::FileType::NONE:
		success = -1;
		break;
	default:
		success = 0;
		break;
	}

#ifdef _DEBUG
	if (success == 0) {
		std::cout << "Error writing file: " << file << '\n';
	}
	else if (success == -1) {
		std::cout << "File type not supported - PNG, JPG, BMP or TGA: " << file << '\n';
	}
	else {
		std::cout << "Write image successful: " << file << '\n';
	}
#endif // _DEBUG

	stbi_image_free(data);

	return success != 0;
}

Image::~Image() {
	delete[] m_data;
	m_data = nullptr;
}

Image::FileType Image::GetFileType(const char* file) {
	std::string l_file = file;
	std::string type = "";

	bool firstOut = true;
	for (auto c : l_file) {
		if (firstOut) {
			if (c == '.') firstOut = false;
		}
		else {
			type += c;
		}
	}

	if (type.length() != 0) {
		if (type == "bmp") {
			return Image::FileType::BMP;
		}
		else if (type == "jpg") {
			return Image::FileType::JPG;
		}
		else if (type == "png") {
			return Image::FileType::PNG;
		}
		else if (type == "tga") {
			return Image::FileType::TGA;
		}
		else {
			return Image::FileType::NONE;
		}
	}
	return Image::FileType::NONE;
}

size_t Image::GetIndex(unsigned int x, unsigned int y) {
	return (size_t)(x + y * m_w);
}