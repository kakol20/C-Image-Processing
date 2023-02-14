#pragma once

#include <vector>

#include "PPM.h"
#include "../maths/Vector2.h"

class Line {
public:
	Line() {};
	~Line() {};
	
	static void DrawLine(PPM& image, const PPM::Color& color, const int& x1, const int& y1, const int& x2, const int& y2);
	static void DrawLine(PPM& image, const PPM::Color& color, const float& x1, const float& y1, const float& x2, const float& y2);
	static void DrawLine(PPM& image, const PPM::Color& color, const Vector2& v1, const Vector2& v2);
	static void DrawLine(PPM& image, const PPM::Color& color, const std::vector<Vector2>& points, const bool& loop = false);

private:
	static PPM::Color LerpColor(const PPM::Color& c1, const PPM::Color& c2, const float& factor);
	static void Plot(PPM& image, const PPM::Color& color, const float& x, const float& y, const float& factor);

	static float fpart(float n);
	static float ipart(float n);
	static float rfpart(float x);
};