#include "Circle.h"
#include "Constants.h"

namespace ch {

	Circle::Circle() : pos(), radius(0) {}

	Circle::Circle(const vec_t& position_, float radius_) : pos(position_), radius(radius_) {}

	float Circle::diameter() const {
		return 2 * radius;
	}

	float Circle::circumference() const {
		return 2 * ch::FLT_PI * radius;
	}

	float Circle::area() const {
		return ch::FLT_PI * radius * radius;
	}

	AABB Circle::enclosingAABB() const {
		return AABB(pos.x - radius, pos.y - radius, radius * 2, radius * 2);
	}

	bool Circle::contains(const vec_t& point) const {
		return vec_magnitude_squared(pos - point) < radius * radius;
	}

	bool Circle::intersects(const Circle& other) const {
		return vec_magnitude_squared(pos - other.pos) < (radius + other.radius) * (radius + other.radius);
	}

	bool Circle::strictlyContains(const Circle& other) const {
		if (other.radius <= radius) {
			return vec_magnitude_squared(pos - other.pos) <= (radius - other.radius) * (radius - other.radius);
		}
		return false;
	}

	void Circle::operator=(const Circle& toCopy) {
		pos = toCopy.pos;
		radius = toCopy.radius;
	}

	bool operator==(const Circle& left, const Circle& right) {
		return left.radius == right.radius && left.pos == right.pos;
	}

	bool operator!=(const Circle& left, const Circle& right) {
		return !(left == right);
	}
}

