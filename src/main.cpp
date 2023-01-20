#include <iostream>

#include "image/PPM.h"
#include "image/Line.h"

int main() {
	std::cout << "Press Enter to exit\n";

	PPM test(256, 256);

	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < 256; y++) {
			test.SetPixel(x, y, { static_cast<float>(x) / 255.f, 0.f, 0.f });
		}
	}

	test.Save("x_test.ppm");

	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < 256; y++) {
			test.SetPixel(x, y, { 0.f, static_cast<float>(y) / 255.f, 0.f });
		}
	}

	test.Save("y_test.ppm");

	PPM lineTest(256, 256);

	Line::DrawLine(lineTest, { 1.f, 1.f, 1.f }, 85, 85, 185, 171);

	lineTest.Save("line_test.ppm");

	std::cin.get();

	return 0;
}