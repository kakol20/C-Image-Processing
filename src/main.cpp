#include <iostream>

#include "PPM.h"

int main() {
	std::cout << "Press Enter to exit\n";

	PPM test(256, 256);

	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < 256; y++) {
			test.SetPixel(x, y, static_cast<float>(x) / 255.f, 0.f, 0.f);
		}
	}

	test.Save("x_test.ppm");

	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < 256; y++) {
			test.SetPixel(x, y, 0.f, static_cast<float>(y) / 255.f, 0.f);
		}
	}

	test.Save("y_test.ppm");

	std::cin.get();

	return 0;
}