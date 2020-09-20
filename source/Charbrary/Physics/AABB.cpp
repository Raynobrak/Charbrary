#include "AABB.h"
#include "Constants.h"

#include <stdexcept>
#include <array>

namespace CB {
	constexpr Corner diagonally_opposed_corner(Corner corner) {
		constexpr std::array<Corner, static_cast<size_t>(Corner::MAX_VALUE)> DIAGONALLY_OPPOSED_CORNERS =
		{
			Corner::BottomRight,
			Corner::BottomLeft,
			Corner::TopRight,
			Corner::TopLeft
		};

		return DIAGONALLY_OPPOSED_CORNERS[static_cast<size_t>(corner)];
	}
}

namespace CB {

	AABB::AABB() : pos(0.f,0.f), size(0.f,0.f) {}

	AABB::AABB(const vec_t& pos_, const vec_t& size_) : pos(pos_), size(size_) {}

	AABB::AABB(float x, float y, float w, float h) : pos(x,y), size(w,h) {}

	void AABB::move(const vec_t& movement) {
		pos += movement;
	}

	vec_t AABB::center() const {
		return pos + size / 2.f;
	}

	vec_t AABB::corner(Corner corner) const {
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

	std::array<vec_t, static_cast<size_t>(Corner::MAX_VALUE)> AABB::corners() const
	{
		return 
		{
			corner(Corner::TopLeft),
			corner(Corner::TopRight),
			corner(Corner::BottomLeft),
			corner(Corner::BottomRight)
		};
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

	AABBCollision AABB::detectCollision(const AABB& other) const {
		if (!intersects(other)) {
			return { NULL_VEC, NULL_VEC };
		}

		auto currentCorners = corners();
		auto otherCorners = other.corners();

		auto otherCenter = other.center();

		float closestCornerDistanceSquared = std::numeric_limits<float>::infinity();

		Corner closestCorner = Corner::MAX_VALUE;

		for (size_t i = 0; i < static_cast<size_t>(Corner::MAX_VALUE); ++i) {
			float distanceToOtherCenterSquared = vec_magnitude(currentCorners[i] - otherCenter);

			if (distanceToOtherCenterSquared < closestCornerDistanceSquared) {
				closestCornerDistanceSquared = distanceToOtherCenterSquared;
				closestCorner = static_cast<Corner>(i);
			}
		}

		Corner oppositeCorner = diagonally_opposed_corner(closestCorner);

		auto c1 = currentCorners[static_cast<size_t>(closestCorner)];
		auto c2 = otherCorners[static_cast<size_t>(oppositeCorner)];
		vec_t delta =  c1 - c2;
		delta = vec_abs(delta);

		AABBCollision collision;
		collision.delta = delta;

		if (delta.x > delta.y) {
			if (closestCorner == Corner::TopLeft || closestCorner == Corner::TopRight)
				collision.normal = UP_VEC;
			else
				collision.normal = DOWN_VEC;
		}
		else {
			if (closestCorner == Corner::TopLeft || closestCorner == Corner::BottomLeft)
				collision.normal = LEFT_VEC;
			else
				collision.normal = RIGHT_VEC;
		}

		return collision;
	}

	bool operator==(const AABB& left, const AABB& right) {
		return left.pos == right.pos && left.size == right.size;
	}

	bool operator!=(const AABB& left, const AABB& right) {
		return !(left == right);
	}
}


