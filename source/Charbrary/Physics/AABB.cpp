#include "AABB.h"

#include <stdexcept>

namespace CB {

	AABB::AABB() : pos(0.f,0.f), size(0.f,0.f) {}

	AABB::AABB(Vector position, Vector widthAndHeight) : pos(position), size(widthAndHeight) {}

	AABB::AABB(float left, float top, float width, float height) : pos(left,top), size(width,height) {}

	void AABB::move(const Vector& movement) {
		pos += movement;
	}

	Vector AABB::center() const {
		return pos + size / 2;
	}

	Vector AABB::corner(const Corner corner) const {
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
		Vector centerPosBeforeTransform = center();
		size *= factor;
		pos = centerPosBeforeTransform - size / 2;
	}

	float AABB::perimeter() const {
		return 2 * (size.x + size.y);
	}

	float AABB::surface() const {
		return size.x * size.y;
	}

	float AABB::diagonalLength() const {
		return size.magnitude();
	}

	bool AABB::contains(const Vector& point) const {
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
		if (size.magnitudeSquared() >= other.size.magnitudeSquared()) {
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


