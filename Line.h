#pragma once

#include "Image.h"

struct Color {
	float r; float g; float b;
};

class Line {
public:
	Line();

	static void Differential(Image& image, const Color color, const int x1, const int y1, const int x2, const int y2);
	static void Naive(Image& image, const Color color, const int x1, const int y1, const int x2, const int y2);

	~Line();
};