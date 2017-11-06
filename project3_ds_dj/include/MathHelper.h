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
}

#endif