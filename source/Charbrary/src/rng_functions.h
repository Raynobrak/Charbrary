#pragma once

#include "vector_type_definition.h"

#include <vector>

namespace ch { 
	namespace rand {

		/**
		 * \brief Generates a random integer within the given boundaries. The lower and upper limits are inclusive, meaning they are included in the range of possible values.
		 */
		int rand_int(int lowerInc, int upperInc);

		/**
		 * \brief Generates a random float within the given boundaries. The lower and upper limits are inclusive, meaning they are included in the range of possible values.
		 */
		float rand_float(float min, float max);

		/**
		* \brief Returns a random boolean.
		*/
		bool rand_bit();
		 
		/**
		* \brief Returns a boolean with the given probability of being true.
		*/
		bool rand_bit(float probability);

		/**
		* \brief Generates a random normalized float (between -1 and 1).
		*/
		float rnd_normal_float();

		/**
		 * \brief Generates a random angle in degrees (between 0 and 360).
		 */
		float rnd_angle_deg();

		/**
		 * \brief Generates a random angle in radians (between 0 and 2*pi).
		 */
		float rnd_angle_rad();

		/**
		 * \brief Generates a vector with random XY values within the given boundaries.
		 */
		vec_t rand_vector(float minX, float maxX, float minY, float maxY);

		/**
		 * \brief Generates a random unit vector.
		 */
		vec_t rand_unit_vector();

		/**
		 * \brief Generates a random point located on the given rectangle.
		 */
		vec_t rand_point_on_rect(vec_t topLeftCorner, vec_t size);

		/**
		 * \brief Generates a random point located on the given rectangle.
		 */
		vec_t rand_point_on_rect(vec_t center, float width, float height);

		/**
		 * \brief Generates a random point located on the given circle.
		 */
		vec_t rand_point_on_circle(float circleRadius, vec_t circleCenter = { 0.f,0.f });

		/**
		 * \brief Generates a random point located on the given taurus (taurus = donut).
		 */
		vec_t rand_point_on_torus(float innerRadius, float outerRadius, vec_t torusCenter = { 0.f,0.f });
	}
}
