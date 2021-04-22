#pragma once

#include "vector_type_definition.h"

namespace ch {

	/*
	 * \brief Contains information about a collision between an AABB and a circle.
	 */
	struct CircleAABBCollision {
		vec_t normal; /**< The collision normal, a vector representing the direction of the collision. */
		float absoluteDepth; /**< The depth of the collision (always positive). Can be used with the normal to determine the collision correction. */
	};
}
