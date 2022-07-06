#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <utility>

#include "Line.h"

Line::Line() {
}

/// <summary>
/// Implementation without the use of floats
/// </summary>
/// <param name="image"></param>
/// <param name="color"></param>
/// <param name="x1"></param>
/// <param name="y1"></param>
/// <param name="x2"></param>
/// <param name="y2"></param>
void Line::Bresenham(Image& image, const Color color, const int x1, const int y1, const int x2, const int y2) {
	int l_x1 = x1;
	int l_y1 = y1;

	int l_x2 = x2;
	int l_y2 = y2;

	int dx = abs(l_x2 - l_x1);
	int sx = l_x1 < l_x2 ? 1 : -1;

	int dy = -abs(l_y2 - l_y1);
	int sy = l_y1 < l_y2 ? 1 : -1;

	int err = dx + dy;

	while (true) {
		int index = image.GetIndex(l_x1, l_y1);

		if (image.GetChannels() >= 3) {
			image.SetData(index + 0, color.r);
			image.SetData(index + 1, color.g);
			image.SetData(index + 2, color.b);

			if (image.GetChannels() == 4) {
				image.SetData(index + 3, (uint8_t)255);
			}
		}
		else {
			image.SetData(index, color.r);
		}

		if (l_x1 == l_x2 && l_y1 == l_y2) break;

		int e2 = 2 * err;

		if (e2 >= dy) {
			err += dy;
			l_x1 += sx;
		}

		if (e2 <= dx) {
			err += dx;
			l_y1 += sy;
		}
	}
}

