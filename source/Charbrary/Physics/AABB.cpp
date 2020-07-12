#include "AABB.h"

#include <stdexcept>

namespace CB {

	AABB::AABB() : pos(0.f,0.f), size(0.f,0.f) {}

	AABB::AABB(const vec_t& position, const vec_t& size_) : pos(position), size(size_) {}

	AABB::AABB(float left, float top, float width, float height) : pos(left,top), size(width,height) {}

	void AABB::move(const vec_t& movement) {
		pos += movement;
	}

	vec_t AABB::center() const {
		return pos + size / 2.f;
	}

	vec_t AABB::corner(const Corner corner) const {
		switch (corner) {
		case Corner::TopLeft:
			return pos;
		case Corner::TopRight:
			return { pos.x + size.x, pos.y };
		case Corner::BottomLeft:
			return { pos.x, pos.y + size.y };
		case Corner::BottomRight:
			return pos + size;
		default:
			throw std::invalid_argument("corner");
		}
	}

	void AABB::scaleRelativeToCenter(float factor) {
		vec_t centerPosBeforeTransform = center();
		size *= factor;
		pos = centerPosBeforeTransform - size / 2.f;
	}

	float AABB::perimeter() const {
		return 2 * (size.x + size.y);
	}

	float AABB::area() const {
		return size.x * size.y;
	}

	float AABB::diagonalLength() const {
		return vec_magnitude(size);
	}

	bool AABB::contains(const vec_t& point) const {
		return	
			point.x >= pos.x &&
			point.y >= pos.y &&
			point.x <= pos.x + size.x &&
			point.y <= pos.y + size.y;
	}

	bool AABB::intersects(const AABB& other) const {
		AABB extended = other;

		extended.size += size;
		extended.pos -= size;

		return extended.contains(pos);
	}

	bool AABB::strictlyContains(const AABB& other) const {
		if (vec_magnitude_squared(size) >= vec_magnitude_squared(other.size)) {
			AABB zone = *this;
			zone.size -= other.size;

			return zone.contains(other.pos);
		}
		return false;
	}

	bool operator==(const AABB& left, const AABB& right) {
		return left.pos == right.pos && left.size == right.size;
	}

	bool operator!=(const AABB& left, const AABB& right) {
		return !(left == right);
	}
}


