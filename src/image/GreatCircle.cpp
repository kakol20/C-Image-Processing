#include <cmath>

#include "GreatCircle.h"

void GreatCircle::DrawCurve(PPM& image, const PPM::Color& color, const Vector2& start, const Vector2& end, const unsigned int& segments) {
	//Vector2 lambda = Maths::
}

Vector2 GreatCircle::ToEquirectangular(const Vector2& v) {
	float x = v.GetX() * Maths::THETA;
	float y = (2.f * std::atanf(std::exp2f(v.GetY() * Maths::THETA))) - (Maths::PI / 2.f);
	return Vector2(x, y);
}

Vector2 GreatCircle::ToMercator(const Vector2& v) {
	float x = v.GetX() / Maths::THETA;
	float y = (1.f / Maths::THETA) * std::log10f(
		std::tanf(
			(v.GetY() / 2.f) + (Maths::PI / 4.f)
		)
	);
	return Vector2(x, y);
}
