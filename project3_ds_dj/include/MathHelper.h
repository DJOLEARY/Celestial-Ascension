#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <SFML\Graphics.hpp>

// Add on functions for sfml vector data types
namespace sf
{
	inline float magnitude(Vector2f &vec)
	{
		return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
	}

	inline float magnitude(Vector3f &vec)
	{
		return sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	}

	inline Vector2f normalize(Vector2f &vec)
	{
		return vec / magnitude(vec);
	}

	inline Vector2f lerp(Vector2f &startPos, Vector2f &endPos, float t)
	{
		return (1.0f - t) * startPos + (t * endPos);
	}

    inline float distance(Vector2f &vec1, Vector2f &vec2)
    {
       return sqrtf(powf(vec2.x - vec1.x, 2) + powf(vec2.y - vec1.y, 2));
    }

	inline float distance(const Vector3f &vec1, const Vector3f &vec2)
	{
		return sqrtf(powf(vec2.x - vec1.x, 2) + powf(vec2.y - vec1.y, 2) + powf(vec2.z - vec1.z, 2));
	}

	inline float distanceSquared(Vector2f &vec1, Vector2f &vec2)
	{
		return powf(vec2.x - vec1.x, 2) + powf(vec2.y - vec1.y, 2);
	}

	inline float distanceSquared(Vector2f &vec)
	{
		return powf(vec.x, 2) + powf(vec.y, 2);
	}

	inline float distanceSquared(Vector3f &vec)
	{
		return powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2);
	}

	inline float catmullRom(const float value1, const float value2, const float value3, const float value4, float amount)
	{
		// Using formula from http://www.mvps.org/directx/articles/catmull/
		// Internally using doubles not to lose precission
		float amountSquared = amount * amount;
		float amountCubed = amountSquared * amount;
		return (0.5f * (2.0f * value2 +
			(value3 - value1) * amount +
			(2.0f * value1 - 5.0f * value2 + 4.0f * value3 - value4) * amountSquared +
			(3.0f * value2 - value1 - 3.0f * value3 + value4) * amountCubed));
	}

	inline Vector2f catmullRom(
		const Vector2f& value1,
		const Vector2f& value2,
		const Vector2f& value3,
		const Vector2f& value4,
		float amount
	)
	{
		return Vector2f(catmullRom(value1.x, value2.x, value3.x, value4.x, amount),
			catmullRom(value1.y, value2.y, value3.y, value4.y, amount));
	}
}

#endif