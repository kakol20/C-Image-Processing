#include "Line.h"

/// <summary>
/// Xiaolin Wu anti-aliased algorithm
/// </summary>
/// <param name="image"></param>
/// <param name="color"></param>
/// <param name="x1"></param>
/// <param name="y1"></param>
/// <param name="x2"></param>
/// <param name="y2"></param>
void Line::DrawLine(PPM& image, const PPM::Color& color, const int& x1, const int& y1, const int& x2, const int& y2) {
	// https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
	DrawLine(image, color, (float)x1, (float)y1, (float)x2, (float)y2);
}

void Line::DrawLine(PPM& image, const PPM::Color& color, const float& x1, const float& y1, const float& x2, const float& y2) {
	bool steep = std::abs(y2 - y1) > std::abs(x2 - x1);

	float l_x0 = x1, l_y0 = y1;
	float l_x1 = x2, l_y1 = y2;

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
	float gradient = dx == 0.f ? 1.0f : dy / dx;

	// first endpoint
	float xend = roundf(l_x0);
	float yend = l_y0 + gradient * (xend - l_x0);
	float xgap = rfpart(l_x0 + 0.5f);

	float xpxl1 = xend; // this will be used in the main loop
	float ypxl1 = ipart(yend);

	if (steep) {
		Plot(image, color, ypxl1, xpxl1, rfpart(yend) * xgap);
		Plot(image, color, ypxl1 + 1, xpxl1, fpart(yend) * xgap);
	} else {
		Plot(image, color, xpxl1, ypxl1, rfpart(yend) * xgap);
		Plot(image, color, xpxl1, ypxl1 + 1, fpart(yend) * xgap);
	}
	float intery = yend + gradient; // first y-intersection for the main loop

	// second endpoint
	xend = std::roundf(l_x1);
	yend = l_y1 + gradient * (xend - l_x1);
	xgap = fpart(l_x1 + 0.5f);

	float xpxl2 = xend; // this will be used in the main loop
	float ypxl2 = ipart(yend);

	if (steep) {
		Plot(image, color, ypxl2, xpxl2, rfpart(yend) * xgap);
		Plot(image, color, ypxl2 + 1, xpxl2, fpart(yend) * xgap);
	} else {
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
	} else {
		for (float x = xpxl1 + 1; x < xpxl2; x++) {
			Plot(image, color, x, ipart(intery), rfpart(intery));
			Plot(image, color, x, ipart(intery) + 1, fpart(intery));

			intery = intery + gradient;
		}
	}
}

void Line::DrawLine(PPM& image, const PPM::Color& color, const Vector2& v1, const Vector2& v2) {
	DrawLine(image, color, v1.GetX(), v1.GetY(), v2.GetX(), v2.GetY());
}

void Line::DrawLine(PPM& image, const PPM::Color& color, const std::vector<Vector2>& points, const bool& loop) {
	size_t limit = points.size();
	limit = loop ? limit : limit - 1;

	for (size_t i = 0; i < limit; i++) {
		const Vector2& start = points[i];
		const Vector2& end = points[(i + 1) % points.size()];

		Line::DrawLine(image, color, start, end);
	}
}

PPM::Color Line::LerpColor(const PPM::Color& c1, const PPM::Color& c2, const float& factor) {
	return { std::lerp(c1.r, c2.r, factor),
		std::lerp(c1.g, c2.g, factor),
		std::lerp(c1.b, c2.b, factor)
	};
}

void Line::Plot(PPM& image, const PPM::Color& color, const float& x, const float& y, const float& factor) {
	PPM::Color bgCol = image.GetColor(static_cast<int>(std::roundf(x)), static_cast<int>(std::roundf(y)));
	PPM::Color newCol = LerpColor(bgCol, color, factor);

	image.SetPixel(static_cast<int>(std::roundf(x)), static_cast<int>(std::roundf(y)), newCol);
}

float Line::fpart(float n) {
	return n - std::floorf(n);
}

float Line::ipart(float n) {
	return std::floorf(n);
}

float Line::rfpart(float x) {
	return 1.f - Line::fpart(x);
}