/// <summary>
/// Modified version of Naive algorithm
/// </summary>
/// <param name="image"></param>
/// <param name="color"></param>
/// <param name="x1"></param>
/// <param name="y1"></param>
/// <param name="x2"></param>
/// <param name="y2"></param>
void Line::Differential(Image& image, const Color color, const int x1, const int y1, const int x2, const int y2) {
	float dx = (float)(x2 - x1);
	float dy = (float)(y2 - y1);
	float step = 0;

	if (abs(dx) >= abs(dy)) {
		step = abs(dx);
	}
	else {
		step = abs(dy);
	}

	dx = dx / step;
	dy = dy / step;

	float x = (float)x1;
	float y = (float)y1;

	int i = 1;

	while (i <= step) {
		int index = image.GetIndex((int)x, (int)y);

		if (image.GetChannels() >= 3) {
			image.SetData(index + 0, color.r);
			image.SetData(index + 1, color.g);
			image.SetData(index + 2, color.b);

			if (image.GetChannels() == 4) {
				image.SetData(index + 3, (uint8_t)255);
			}
		}
		else {
			image.SetData(index, color.r);
		}

		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
}

/// <summary>
/// Basic implementation
/// </summary>
/// <param name="image"></param>
/// <param name="color"></param>
/// <param name="x1"></param>
/// <param name="y1"></param>
/// <param name="x2"></param>
/// <param name="y2"></param>
void Line::Naive(Image& image, const Color color, const int x1, const int y1, const int x2, const int y2) {
	int dX = x2 - x1;
	int dY = y2 - y1;

	for (int x = x1; x < x2; x++) {
		int y = y1 + dY * (x - x1) / dX;

		int index = image.GetIndex(x, y);

		if (image.GetChannels() >= 3) {
			image.SetData(index + 0, color.r);
			image.SetData(index + 1, color.g);
			image.SetData(index + 2, color.b);

			if (image.GetChannels() == 4) {
				image.SetData(index + 3, (uint8_t)255);
			}
		}
		else {
			image.SetData(index, color.r);
		}
	}
}

/// <summary>
/// Anti-aliased algorithm
/// </summary>
/// <param name="image"></param>
/// <param name="color"></param>
/// <param name="x1"></param>
/// <param name="y1"></param>
/// <param name="x2"></param>
/// <param name="y2"></param>
void Line::XiaolinWu(Image& image, const Color color, const int x1, const int y1, const int x2, const int y2) {
	// https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm

	bool steep = abs(y2 - y1) > abs(x2 - x1);

	float l_x0 = (float)x1, l_y0 = (float)y1;
	float l_x1 = (float)x2, l_y1 = (float)y2;

	if (steep) {
		std::swap(l_x0, l_y0);
		std::swap(l_x1, l_y1);
	}
	if (l_x0 > l_x1) {
		std::swap(l_x0, l_x1);
		std::swap(l_y0, l_y1);
	}

	float dx = l_x1 - l_x0;
	float dy = l_y1 - l_y0;
	float gradient = dx == 0 ? 1.0f : dy / dx;

	// first endpoint
	float xend = roundf(l_x0);
	float yend = l_y0 + gradient * (xend - l_x0);
	float xgap = rfpart(l_x0 + 0.5f);

	float xpxl1 = xend; // this will be used in the main loop
	float ypxl1 = ipart(yend);

	if (steep) {
		Plot(image, color, ypxl1, xpxl1, rfpart(yend) * xgap);
		Plot(image, color, ypxl1 + 1, xpxl1, fpart(yend) * xgap);
	}
	else {
		Plot(image, color, xpxl1, ypxl1, rfpart(yend) * xgap);
		Plot(image, color, xpxl1, ypxl1 + 1, fpart(yend) * xgap);
	}
	float intery = yend + gradient; // first y-intersection for the main loop

	// second endpoint
	xend = roundf(l_x1);
	yend = l_y1 + gradient * (xend - l_x1);
	xgap = fpart(l_x1 + 0.5f);
	
	float xpxl2 = xend; // this will be used in the main loop
	float ypxl2 = ipart(yend);

	if (steep) {
		Plot(image, color, ypxl2, xpxl2, rfpart(yend) * xgap);
		Plot(image, color, ypxl2 + 1, xpxl2, fpart(yend) * xgap);
	}
	else {
		Plot(image, color, xpxl2, ypxl2, rfpart(yend) * xgap);
		Plot(image, color, xpxl2, ypxl2 + 1, fpart(yend) * xgap);
	}

	// main loop
	if (steep) {
		for (float x = xpxl1 + 1; x < xpxl2; x++) {
			Plot(image, color, ipart(intery), x, rfpart(intery));
			Plot(image, color, ipart(intery) + 1, x, fpart(intery));

			intery = intery + gradient;
		}
	}
	else {
		for (float x = xpxl1 + 1; x < xpxl2; x++) {
			Plot(image, color, x, ipart(intery), rfpart(intery));
			Plot(image, color, x, ipart(intery) + 1, fpart(intery));

			intery = intery + gradient;
		}
	}
}

float Line::fpart(float n) {
	return n - floorf(n);
}

float Line::ipart(float n) {
	return floorf(n);
}

float Line::rfpart(float x) {
	return 1 - Line::fpart(x);
}

Color Line::LerpColor(const Color col1, const Color col2, float factor) {
	float r = std::lerp(col1.r, col2.r, factor);
	float g = std::lerp(col1.g, col2.g, factor);
	float b = std::lerp(col1.b, col2.b, factor);
	return {r, g, b};
}

void Line::Plot(Image& image, const Color color, const float x, const float y, const float factor) {
	int index = image.GetIndex((int)x, (int)y);

	if (image.GetChannels() >= 3) {
		Color bgCol = { image.GetDataF(index + 0), image.GetDataF(index + 1), image.GetDataF(index + 2) };
		Color newCol = Line::LerpColor(bgCol, color, factor);

		image.SetData(index + 0, newCol.r);
		image.SetData(index + 1, newCol.g);
		image.SetData(index + 2, newCol.b);

		if (image.GetChannels() == 4) {
			image.SetData(index + 3, std::lerp(image.GetDataF(index + 3), 255.0f, factor));
		}
	}
	else {
		image.SetData(index, std::lerp(image.GetDataF(index), color.r, factor));
	}
}

Line::~Line() {
}
