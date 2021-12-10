#include <stdlib.h>

#include "Line.h"

Line::Line() {
}

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

void Line::Naive(Image& image, const Color color, const int x1, const int y1, const int x2, const int y2) {
	int dX = x2 - x1;
	int dY = y2 - y1;

	for (unsigned int x = x1; x < x2; x++) {
		unsigned int y = y1 + dY * (x - x1) / dX;

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

Line::~Line() {
}
