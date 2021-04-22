#include "charbrary.h"
// BEGIN CHARBRARY.CPP

#pragma once

#include <stdexcept>

namespace ch {
	Vector::Vector(float X, float Y) : x(X), y(Y) {}

	Vector & Vector::operator+=(const Vector & add) {
		x += add.x;
		y += add.y;
		return *this;
	}

	Vector & Vector::operator-=(const Vector & substract) {
		*this += -substract;
		return *this;
	}

	Vector & Vector::operator*=(const float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector & Vector::operator/=(const float divisor) {
		if (divisor == 0) {
			throw std::invalid_argument("Invalid argument : Cannot divide vector by 0");
		}
		x /= divisor;
		y /= divisor;
		return *this;
	}

	void Vector::operator=(const Vector & other) {
		x = other.x;
		y = other.y;
	}

	Vector operator+(const Vector & left, const Vector & right) {
		return Vector(left.x + right.x, left.y + right.y);
	}

	Vector operator-(const Vector & left, const Vector & right) {
		return Vector(left.x - right.x, left.y - right.y);
	}

	Vector operator-(const Vector & right) {
		return Vector(-right.x, -right.y);
	}

	Vector operator*(const Vector & base, const float scalar) {
		return Vector(base.x * scalar, base.y * scalar);
	}

	Vector operator*(const float scalar, const Vector & base) {
		return base * scalar;
	}

	Vector operator/(const Vector & base, const float divisor) {
		if (divisor == 0) {
			throw std::invalid_argument("Invalid argument : Cannot divide vector by 0");
		}
		return Vector(base.x / divisor, base.y / divisor);
	}

	bool operator==(const Vector & left, const Vector & right) {
		return left.x == right.x && left.y == right.y;
	}

	bool operator!=(const Vector & left, const Vector & right) {
		return !(left == right);
	}
}

#include <cmath>
#include <stdexcept>

namespace ch {
	constexpr float DEGREES_TO_RADIANS = FLT_PI / 180.f;

	float vec_magnitude_squared(vec_t v) {
		return v.x * v.x + v.y * v.y;
	}

	float vec_magnitude(vec_t v) {
		return std::sqrtf(vec_magnitude_squared(v));
	}

	float vec_dot_product(vec_t a, vec_t b) {
		return a.x * b.x + a.y * b.y;
	}	

	vec_t vec_abs(vec_t v) {
		return vec_t(std::abs(v.x), std::abs(v.y));
	}

	vec_t vec_normalize(vec_t v) {
		if (v.x == 0.f && v.y == 0.f) {
			return NULL_VEC;
		}

		return v / vec_magnitude(v);
	}

	vec_t vec_rotate(vec_t v, float angle) {
		angle *= DEGREES_TO_RADIANS;

		// Formula taken from https://matthew-brett.github.io/teaching/rotation_2d.html
		return vec_t(std::cosf(angle) * v.x - std::sinf(angle) * v.y, std::sinf(angle) * v.x + std::cosf(angle) * v.y);
	}

	vec_t vec_from_polar_coordinates(float degrees, float length) {
		degrees *= DEGREES_TO_RADIANS;
		return length * vec_t(std::cosf(degrees), std::sinf(degrees));
	}
}

#include <array>

namespace ch {
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

	constexpr Corner vertically_opposed_corner(Corner corner) {
		constexpr std::array<Corner, static_cast<size_t>(Corner::MAX_VALUE)> VERTICALLY_OPPOSED_CORNERS =
		{
			Corner::BottomLeft,
			Corner::BottomRight,
			Corner::TopLeft,
			Corner::TopRight
		};
		return VERTICALLY_OPPOSED_CORNERS[static_cast<size_t>(corner)];
	}

	constexpr Corner horizontally_opposed_corner(Corner corner) {
		constexpr std::array<Corner, static_cast<size_t>(Corner::MAX_VALUE)> HORIZONTALLY_OPPOSED_CORNERS =
		{
			vertically_opposed_corner(diagonally_opposed_corner(Corner::TopLeft)),
			vertically_opposed_corner(diagonally_opposed_corner(Corner::TopRight)),
			vertically_opposed_corner(diagonally_opposed_corner(Corner::BottomLeft)),
			vertically_opposed_corner(diagonally_opposed_corner(Corner::BottomRight))
		};
		return HORIZONTALLY_OPPOSED_CORNERS[static_cast<size_t>(corner)];
	}
}

namespace ch {
	float AABBCollision::absolutePenetrationDepthAlongNormal() const {
		return std::abs(vec_dot_product(normal, delta));
	}
}

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

#include <stdexcept>

namespace ch {

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

	bool operator==(const AABB& left, const AABB& right) {
		return left.pos == right.pos && left.size == right.size;
	}

