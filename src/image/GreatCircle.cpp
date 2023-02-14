#include <cmath>
#include <vector>

#include "Line.h"

#include "GreatCircle.h"

void GreatCircle::DrawCurve(PPM& image, const PPM::Color& color, const Vector2& start, const Vector2& end, const unsigned int& segments) {
	// normalize pixel coordinates to mercator coordinates (-0.5 to 0.5)

	const Vector2 pixelMax((float)image.GetWidth(), (float)image.GetHeight());
	const Vector2 mercatorMin(-0.5f, -0.5f);
	const Vector2 mercatorMax(0.5f, 0.5f);

	const Vector2 start_n = Vector2::Map(start, Vector2::Zero, pixelMax, mercatorMin, mercatorMax);
	const Vector2 end_n   = Vector2::Map(end,	Vector2::Zero, pixelMax, mercatorMin, mercatorMax);

	const Vector2 start_e = GreatCircle::ToEquirectangular(start_n);
	const Vector2 end_e = GreatCircle::ToEquirectangular(end_n);

	// Calculate
	std::vector<Vector2> points;
	points.reserve((size_t)(segments + 1));

	const float alpha = GreatCircle::Alpha(start_e, end_e);
	const float step = alpha / (float)segments;

	for (float t = 0.f; t < alpha; t += step) {
		points.push_back(GreatCircle::Point(alpha, t, start_e, end_e, pixelMax));
	}
	points.push_back(GreatCircle::Point(alpha, alpha, start_e, end_e, pixelMax));

	Line::DrawLine(image, color, points);
}

Vector2 GreatCircle::ToEquirectangular(const Vector2& v) {
	float x = v.GetX() * Maths::THETA;
	float y = (2.f * std::atanf(std::exp2f(v.GetY() * Maths::THETA))) - (Maths::PI / 2.f);
	return Vector2(x, y);
}

Vector2 GreatCircle::ToMercator(const Vector2& v) {
	float x = v.GetX() / Maths::THETA;
	float y = (1.f / Maths::THETA) * std::logf(
		std::tanf(
			(v.GetY() / 2.f) + (Maths::PI / 4.f)
		)
	);
	return Vector2(x, y);
}

float GreatCircle::Alpha(const Vector2& start, const Vector2& end) {
	return std::acosf(
		(std::cosf(start.GetY()) * std::cosf(end.GetY()) * std::cosf(end.GetX() - start.GetX())) +
		(std::sinf(start.GetY()) * std::sinf(end.GetY()))
	);
}

float GreatCircle::K(const float& alpha, const float& t) {
	return 1.f / (
		(std::sinf(alpha) * Maths::Cot(t)) - std::cosf(alpha) + 1.f
	);
}

float GreatCircle::X(const float& k, const Vector2& start, const Vector2& end) {
	return ((1.f - k) * std::cosf(start.GetY()) * std::cosf(start.GetX())) +
		(k * std::cosf(end.GetY()) * std::cosf(end.GetX()));
}

float GreatCircle::Y(const float& k, const Vector2& start, const Vector2& end) {
	return ((1.f - k) * std::cosf(start.GetY()) * std::sinf(start.GetX())) +
		(k * std::cosf(end.GetY()) * std::sinf(end.GetX()));
}

float GreatCircle::Z(const float& k, const Vector2& start, const Vector2& end) {
	return ((1.f - k) * std::sinf(start.GetY())) + 
		(k * std::sinf(end.GetY()));
}

Vector2 GreatCircle::Point(const float alpha, const float& t, const Vector2& start, const Vector2& end, const Vector2& pixelMax) {
	const Vector2 mercatorMin(-0.5f, -0.5f);
	const Vector2 mercatorMax(0.5f, 0.5f);

	float k = GreatCircle::K(alpha, t);
	float X = GreatCircle::X(k, start, end);
	float Y = GreatCircle::Y(k, start, end);
	float Z = GreatCircle::Z(k, start, end);

	float lambda = std::atan2f(Y, X);
	float phi = std::atanf(
		Z / std::sqrtf((X * X) + (Y * Y))
	);

	Vector2 point(lambda, phi);
	point = GreatCircle::ToMercator(point);
	point = Vector2::Map(point, mercatorMin, mercatorMax, Vector2::Zero, pixelMax);

	return point;
}