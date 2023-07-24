#include <algorithm>

#include "Image.h"

Image::Image(const unsigned int w, const unsigned int h, const uint8_t channels, const Interpolation interpolation, const Extrapolation extrapolation) {
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

Image::~Image() {
	delete[] m_data;
	m_data = nullptr;
}
