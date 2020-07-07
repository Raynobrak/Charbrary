#pragma once

#include "vector_type_definition.h"

namespace CB {
	vec_t fromPolarCoordinates(float degrees, float length);
	float magnitudeSquared(vec_t v);
	float magnitude(vec_t v);
	vec_t normalize(vec_t v);
	vec_t abs(vec_t v);
	vec_t rotate(vec_t v, float angle);
	float dotProduct(vec_t a, vec_t b);
}

