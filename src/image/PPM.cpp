#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <sstream>

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

void PPM::Read(const char* file) {
	m_file.open(file, std::ios_base::in | std::ios_base::binary);

	// ----- READ HEADER IN ASCII -----
	char header[256];

	if (m_file.is_open()) {
		// Read format
		m_file.read(header, 2);
		header[2] = '\0';

		if (header[0] == 'P' && header[1] == '6') {
#ifdef _DEBUG
			std::cout << "PPM image format detected\n";
#endif // _DEBUG
		} else {
#ifdef _DEBUG
			std::cout << "Error: Not a PPM image\n";
#endif // _DEBUG

			return;
		}

		// Read the image size
		int width, height;
		m_file >> width >> height;
		int max;
		m_file >> max;
		m_file.get();

		m_w = width;
		m_h = height;

		// Calculate the size of the image data
		int num_pixels = width * height;
		int data_size = num_pixels * 3;

		// Read the image data
		std::vector<unsigned char> data(data_size);
		m_file.read(reinterpret_cast<char*>(data.data()), data_size);

		// Copy to member data
		m_data.clear();
		m_data.reserve((size_t)data_size);
		for (auto it = data.begin(); it != data.end(); it++) {
			unsigned char& col = (*it);
			unsigned int uint_col = (unsigned int)col;
			float f_col = (float)uint_col;
			f_col /= 255.f;

			m_data.push_back(f_col);
		}

		// Correct channels

		/*for (size_t i = 0; i < m_data.size(); i += 3) {
			float r = m_data[i + 0];
			float g = m_data[i + 1];
			float b = m_data[i + 2];

			m_data[i + 0] = r;
			m_data[i + 1] = g;
			m_data[i + 2] = b;
		}*/
	} else {
#ifdef _DEBUG
		std::cout << "Error: Could not open file\n";
#endif // _DEBUG
	}

	m_file.close();
}

void PPM::Write(const char* file) {
	m_file.open(file, std::ios_base::out | std::ios_base::binary);

	// ----- SAVE HEADER AS ASCII -----
	std::stringstream ss;
	ss << "P6\n" << m_w << ' ' << m_h << "\n255\n";
	m_file.write(ss.str().c_str(), ss.str().length());

	// ----- SAVE DATA -----
	for (int y = m_h - 1; y >= 0; y--) {
		for (int x = 0; x < m_w; x++) {
			size_t index = GetIndex(x, y);

			for (int i = 0; i < 3; i++) {
				int p = static_cast<int>(std::roundf(m_data[index + i] * 255.f));
				p = p < 0 ? 0 : p;
				p = p > 255 ? 255 : p;

				unsigned char char_p = (unsigned char)p;
				m_file.write((char*)&char_p, sizeof(unsigned char));

				//m_file << (char)p;
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