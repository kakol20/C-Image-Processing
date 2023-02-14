#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include "PPM.h"

PPM::PPM(const int& w, const int& h) {
	m_w = w;
	m_h = h;

	m_data.reserve(static_cast<size_t>(m_w * m_h * 3));

	for (int x = 0; x < m_w; x++) {
		for (int y = 0; y < m_h; y++) {
			m_data.push_back(0.f);
			m_data.push_back(0.f);
			m_data.push_back(0.f);
		}
	}
}

void PPM::Save(const char* file) {
	m_file.open(file, std::ios_base::out | std::ios_base::binary);

	m_file << "P6\n" << m_w << ' ' << m_h << "\n255\n";

	for (int y = m_h - 1; y >= 0; y--) {
		for (int x = 0; x < m_w; x++) {
			size_t index = GetIndex(x, y);

			for (int i = 0; i < 3; i++) {
				int p = static_cast<int>(std::roundf(m_data[index + i] * 255.f));
				p = p < 0 ? 0 : p;
				p = p > 255 ? 255 : p;

				m_file << (char)p;
			}
		}
	}

#ifdef _DEBUG
	std::cout << "Saved file: " << file << '\n';
#endif // _DEBUG

	m_file.close();
}

PPM::Color PPM::GetColor(const int& x, const int& y) const {
	const size_t index = GetIndex(x, y);
	return { m_data[index + 0], m_data[index + 1], m_data[index + 2] };
}

void PPM::SetPixel(const int& x, const int& y, const PPM::Color& color) {
	size_t index = GetIndex(x, y);

	m_data[index + 0] = color.r;
	m_data[index + 1] = color.g;
	m_data[index + 2] = color.b;
}

size_t PPM::GetIndex(const int& x, const int& y) const {
	int l_y = y % m_h;
	l_y = m_h - l_y - 1;
	return static_cast<size_t>(((x % m_w) + l_y * m_w) * 3);
}

//void PPM::IndexToXY(const size_t& index, int& x, int& y) {
//	int pixelIndex = (int)index / 3;
//	x = pixelIndex % m_w;
//	y = pixelIndex / m_w;
//}