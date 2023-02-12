#pragma once

#include "../maths/Vector2.h"
#include "Line.h"
#include "PPM.h"

class GreatCircle {
public:
	GreatCircle() {};
	~GreatCircle() {};

	static void DrawCurve(PPM& image, const PPM::Color& color, const Vector2& start, const Vector2& end, const unsigned int& segments);

private:
	/// <summary>
	/// Converts Mercator to Equirectangular coordinates
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	static Vector2 ToEquirectangular(const Vector2& v);

	/// <summary>
	/// Converts Equirectangular to Mercator coordinates
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	static Vector2 ToMercator(const Vector2& v);
};