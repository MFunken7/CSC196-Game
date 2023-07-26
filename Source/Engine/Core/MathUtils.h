#pragma once
#include <cmath>
#include <utility>

namespace kiko {
	constexpr float Pi = 3.14159265359f;
	constexpr float TwoPi = 6.28318530718;
	constexpr float HalfPi = 1.57079632679;

	constexpr float RadiansToDegrees(float radians) { return radians * (180.0f / Pi); }
	constexpr float DegreesToRadians(float degrees) { return degrees * (Pi / 180.0f); }

	constexpr int Wrap(int value, int max)
	{
		return (value % max) + (( value < 0) ? max : 0);
	}

	inline float Wrap(float value, float max)
	{
		return std::fmod(value, max) + ((value < 0) ? max : 0);
	}

	template <typename T>
	inline T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	template <typename T>
	inline T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template <typename T>
	inline T Clamp(T value, T min, T max)
	{
		if (min > max) std::swap(min, max);

		if (value < min) value = min;
		else if (value > max) value = max;

		return  (value < min) ? min : (value > max) ? max : value;
	}

	template<typename T>
	constexpr T Lerp(const T& a, const T& b, float t) // t = 0 <-> 1
	{
		return (a * (1.0f - t)) + (b * t);
	}
}