#pragma once

#include "../maths/Vector2.h"
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
	/// <param name="v">Between -0.5 to 0.5</param>
	/// <returns></returns>
	static Vector2 ToEquirectangular(const Vector2& v);

	/// <summary>
	/// Converts Equirectangular to Mercator coordinates
	/// </summary>
	/// <param name="v"></param>
	/// <returns>Between -0.5 to 0.5</returns>
	static Vector2 ToMercator(const Vector2& v);

	static float Alpha(const Vector2& start, const Vector2& end);

	static float K(const float& alpha, const float& t);
	static float X(const float& k, const Vector2& start, const Vector2& end);
	static float Y(const float& k, const Vector2& start, const Vector2& end);
	static float Z(const float& k, const Vector2& start, const Vector2& end);

	/// <summary>
	/// Gets point in segment
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="t">aka the factor</param>
	/// <param name="start"></param>
	/// <param name="end"></param>
	/// <param name="pixelMax">the size of the image</param>
	/// <returns>Converted to pixel coordinates</returns>
	static Vector2 Point(const float alpha, const float& t, const Vector2& start, const Vector2& end, const Vector2& pixelMax);
};