	bool operator!=(const AABB& left, const AABB& right) {
		return !(left == right);
	}
}

namespace ch {
	SegmentsIntersection::SegmentsIntersection(IntersectionType type_) : type(type_) {}
	SegmentsIntersection::SegmentsIntersection(IntersectionType type_, const vec_t& point_) : type(type_), point(point_) {}
	SegmentsIntersection::SegmentsIntersection(IntersectionType type_, const std::pair<vec_t, vec_t>& segment) : type(type_), resultingSegment(segment) {}
}

namespace ch {

	LineSegment::LineSegment() : start(), end() {}

	LineSegment::LineSegment(const vec_t& start_, const vec_t& end_) : start(start_), end(end_) {}

	float LineSegment::length() const {
		return vec_magnitude(end - start);
	}

	float LineSegment::lengthSquared() const {
		return vec_magnitude_squared(end - start);
	}

	vec_t LineSegment::absoluteSize() const {
		return vec_abs(end - start);
	}

	vec_t LineSegment::dirFromStart() const {
		return vec_normalize(end - start);
	}

	float LineSegment::slope() const {
		vec_t size = start - end;
		if (size.x != 0) {
			return size.y / size.x;
		}
		else {
			return std::numeric_limits<float>::infinity();
		}
	}

	float LineSegment::minX() const {
		return start.x < end.x ? start.x : end.x;
	}

	float LineSegment::minY() const {
		return start.y < end.y ? start.y : end.y;
	}

	float LineSegment::maxX() const {
		return start.x > end.x ? start.x : end.x;
	}

	float LineSegment::maxY() const {
		return start.y > end.y ? start.y : end.y;
	}

	float LineSegment::YIntercept(const vec_t& anyPoint, float slope) {
		return slope != std::numeric_limits<float>::infinity() ? anyPoint.y - slope * anyPoint.x : slope;
	}

	void LineSegment::operator=(const LineSegment& model) {
		start = model.start;
		end = model.end;
	}

	bool operator==(const LineSegment& left, const LineSegment& right) {
		return 
			(left.start == right.start && left.end == right.end)
			||
			(left.start == right.end && left.end == right.start);
	}

	bool operator!=(const LineSegment& left, const LineSegment& right) {
		return !(left == right);
	}
}

namespace ch {

	Stopwatch::Stopwatch() {
		start();
	}

	void Stopwatch::start() {
		start_ = now();
	}

	void Stopwatch::reset() {
		start();
	}

	void Stopwatch::stop() {
		end_ = now();
	}

	long Stopwatch::elapsedSeconds() {
		stop();
		return std::chrono::duration_cast<std::chrono::seconds>(end_ - start_).count();
	}

	long Stopwatch::elapsedMilliseconds() {
		stop();
		return std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_).count();
	}

	long Stopwatch::elapsedMicroseconds() {
		stop();
		return std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count();
	}

	long Stopwatch::elapsedNanoseconds() {
		stop();
		return std::chrono::duration_cast<std::chrono::nanoseconds>(end_ - start_).count();
	}

	Stopwatch::time_point Stopwatch::now() const {
		return std::chrono::system_clock::now();
	}
}

#include <random>
#include <chrono>

namespace ch {
	namespace rand {

		/**
		 * \brief Returns a reference to a static instance of the random engine.
		 */
		std::default_random_engine& get_random_engine() {
			static std::default_random_engine rng{ static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()) };
			return rng;
		}

		int rand_int(int lowerInc, int upperInc) {
			std::uniform_int_distribution<int> distribution(lowerInc, upperInc);
			return distribution(get_random_engine());
		}

		float rand_float(float min, float max) {
			std::uniform_real_distribution<float> distribution(min, max);
			return distribution(get_random_engine());
		}

		bool rand_bit() {
			return rand_int(0, 1) == 0;
		}

		bool rand_bit(float probability) {
			return rand_float(0.f, 1.f) <= probability;
		}

		float rnd_normal_float() {
			return rand_float(-1.f, 1.f);
		}

		float rnd_angle_deg() {
			return rand_float(0.f, 360.f);
		}

		float rnd_angle_rad() {
			static constexpr float PI_2 = 2.f * 3.1415926f;
			return rand_float(0.f, PI_2);
		}

		vec_t rand_vector(float minX, float maxX, float minY, float maxY) {
			return vec_t(rand_float(minX, maxX), rand_float(minY, maxY));
		}

		vec_t rand_unit_vector() {
			float randomRadianAngle = rnd_angle_rad();
			return vec_t(std::cosf(randomRadianAngle), std::sinf(randomRadianAngle));
		}

		vec_t rand_point_on_rect(vec_t topLeftCorner, vec_t size) {
			auto bottomRightCorner = topLeftCorner + size;
			return rand_vector(topLeftCorner.x, topLeftCorner.y, bottomRightCorner.x, bottomRightCorner.y);
		}

