#include <iostream>
#include "image/Color.h"

int main() {
	std::cout << "Hello World!\n";

	Color red = Color(255.f / 255.f, 49.f / 255.f, 49.f / 255.f, 1.f);
	Color blue = Color(0.f, 150.f / 255.f, 255.f / 255.f, 165 / 255.f);
	Color mul = red * blue;
	Color add = red + blue;
	add.Clamp();

	std::cin.get();
	return 0;
}