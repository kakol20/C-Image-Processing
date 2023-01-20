#include "Vector2.h"

Vector2::Vector2(const float& x, const float& y) {
	m_x = x;
	m_y = y;
}

Vector2::Vector2(const int& x, const int& y) {
	m_x = static_cast<float>(x);
	m_y = static_cast<float>(y);
}

Vector2& Vector2::operator=(const Vector2& other) {
	if (this == &other) return *this;

	m_x = other.m_x;
	m_y = other.m_y;
	return *this;
}

Vector2 Vector2::CubicLerp(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, const float& factor) {
	return Vector2(Maths::Cubic(a.m_x, b.m_x, c.m_x, d.m_x, factor),
		Maths::Cubic(a.m_y, b.m_y, c.m_y, d.m_y, factor)
	);
}
