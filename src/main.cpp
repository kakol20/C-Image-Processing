#include <iostream>

#include "image/Color.h"
#include "image/Image.h"

int main() {
	std::cout << "Hello World!\n";

	int x = 8;
	int modX = ((x % 3) + 3) % 3;

	std::cout << modX << '\n';

	Image img(100, 100, 4);
	Image copyTest = img;

	std::cin.get();
	return 0;
}