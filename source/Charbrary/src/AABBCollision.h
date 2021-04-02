#pragma once

#include "vector_type_definition.h"
#include "Constants.h"

namespace ch {

	/*
	 * \brief Contains information about the collision of 2 AABBs.
	 */
	struct AABBCollision {
		vec_t normal; /**< The collision normal, a vector representing the direction of the collision. */
		vec_t delta; /**< The overlap of the colliding AABB on the other AABB. */
	};

	
}
