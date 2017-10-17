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

	inline Vector2f normalize(Vector2f &vec)
	{
		return vec / magnitude(vec);
	}
}

#endif