		vec_t rand_point_on_rect(vec_t center, float width, float height) {
			return center + vec_t(rnd_normal_float() * (width / 2.f), rnd_normal_float() * (height / 2.f));
		}

		vec_t rand_point_on_circle(float circleRadius, vec_t circleCenter) {
			return circleCenter + rand_unit_vector() * rand_float(0.f, circleRadius);
		}

		vec_t rand_point_on_torus(float innerRadius, float outerRadius, vec_t torusCenter) {
			return torusCenter + rand_unit_vector() * rand_float(innerRadius, outerRadius);
		}
	}
}

namespace ch {
	namespace collision {
		Circle enclosingCircle(const AABB& aabb) {
			return Circle(aabb.center(), aabb.diagonalLength() / 2.f);
		}

		Circle inscribedCircle(const AABB& aabb) {
			return Circle(aabb.center(), std::min(aabb.size.x, aabb.size.y) / 2.f);
		}

		AABB enclosingAABB(const Circle& circle) {
			return AABB(circle.pos.x - circle.radius, circle.pos.y - circle.radius, circle.radius * 2, circle.radius * 2);
		}

		AABB enclosingAABB(const LineSegment& lineSegment) {
			return AABB({ lineSegment.minX(), lineSegment.minY() }, lineSegment.absoluteSize());
		}

		AABB inscribedAABB(const Circle& circle) {
			float halfSide = sqrtf(circle.radius * circle.radius / 2.f);
			auto halfSize = vec_t(halfSide, halfSide);
			return AABB(circle.pos - halfSize, halfSize * 2.f);
		}

		bool aabb_contains(const AABB& aabb, const vec_t& point) {
			return
				point.x >= aabb.pos.x &&
				point.y >= aabb.pos.y &&
				point.x <= aabb.pos.x + aabb.size.x &&
				point.y <= aabb.pos.y + aabb.size.y;
		}

		bool aabb_contains(const AABB& first, const AABB& other) {
			if (first.area() >= other.area()) {
				AABB zone = first;
				zone.size -= other.size;

				return aabb_contains(zone, other.pos);
			}
			return false;
		}

		bool aabb_contains(const AABB& aabb, const Circle& circle) {
			return aabb_contains(aabb, enclosingAABB(circle));
		}

		bool circle_contains(const Circle& circle, const vec_t& point) {
			return vec_magnitude_squared(circle.pos - point) < circle.radius * circle.radius;
		}

		bool circle_contains(const Circle& first, const Circle& other) {
			if (other.radius <= first.radius) {
				return vec_magnitude_squared(first.pos - other.pos) <= (first.radius - other.radius) * (first.radius - other.radius);
			}
			return false;
		}

		bool circle_contains(const Circle& circle, const AABB& aabb) {
			return
				circle_contains(circle, aabb.corner(ch::Corner::TopLeft)) &&
				circle_contains(circle, aabb.corner(ch::Corner::TopRight)) &&
				circle_contains(circle, aabb.corner(ch::Corner::BottomLeft)) &&
				circle_contains(circle, aabb.corner(ch::Corner::BottomRight));
		}

		bool aabb_intersects(const AABB& a, const AABB& b) {
			AABB extended = b;

			extended.size += a.size;
			extended.pos -= a.size;

			return aabb_contains(extended, a.pos);
		}

		bool aabb_intersects(const AABB& aabb, const Circle& circle) {
			// First check : are the circle and the box close enough to be colliding ?
			if (!aabb_intersects(aabb, enclosingAABB(circle))) {
				return false;
			}

			// Second check : does the circle contain any of the box corners ?
			if (circle_contains(circle, aabb.corner(ch::Corner::TopLeft)) ||
				circle_contains(circle, aabb.corner(ch::Corner::TopRight)) ||
				circle_contains(circle, aabb.corner(ch::Corner::BottomLeft)) ||
				circle_contains(circle, aabb.corner(ch::Corner::BottomRight)))
					return true;

			// Last check : does the aabb contain any of the extremums of the circle ?
			if (aabb_contains(aabb, circle.pos + LEFT_VEC * circle.radius) ||
				aabb_contains(aabb, circle.pos + RIGHT_VEC * circle.radius) ||
				aabb_contains(aabb, circle.pos + UP_VEC * circle.radius) ||
				aabb_contains(aabb, circle.pos + DOWN_VEC * circle.radius))
					return true;

			return false;
		}

		bool circle_intersects(const Circle& circle, const Circle& other) {
			return vec_magnitude_squared(circle.pos - other.pos) < (circle.radius + other.radius) * (circle.radius + other.radius);
		}

		bool circle_intersects(const Circle& circle, const AABB& aabb) {
			return aabb_intersects(aabb, circle);
		}

		float circles_distance(const Circle& a, const Circle& b) {
			return vec_magnitude(a.pos - b.pos) - a.radius - b.radius;
		}
		
