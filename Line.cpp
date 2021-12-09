#include <stdlib.h>

#include "Line.h"

Line::Line() {
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
