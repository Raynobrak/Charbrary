#pragma once

#include "vector_type_definition.h"

namespace ch {
	/**
	 * \brief Computes the magnitude squared of the given vector.
	 *
	 * The "magnitude squared" is useful because it allows to *compare*
	 * the magnitude of 2 vectors without having to square-root the values.
	 *
	 * \return The magnitude squared of the given vector.
	 */
	float vec_magnitude_squared(vec_t v);

	/**
	 * \brief Computes the magnitude of a vector.
	 *
	 * The magnitude is the "length" of a vector.
	 *
	 * \return The magnitude of the given vector.
	 */
	float vec_magnitude(vec_t v);

	/**
	 * \brief Computes the dot product of 2 vectors.
	 * \return The result of the dot product, a scalar.
	 */
	float vec_dot_product(vec_t a, vec_t b);

	/**
	 * \brief Makes the components of the vector positive.
	 * \return A vector whose components are positive numbers.
	 */
	vec_t vec_abs(vec_t v);

	/**
	 * \brief Normalizes the given vector.
	 *
	 * Computes the normalized version of the current vector. A normalized vector
     * is a vector with an intensity (magnitude) of 1. Normalized vectors can be
	 * used to represent directions.
	 *
	 * \return A normalized vector.
	 */
	vec_t vec_normalize(vec_t v);

	/**
	 * \brief Rotates a vector.
	 * \return A vector "rotated" by the given angle.
	 */
	vec_t vec_rotate(vec_t v, float angle);

	/**
	 * \brief Builds a vector from polar coordinates (a length and an angle).
	 * \return The polar coordinates converted to a cartesian vector.
	 */
	vec_t vec_from_polar_coordinates(float degrees, float length);
}

