#include <iostream>

#include "image/Color.h"
#include "image/Image.h"

int main() {
	// ----- THE FOLLOWING CODE IS FOR TESTING PURPOSES -----

	std::cout << "Hello World!\n";

	int x = -8;
	int modX = ((x % 3) + 3) % 3;

	std::cout << modX << '\n';

	Image img(100, 100, 4);
	Image copyTest = img;

	Image gradient(255, 255, 3);
	for (unsigned int y = 0; y < 255; y++) {
		float l_y = (float)y / 255;
		for (unsigned int x = 0; x < 255; x++) {
			float l_x = (float)x / 255.f;

			gradient.SetPixel(Color(l_x, l_y, 0.f), l_x, l_y);
		}
	}
	gradient.Write("images/gradient.png");

	std::cin.get();
	return 0;
}