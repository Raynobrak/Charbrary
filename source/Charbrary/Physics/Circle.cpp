/* Copyright 2019 Lucas Charbonnier

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#include "Circle.h"
#include "Constants.h"

namespace CB {

	Circle::Circle() : pos(), radius(0) {}

	Circle::Circle(const Vector& position, float radius_) : pos(position), radius(radius_) {}

	float Circle::diameter() const {
		return 2 * radius;
	}

	float Circle::circumference() const {
		return 2 * CB::FLT_PI * radius;
	}

	float Circle::area() const {
		return CB::FLT_PI * radius * radius;
	}

	AABB Circle::enclosingAABB() const {
		return AABB(pos.x - radius, pos.y - radius, radius * 2, radius * 2);
	}

	bool Circle::contains(const Vector& point) const {
		return (pos - point).magnitudeSquared() < radius * radius;
	}

	bool Circle::intersects(const Circle& other) const {
		return (pos - other.pos).magnitudeSquared() < (radius + other.radius) * (radius + other.radius);
	}

	bool Circle::strictlyContains(const Circle& other) const {
		if (other.radius < radius) {
			return (pos - other.pos).magnitudeSquared() < (radius - other.radius) * (radius - other.radius);
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

