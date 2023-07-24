#include <algorithm>

#include "Color.h"

Color::Color(const float r, const float g, const float b, const float a) {
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
}

Color::Color(const Color& other) {
	m_r = other.m_r;
	m_g = other.m_g;
	m_b = other.m_b;
	m_a = other.m_a;
}

void Color::Clamp() {
	m_r = std::clamp(m_r, 0.f, 1.f);
	m_g = std::clamp(m_g, 0.f, 1.f);
	m_b = std::clamp(m_b, 0.f, 1.f);
	m_a = std::clamp(m_a, 0.f, 1.f);
}
