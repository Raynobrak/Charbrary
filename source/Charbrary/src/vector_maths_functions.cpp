#include "vector_maths_functions.h"
#include "Constants.h"

#include <cmath>
#include <stdexcept>

namespace ch {
	constexpr float DEGREES_TO_RADIANS = FLT_PI / 180.f;

	float vec_magnitude_squared(vec_t v) {
		return v.x * v.x + v.y * v.y;
	}

	float vec_magnitude(vec_t v) {
		return std::sqrtf(vec_magnitude_squared(v));
	}

	float vec_dot_product(vec_t a, vec_t b) {
		return a.x * b.x + a.y * b.y;
	}	

	vec_t vec_abs(vec_t v) {
		return vec_t(std::abs(v.x), std::abs(v.y));
	}

	vec_t vec_normalize(vec_t v) {
		if (v.x == 0.f && v.y == 0.f) {
			return NULL_VEC;
		}

		return v / vec_magnitude(v);
	}

	vec_t vec_rotate(vec_t v, float angle) {
		angle *= DEGREES_TO_RADIANS;

		// Formula taken from https://matthew-brett.github.io/teaching/rotation_2d.html
		return vec_t(std::cosf(angle) * v.x - std::sinf(angle) * v.y, std::sinf(angle) * v.x + std::cosf(angle) * v.y);
	}

	vec_t vec_from_polar_coordinates(float degrees, float length) {
		degrees *= DEGREES_TO_RADIANS;
		return length * vec_t(std::cosf(degrees), std::sinf(degrees));
	}
}
