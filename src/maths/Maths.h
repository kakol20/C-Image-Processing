#pragma once

#include <algorithm>
#include <cmath>

namespace Maths {
	float Cubic(const float& a, const float& b, const float& c, const float& d, const float factor);

	float LoopPow(const float& n, const unsigned int& p);

	const float PI = 3.14159265f;
	const float THETA = Maths::PI * 2.f;

	float Cot(const float& x);
}