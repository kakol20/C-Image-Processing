#pragma once

#include <fstream>
#include <vector>

class PPM {
public:
	PPM(const int& w = 1, const int& h = 1);
	~PPM() {};

	void Save(const char* file);

	void SetPixel(const int& x, const int& y, const float& r, const float& g, const float& b);

private:
	int m_w;
	int m_h;

	std::vector<float> m_data;

	std::fstream m_file;
};