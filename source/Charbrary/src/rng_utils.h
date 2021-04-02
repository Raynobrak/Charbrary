#pragma once

#include "vector_type_definition.h"

namespace CB {

	// Generates a random integer between the given boundaries.
	int rnd_int(int lowerInc, int upperInc);

	// Generates a random float within the given boundaries.
	float rnd_float(float min, float max);

	// Generates a random normalized float (between -1 and 1).
	float rnd_normal_float();

	// Generates a float representing an angle in degrees (between 0 and 360).
	float rnd_angle_deg();

	// Generates a float representing an angle in radians (between 0 and 2*pi).
	float rnd_angle_rad();

	// Generates a vector with random XY values between the given boundaries.
	vec_t rnd_sfvector(float minX, float maxX, float minY, float maxY);

	// Generates a random unit vector.
	vec_t rnd_unit_sfvector();

	// Generates a random point located within the given rectangle.
	vec_t rnd_point_on_rect(vec_t topLeftCorner, vec_t size);

	// Generates a random point located within the given rectangle.
	vec_t rnd_point_on_rect(vec_t center, float width, float height);

	// Generates a random point located within the given circle.
	vec_t rnd_point_on_circle(float circleRadius, vec_t circleCenter = { 0.f,0.f });

	// Generates a random point located on the given taurus (taurus = donut).
	vec_t rnd_point_on_torus(float innerRadius, float outerRadius, vec_t torusCenter = { 0.f,0.f });
}
