#pragma once

#include "Maths.h"

class Vector2 {
public:
	Vector2(const float& x = 0.f, const float& y = 0.f);
	Vector2(const int& x, const int& y);
	~Vector2() {};

	float GetX() const { return m_x; };
	float GetY() const { return m_y; };

	void SetX(const float& x) { m_x = x; };
	void SetY(const float& y) { m_y = y; };

	// ----- ASSIGNMENT OPERATORS -----

	Vector2& operator=(const Vector2& other);

	Vector2& operator*=(const Vector2& other);
	Vector2& operator/=(const Vector2& other);
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);

	// ----- ARITHMETIC OPERATORS -----

	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const Vector2& other) const;
	Vector2 operator/(const Vector2& other) const;
	Vector2 operator+(const Vector2& other) const;

	// ----- OTHER -----

	static Vector2 CubicLerp(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, const float& factor);
	static Vector2 Lerp(const Vector2& min, const Vector2& max, const float& factor);
	static Vector2 Lerp(const Vector2& min, const Vector2& max, const Vector2& factor);
	static Vector2 Map(const Vector2& v, const Vector2& fromMin, const Vector2& fromMax, const Vector2& toMin, const Vector2& toMax);

private:
	float m_x;
	float m_y;
};