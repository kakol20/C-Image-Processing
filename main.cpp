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
	//naive.BackgroundColor(255.0f, 255.0f, 255.0f, 255.0f);

	Line::Naive(naive, { 255.0f, 0.0f, 0.0f }, 0, 0, 100, 50);
	Line::Differential(naive, { 0.0f, 255.0f, 0.0f }, 100, 100, -1, 50);

	naive.Write("images/line/comparison.png");

	system("PAUSE");

	return 0;
}