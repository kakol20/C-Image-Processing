#include <iostream>
#include <stdio.h>
#include <charconv>
#include <sstream>
#include <vector>
#include <set>

#include "Image.h"
#include "Filters.h"
#include "String.h"
#include "Functions.h"
#include "Line.h"

int main(int argc, char** argv) {
	Image naive(100, 100, 3);
	//naive.BackgroundColor(51.0f, 51.0f, 51.0f, 255.0f);

	Line::Naive       (naive, { 255.0f,  51.0f,  51.0f }, 0,  0, 100,  25);
	Line::Differential(naive, { 153.0f, 255.0f,  51.0f }, 0, 25, 100,  50);
	Line::Bresenham   (naive, {  51.0f, 255.0f, 255.0f }, 0, 50, 100,  75);
	Line::XiaolinWu   (naive, { 153.0f,  51.0f, 255.0f }, 0, 75, 100, 100);

	OrderedDithering(naive, DitherFilter::FULLCOLOR, Threshold::ORDERED_8, 255);

	naive.Write("images/line/comparison.png");

	//system("PAUSE");

	return 0;
}