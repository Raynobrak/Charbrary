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

