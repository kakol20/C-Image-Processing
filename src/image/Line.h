#pragma once

#include "PPM.h"

class Line {
public:
	Line() {};
	~Line() {};
	
	static void DrawLine(PPM& image, const PPM::Color& color, const int& x1, const int& y1, const int& x2, const int& y2);

private:
	static PPM::Color LerpColor(const PPM::Color& c1, const PPM::Color& c2, const float& factor);
	static void Plot(PPM& image, const PPM::Color& color, const float& x, const float& y, const float& factor);

	static float fpart(float n);
	static float ipart(float n);
	static float rfpart(float x);
};