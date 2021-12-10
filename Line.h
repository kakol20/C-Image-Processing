#pragma once

#include "Image.h"

struct Color {
	float r; float g; float b;
};

class Line {
public:
	Line();

	static void Bresenham(Image& image, const Color color, const int x1, const int y1, const int x2, const int y2);
	static void Differential(Image& image, const Color color, const int x1, const int y1, const int x2, const int y2);
	static void Naive(Image& image, const Color color, const int x1, const int y1, const int x2, const int y2);
	static void XiaolinWu(Image& image, const Color color, const int x1, const int y1, const int x2, const int y2);

private:
	static float fpart(float n);
	static float ipart(float n);
	static float rfpart(float x);
	static Color LerpColor(const Color col1, const Color col2, float factor);
	static void Plot(Image& image, const Color color, const float x, const float y, const float factor);


	~Line();
};