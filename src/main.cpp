#include <iostream>
#include <cmath>

#include "image/Color.h"
#include "image/Image.h"

int main() {
	// ----- THE FOLLOWING CODE IS FOR TESTING PURPOSES -----

	std::cout << "Hello World!\n";

	int x = -8;
	int modX = ((x % 3) + 3) % 3;

	std::cout << modX << '\n';

	Image img(1024, 1024, 1);

	float halfW = (float)img.GetWidth() / 2.f;
	float R = 5.;
	float halfWR = std::powf(halfW, R);
	float A = (float)img.GetWidth() / (float)img.GetHeight();
	float yOffset = ((float)img.GetHeight() * A) / 2.f;

	Color trueColor(1, 1, 1, 1);
	Color falseColor(0, 0, 0, 1);

	float sampleDimensions = 8.f;
	sampleDimensions = 1.f / sampleDimensions;

	for (int x = 0; x < img.GetWidth(); x++) {
		float x_norm = (float)(x) / (float)img.GetWidth();
		for (int y = 0; y < img.GetHeight(); y++) {
			Color totalColor(0, 0, 0, 0);
			int count = 0;
			for (float x_sample = (float)x; x_sample <= (float)(x + 1); x_sample += sampleDimensions) {
				float x_normS = x_sample / (float)img.GetWidth();
				float x_check = std::powf(std::abs(x_sample - halfW), R);

				for (float y_sample = (float)y; y_sample <= (float)(y + 1); y_sample += sampleDimensions) {
					float y_norm = y_sample / (float)img.GetHeight();
					float y_check = std::powf(std::abs(A * y_sample - yOffset), R);

					bool check = x_check + y_check <= halfWR;

					totalColor += check ? trueColor : falseColor;
					count++;
				}
			}

			totalColor /= (float)count;

			float y_norm = (float)(y) / (float)img.GetHeight();

			img.SetPixel(totalColor, x_norm, y_norm);
		}
	}

	img.Write("images/superCircle.png");

	std::cin.get();
	return 0;
}