		AABBCollision aabb_collision_info(const AABB& first, const AABB& other) {
			if (!aabb_intersects(first, other)) {
				return AABBCollision{ NULL_VEC, NULL_VEC };
			}

			auto currentCorners = first.corners();
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
			vec_t delta = c1 - c2;
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

		CirclesCollision circles_collision_info(const Circle& first, const Circle& other) {
			if (!circle_intersects(first, other))
				return CirclesCollision{ NULL_VEC, 0.f };

			return CirclesCollision{ vec_normalize(other.pos - first.pos), std::abs(circles_distance(first, other)) };
		}

		CircleAABBCollision circle_aabb_collision_info(const AABB& aabb, const Circle& circle) {
			static const CircleAABBCollision NO_COLLISION = CircleAABBCollision{ NULL_VEC, 0.f };

			if (!aabb_intersects(aabb, enclosingAABB(circle))) {
				return NO_COLLISION;
			}

			if ((circle.pos.x > aabb.pos.x && circle.pos.x < aabb.pos.x + aabb.size.x) ||
				(circle.pos.y > aabb.pos.y && circle.pos.y < aabb.pos.y + aabb.size.y)) {
				auto aabbColl = aabb_collision_info(aabb, enclosingAABB(circle));
				return CircleAABBCollision{ aabbColl.normal, aabbColl.absolutePenetrationDepthAlongNormal() };
			}
			else {
				auto corners = aabb.corners();
				for (const auto& corner : corners) {
					if (circle_contains(circle, corner)) {
						auto dir = vec_normalize(circle.pos - corner);
						float depth = circle.radius - vec_magnitude(circle.pos - corner);
						return CircleAABBCollision{ dir, depth };
					}
				}
			}

			return NO_COLLISION;
		}

		SegmentsIntersection line_segments_intersection_info(const LineSegment& first, const LineSegment& other) {
			if (collision::aabb_intersects(enclosingAABB(first), enclosingAABB(other))) {
				float slopeCurrent = first.slope();
				float slopeOther = other.slope();
				float YInterceptCurrent = LineSegment::YIntercept(first.start, slopeCurrent);
				float YInterceptOther = LineSegment::YIntercept(other.start, slopeOther);

				if (slopeCurrent == slopeOther) {
					if (YInterceptCurrent == YInterceptOther) {

						float minx = first.minX() < other.minX() ? first.minX() : other.minX();
						float maxx = first.maxX() > other.maxX() ? first.maxX() : other.maxX();
						float miny = first.minY() < other.minY() ? first.minY() : other.minY();
						float maxy = first.maxY() > other.maxY() ? first.maxY() : other.maxY();

						const vec_t* p1 = nullptr;
						const vec_t* p2 = nullptr;

						if (minx == maxx) {
							if (first.start.y == miny || first.start.y == maxy) {
								p1 = &first.end;
							}
							else {
								p1 = &first.start;
							}

							if (other.start.y == miny || other.start.y == maxy) {
								p2 = &other.end;
							}
							else {
								p2 = &other.start;
							}
						}
						else if (miny == maxy) {
							if (first.start.x == minx || first.start.x == maxx) {
								p1 = &first.end;
							}
							else {
								p1 = &first.start;
							}

							if (other.start.x == minx || other.start.x == maxx) {
								p2 = &other.end;
							}
							else {
								p2 = &other.start;
							}
						}
						else {
							if (first.start.x == minx || first.start.x == maxx || first.start.y == miny || first.start.y == maxy) {
								p1 = &first.end;
							}
							else {
								p1 = &first.start;
							}

							if (other.start.x == minx || other.start.x == maxx || other.start.y == miny || other.start.y == maxy) {
								p2 = &other.end;
							}
							else {
								p2 = &other.start;
							}
						}

						return SegmentsIntersection(IntersectionType::Overlapping, std::pair<vec_t, vec_t>{ *p1, *p2 });
					}
					else {
						return SegmentsIntersection(IntersectionType::None);
					}
				}
				else {
					if (YInterceptCurrent == YInterceptOther) {

						return SegmentsIntersection(IntersectionType::Crossing, vec_t(0, YInterceptCurrent));
					}
					else {
						float commonX = (YInterceptOther - YInterceptCurrent) / (slopeCurrent - slopeOther);

						if (commonX > first.minX() && commonX < first.maxX() && commonX > other.minX() && commonX < other.maxX()) {
							float commonY = slopeCurrent * commonX + YInterceptCurrent;

							return SegmentsIntersection(IntersectionType::Crossing, vec_t(commonX, commonY));
						}
						else {
							return SegmentsIntersection(IntersectionType::None);
						}
					}
				}
			}
			else {
				return SegmentsIntersection(IntersectionType::None);
			}
		}
	}
}

// END CHARBRARY.CPP