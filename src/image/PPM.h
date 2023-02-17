#pragma once

#include <fstream>
#include <vector>

class PPM {
public:
	struct Color {
		float r, g, b;
	};

	PPM(const int& w = 1, const int& h = 1);
	~PPM() {};

	void Read(const char* file);
	void Write(const char* file);

	PPM::Color GetColor(const int& x, const int& y) const;

	void SetPixel(const int& x, const int& y, const PPM::Color& color);

	inline int GetHeight() const { return m_h; };
	inline int GetWidth() const { return m_w; };

private:
	int m_w;
	int m_h;

	std::vector<float> m_data;

	std::fstream m_file;

	size_t GetIndex(const int& x, const int& y) const;

	//void IndexToXY(const size_t& index, int& x, int& y);
};