#pragma once

class Color {
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="r">Between 0 &#38; 1</param>
	/// <param name="g">Between 0 &#38; 1</param>
	/// <param name="b">Between 0 &#38; 1</param>
	/// <param name="a">Between 0 &#38; 1</param>
	Color(const float r = 0.f, const float g = 0.f, const float b = 0.f, const float a = 1.f);
	~Color() {};

	// ----- ASSIGNMENT -----

	inline Color& operator=(const Color& other) {
		if (this == &other) return *this;
		m_r = other.m_r;
		m_g = other.m_g;
		m_b = other.m_b;
		m_a = other.m_a;
		return *this;
	}

	inline Color& operator*=(const Color& other) {
		m_r *= other.m_r;
		m_g *= other.m_g;
		m_b *= other.m_b;
		m_a *= other.m_a;
		return *this;
	}
	inline Color& operator/=(const Color& other) {
		m_r /= other.m_r;
		m_g /= other.m_g;
		m_b /= other.m_b;
		m_a /= other.m_a;
		return *this;
	}
	inline Color& operator+=(const Color& other) {
		m_r += other.m_r;
		m_g += other.m_g;
		m_b += other.m_b;
		m_a += other.m_a;
		return *this;
	}
	inline Color& operator-=(const Color& other) {
		m_r -= other.m_r;
		m_g -= other.m_g;
		m_b -= other.m_b;
		m_a -= other.m_a;
		return *this;
	}

	inline Color& operator*=(const float& scalar) {
		m_r *= scalar;
		m_g *= scalar;
		m_b *= scalar;
		m_a *= scalar;
		return *this;
	}
	inline Color& operator/=(const float& scalar) {
		m_r /= scalar;
		m_g /= scalar;
		m_b /= scalar;
		m_a /= scalar;
		return *this;
	}

	// ----- ARITHMETIC -----

	inline Color operator*(const Color& other) const {
		return Color(m_r * other.m_r,
			m_g * other.m_g,
			m_b * other.m_b,
			m_a * other.m_a);
	}
	inline Color operator/(const Color& other) const {
		return Color(m_r / other.m_r,
			m_g / other.m_g,
			m_b / other.m_b,
			m_a / other.m_a);
	}
	inline Color operator+(const Color& other) const {
		return Color(m_r + other.m_r,
			m_g + other.m_g,
			m_b + other.m_b,
			m_a+ other.m_a);
	}
	inline Color operator-(const Color& other) const {
		return Color(m_r - other.m_r,
			m_g - other.m_g,
			m_b - other.m_b,
			m_a - other.m_a);
	}

	inline Color operator*(const float& scalar) const {
		return Color(m_r * scalar,
			m_g * scalar,
			m_b * scalar,
			m_a * scalar);
	}

	inline Color operator/(const float& scalar) const {
		return Color(m_r / scalar,
			m_g / scalar,
			m_b / scalar,
			m_a / scalar);
	}

	// ----- GETTERS & SETTERS -----

	inline void SetRGBA(const float r, const float g, const float b, const float a = 1.f) {
		m_r = r;
		m_g = g;
		m_b = b;
		m_a = a;
	}

	inline void GetRGBA(float& r, float& g, float& b, float& a) const {
		r = m_r;
		g = m_g;
		b = m_b;
		a = m_a;
	}

	inline float GetR() const { return m_r; };
	inline float GetG() const { return m_g; };
	inline float GetB() const { return m_b; };
	inline float GetA() const { return m_a; };

	// ----- OTHER -----

	void Clamp();

private:
	float m_r, m_g, m_b, m_a;

};