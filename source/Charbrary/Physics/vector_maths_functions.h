#pragma once

#include "vector_type_definition.h"

namespace CB {
	float vec_magnitude_squared(vec_t v);
	float vec_magnitude(vec_t v);
	float vec_dot_product(vec_t a, vec_t b);

	vec_t vec_abs(vec_t v);
	vec_t vec_normalize(vec_t v);
	vec_t vec_rotate(vec_t v, float angle);
	vec_t vec_from_polar_coordinates(float degrees, float length);
}

