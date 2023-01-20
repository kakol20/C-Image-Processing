#pragma once

#include "Maths.h"

class Vector2 {
public:
	Vector2(const float& x = 0.f, const float& y = 0.f);
	Vector2(const int& x, const int& y);
	~Vector2() {};

	float GetX() const { return m_x; };
	float GetY() const { return m_y; };

	// ----- ASSIGNMENT OPERATORS -----

	Vector2& operator=(const Vector2& other);

	// ----- OTHER -----

	static Vector2 CubicLerp(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, const float& factor);

private:
	float m_x;
	float m_y;
};