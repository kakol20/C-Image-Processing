#include <iostream>
#include <vector>
#include <algorithm>

#include "image/GreatCircle.h"
#include "image/Line.h"
#include "image/PPM.h"
#include "maths/Vector2.h"

Vector2 Vector2::Zero(0.f, 0.f);

int main() {
	//std::cout << "Press Enter to exit\n";

	// ----- TEST X & Y AXIS -----

	PPM test(256, 256);
	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < 256; y++) {
			test.SetPixel(x, y, { static_cast<float>(x) / 255.f, 0.f, 0.f });
		}
	}
	test.Write("x_test.ppm");
	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < 256; y++) {
			test.SetPixel(x, y, { 0.f, static_cast<float>(y) / 255.f, 0.f });
		}
	}
	test.Write("y_test.ppm");

	// ----- TEST LINE DRAWING -----

	PPM lineTest(256, 256);
	Line::DrawLine(lineTest, { 1.f, 1.f, 1.f }, 85, 85, 185, 171);
	lineTest.Write("line_test.ppm");

	// ----- TEST CUBIC INTERPOLATION -----

	PPM cubicTest(256, 256);
	const float mX = 256.f / 12;
	const float mY = 256.f / 7;
	std::vector<Vector2> points = { Vector2(1.f, 1.f),
		Vector2(2.f, 3.f),
		Vector2(5.f, 5.f),
		Vector2(6.f, 4.f),
		Vector2(8.f, 6.f),
		Vector2(9.f, 3.f),
		Vector2(11.f, 3.f)
	};

	for (auto it = points.begin(); it != points.end(); it++) {
		Vector2& i = (*it);
		i.SetX(i.GetX() * mX);
		i.SetY(i.GetY() * mY);
	}

	const int segments = 10;

	for (size_t i = 0; i < points.size() - 1; i++) {
		Vector2 a = points[static_cast<size_t>(std::clamp((int)i - 1, 0, (int)points.size() - 1))];
		Vector2 b = points[i];
		Vector2 c = points[i + 1];
		Vector2 d = points[std::clamp(i + 2, (size_t)0, points.size() - 1)];

		std::vector<Vector2> points;
		points.reserve((size_t)segments + 1);

		for (int s = 0; s <= segments; s++) {
			float factor1 = (float)s / (float)segments;

			points.push_back(Vector2::CubicLerp(a, b, c, d, factor1));
		}

		Line::DrawLine(cubicTest, { 1.f, 1.f, 1.f }, points);
	}

	for (auto it = points.begin(); it != points.end(); it++) {
		Vector2& p = (*it);

		int x = static_cast<int>(std::floorf(p.GetX()));
		int y = static_cast<int>(std::floorf(p.GetY()));

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				cubicTest.SetPixel(x + i, y + j, { 1.f, 0.f, 0.f });
			}
		}
	}

	cubicTest.Write("cubic_test.ppm");

	// ----- TEST GREAT CIRCLE CURVE -----

	PPM greatCircle(1080, 1080);

	Vector2 start(-43.1729f, -22.9068f);
	Vector2 end(120.9842f, 14.5995f);

	start += Vector2(180.f, 180.f);
	end += Vector2(180.f, 180.f);
	start /= Vector2(360.f, 360.f);
	end /= Vector2(360.f, 360.f);
	start *= Vector2(1080.f, 1080.f);
	end *= Vector2(1080.f, 1080.f);

	GreatCircle::DrawCurve(greatCircle, { 1.f, 1.f, 1.f }, start, end, 10);

	greatCircle.Write("greatCircle_test.ppm");

	// ----- READING PPM FILE -----

	PPM map(1, 1);
	map.Read("map.ppm");

	GreatCircle::DrawCurve(map, { 1.f, 1.f, 1.f }, start, end, 10);
	map.Write("readAndWrite_test.ppm");


#ifdef _DEBUG
	std::cout << "Press enter to exit\n";
	std::cin.get();
#endif // _DEBUG


	return 0;
}