#include "AABBCollision.h"

namespace ch {
	float AABBCollision::absolutePenetrationDepthAlongNormal() const {
		return std::abs(vec_dot_product(normal, delta));
	}
}