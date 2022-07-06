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
#include "Vector3D.h"
#include "LinearFeedbackShift.h"

Vector3D BiLerp(const float x, const float y, Image& image);
void UVSphere(Vector3D unitDir, float& u, float& v);

unsigned int LinearFeedbackShift::Seed = 3808;
bool Image::PrintToConsole = false;

int main(int argc, char** argv) {
	//Image naive(100, 100, 3);
	//naive.BackgroundColor(51.0f, 51.0f, 51.0f, 255.0f);

	/*Line::Naive       (naive, { 255.0f,  51.0f,  51.0f }, 0,  0, 100,  25);
	Line::Differential(naive, { 153.0f, 255.0f,  51.0f }, 0, 25, 100,  50);
	Line::Bresenham   (naive, {  51.0f, 255.0f, 255.0f }, 0, 50, 100,  75);
	Line::XiaolinWu   (naive, { 153.0f,  51.0f, 255.0f }, 0, 75, 100, 100);*/

	//naive.Write("images/line/comparison.png");

	Image bresenham(100, 100, 3);
	Image differential(100, 100, 3);
	Image naive(100, 100, 3);
	Image xiaolinWu(100, 100, 3);

	Line::Bresenham(bresenham, { 255.f, 255.f, 255.f }, 0, 25, 100, 75);
	Line::Differential(differential, { 255.f, 255.f, 255.f }, 0, 25, 100, 75);
	Line::Naive(naive, { 255.f, 255.f, 255.f }, 0, 25, 100, 75);
	Line::XiaolinWu(xiaolinWu, { 255.f, 255.f, 255.f }, 0, 25, 100, 75);

	OrderedDithering(bresenham, DitherFilter::FULLCOLOR, Threshold::ORDERED_8, 255);
	OrderedDithering(differential, DitherFilter::FULLCOLOR, Threshold::ORDERED_8, 255);
	OrderedDithering(naive, DitherFilter::FULLCOLOR, Threshold::ORDERED_8, 255);
	OrderedDithering(xiaolinWu, DitherFilter::FULLCOLOR, Threshold::ORDERED_8, 255);

	bresenham.Write("images/line/bresenham.png");
	differential.Write("images/line/differential.png");
	naive.Write("images/line/naive.png");
	xiaolinWu.Write("images/line/xiaolinWu.png");

	//system("PAUSE");

	return 0;
}

Vector3D BiLerp(const float x, const float y, Image& image) {
	int index = 0;

	index = image.GetIndex((int)floorf(x), (int)floorf(y));
	Vector3D Q11(image.GetDataF(index + 0) / 255.0f, image.GetDataF(index + 1) / 255.0f, image.GetDataF(index + 2) / 255.0f);

	index = image.GetIndex((int)floorf(x), (int)ceilf(y));
	Vector3D Q12(image.GetDataF(index + 0) / 255.0f, image.GetDataF(index + 1) / 255.0f, image.GetDataF(index + 2) / 255.0f);

	index = image.GetIndex((int)ceil(x), (int)floorf(y));
	Vector3D Q21(image.GetDataF(index + 0) / 255.0f, image.GetDataF(index + 1) / 255.0f, image.GetDataF(index + 2) / 255.0f);

	index = image.GetIndex((int)ceilf(x), (int)ceilf(y));
	Vector3D Q22(image.GetDataF(index + 0) / 255.0f, image.GetDataF(index + 1) / 255.0f, image.GetDataF(index + 2) / 255.0f);

	Vector3D R1 = Vector3D::Lerp(Q11, Q21, x - floorf(x));
	Vector3D R2 = Vector3D::Lerp(Q12, Q22, x - floorf(x));

	Vector3D p = Vector3D::Lerp(R1, R2, y - floorf(y));
	return p;
}

void UVSphere(Vector3D unitDir, float& u, float& v) {
	u = 0.5f + (atan2f(unitDir.GetX(), unitDir.GetZ()) / (2.0f * 3.14159265f));
	v = 0.5f - (asinf(unitDir.GetY()) / 3.14159265f);
}
