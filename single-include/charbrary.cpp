#include "charbrary.h"
// BEGIN CHARBRARY.CPP

#pragma once

#include <stdexcept>

namespace CB {
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

namespace CB {
	constexpr float DEGREES_TO_RADIANS = FLT_PI / 180.f;

	float vec_magnitude_squared(vec_t v)  {
		return v.x * v.x + v.y * v.y;
	}

	float vec_magnitude(vec_t v)  {
		return std::sqrtf(vec_magnitude_squared(v));
	}

	float vec_dot_product(vec_t a, vec_t b) {
		return a.x * b.x + a.y * b.y;
	}	

	vec_t vec_abs(vec_t v)  {
		return vec_t(std::abs(v.x), std::abs(v.y));
	}

	vec_t vec_normalize(vec_t v) {
		if (v.x == 0 && v.y == 0) {
			return vec_t();
		}

		return v / vec_magnitude(v);
	}

	vec_t vec_rotate(vec_t v, float angle)  {
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

#include <stdexcept>
#include <array>

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

namespace CB {

	Circle::Circle() : pos(), radius(0) {}

	Circle::Circle(const vec_t& position_, float radius_) : pos(position_), radius(radius_) {}

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

namespace CB {
	SegmentsIntersection::SegmentsIntersection(IntersectionType type_) : type(type_) {}
	SegmentsIntersection::SegmentsIntersection(IntersectionType type_, const vec_t& point_) : type(type_), point(point_) {}
	SegmentsIntersection::SegmentsIntersection(IntersectionType type_, const std::pair<vec_t, vec_t>& segment) : type(type_), resultingSegment(segment) {}
}

namespace CB {

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

	SegmentsIntersection LineSegment::checkForIntersection(const LineSegment& other) const {
		if (enclosingAABB().intersects(other.enclosingAABB())) {
			float slopeCurrent = slope();
			float slopeOther = other.slope();
			float YInterceptCurrent = YIntercept(start, slopeCurrent);
			float YInterceptOther = YIntercept(other.start, slopeOther);

			if (slopeCurrent == slopeOther) {
				if (YInterceptCurrent == YInterceptOther) {

					float minx = minX() < other.minX() ? minX() : other.minX();
					float maxx = maxX() > other.maxX() ? maxX() : other.maxX();
					float miny = minY() < other.minY() ? minY() : other.minY();
					float maxy = maxY() > other.maxY() ? maxY() : other.maxY();
		
					const vec_t* p1 = nullptr;
					const vec_t* p2 = nullptr;

					if (minx == maxx) {
						if (start.y == miny || start.y == maxy) {
							p1 = &end;
						}
						else {
							p1 = &start;
						}

						if (other.start.y == miny || other.start.y == maxy) {
							p2 = &other.end;
						}
						else {
							p2 = &other.start;
						}
					}
					else if (miny == maxy) {
						if (start.x == minx || start.x == maxx) {
							p1 = &end;
						}
						else {
							p1 = &start;
						}

						if (other.start.x == minx || other.start.x == maxx) {
							p2 = &other.end;
						}
						else {
							p2 = &other.start;
						}
					}
					else {
						if (start.x == minx || start.x == maxx || start.y == miny || start.y == maxy) {
							p1 = &end;
						}
						else {
							p1 = &start;
						}

						if (other.start.x == minx || other.start.x == maxx || other.start.y == miny || other.start.y == maxy) {
							p2 = &other.end;
						}
						else {
							p2 = &other.start;
						}
					}

					return SegmentsIntersection(IntersectionType::Overlapping, std::pair<vec_t, vec_t>{ *p1,*p2 });
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

					if (commonX > minX() && commonX < maxX() && commonX > other.minX() && commonX < other.maxX()) {
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

	AABB LineSegment::enclosingAABB() const {
		return AABB({ minX(), minY() }, absoluteSize());
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

namespace CB {

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
// END CHARBRARY.CPP