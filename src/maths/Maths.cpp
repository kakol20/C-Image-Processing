#include "Maths.h"

float Maths::Cubic(const float& a, const float& b, const float& c, const float& d, const float factor) {
	//return b + 0.5f * factor * (c - a + factor * (2.f * a - 5.f * b + 4.f * c - d + factor * (3.f * (b - c) + d - a)));

	const float factor2 = Maths::LoopPow(factor, 2);
	const float factor3 = factor2 * factor;

	return b + (0.5f * factor * c) - (0.5f * factor * a) + (factor2 * a) -
		(2.5f * b * factor2) + (2.f * factor2 * c) - (0.5f * factor2 * d) +
		(1.5f * b * factor3) - (1.5f * factor3 * c) + (0.5f * factor3 * d) - (0.5f * factor3 * a);
}

float Maths::LoopPow(const float& n, const unsigned int& p) {
	if (p == 0) return 1.f;
	if (p == 1) return n;

	float r = n;
	for (unsigned int i = 0; i < p - 1; i++) {
		r *= n;
	}
	return r;
}

float Maths::Cot(const float& x) {
	return 1.f / std::tanf(x);
}
