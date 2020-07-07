#include "VectorMaths.h"
#include "Constants.h"

#include <cmath>
#include <stdexcept>

namespace CB {
	constexpr float DEGREES_TO_RADIANS = FLT_PI / 180.f;

	vec_t fromPolarCoordinates(float degrees, float length) {
		degrees *= DEGREES_TO_RADIANS;
		return length * vec_t(std::cosf(degrees), std::sinf(degrees));
	}

	float magnitudeSquared(vec_t v)  {
		return v.x * v.x + v.y * v.y;
	}

	float magnitude(vec_t v)  {
		return std::sqrtf(magnitudeSquared(v));
	}

	vec_t normalize(vec_t v)  {
		if (v.x == 0 && v.y == 0) {
			return vec_t();
		}

		return v / magnitude(v);
	}

	vec_t abs(vec_t v)  {
		return vec_t(std::abs(v.x), std::abs(v.y));
	}

	vec_t rotate(vec_t v, float angle)  {
		angle *= DEGREES_TO_RADIANS;

		// Formula taken from https://matthew-brett.github.io/teaching/rotation_2d.html
		return vec_t(std::cosf(angle) * v.x - std::sinf(angle) * v.y, std::sinf(angle) * v.x + std::cosf(angle) * v.y);
	}

	float dotProduct(vec_t a, vec_t b) {
		return a.x * b.x + a.y * b.y;
	}
}
