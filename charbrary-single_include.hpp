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

#pragma once

// Uncomment the following line to use the vectors from the SFML library.
// #define USE_SFML_VECTORS 1

namespace CB {
	constexpr float FLT_PI = 3.14159265359f;
}

#include <string>

namespace CB {

	/*
	/**
	 * \brief Represents a 2D vector.
	 * 
	 * Represents a 2D vector whose components are axis-aligned. This class can be used
	 * to represent physical properties such as
	 * - acceleration
	 * - velocity
	 * - position
	 * - size
	 * - force
	 * - etc...
	 * 
	 * The components are public and can be directly like so
	 * 
	 * Common vector operations such as computing the magnitude, normalizing or
	 * computing the dot product are encapsulated in member functions.
	 * 
	 * Most operators are overloaded to simplify vector calculus.
	 */
	class Vector {
	public:	
		float x; /**< Horizontal component of the vector. */
		float y; /**< Vertical component of the vector. */
	public:
		/**
		 * \brief Constructs a new Vector from it's X and Y values.
		 * \param X Horizontal component
		 * \param Y Vertical component
		 * 
		 * By default, X and Y will be equal to 0. So constructing a vector without any
		 * parameters is absolutely valid.
		 */
		Vector(float X = 0.f, float Y = 0.f);

		/**
		 * \brief Overload of the addition-assignment operator.
		 * 
		 * The vector given as parameter will be added onto the current vector. Their
		 * components will be added respectively.
		 * 
		 * \param add The vector that will be added to the current vector.
		 * \return A reference to the current vector.
		 */
		Vector& operator+=(const Vector& add);

		/**
		 * \brief Overload of the substraction-assignment operator.
		 * 
		 * The components of the current vector will be respectively substracted by the
		 * components of the vector given as parameter.
		 * 
		 * \param add The vector that the current vector will be substracted by.
		 * \return A reference to the current vector.
		 */
		Vector& operator-=(const Vector& substract);

		/**
		 * \brief Overload of the multiplication-assignment operator.
		 * 
		 * Amplifies (or "scales") the current vector by a scalar. Each component will be
		 * multiplied by the given scalar.
		 * 
		 * \param scalar Scalar by which the current vector will be amplified.
		 * \return A reference to the current vector.
		 */
		Vector& operator*=(const float scalar);

		/**
		 * \brief Overload of the division-assignment operator.
		 * 
		 * Divides the current vector by a real number. Each component will be
		 * divided by the given number.
		 * 
		 * \param divisor Number by which the current vector will be divided.
		 * \return A reference to the current vector.
		 */
		Vector& operator/=(const float divisor);

		/**
		 * \brief Overload of the assignment operator.
		 */
		void operator=(const Vector& other);	
	};

	/**
	 * \brief Overload of the addition operator.
	 * 
	 * The vectors are summed by respectively adding their components.
	 * 
	 * \return The sum as a new Vector.
	 */
	Vector operator+(const Vector& left, const Vector& right);

	/**
	 * \brief Overload of the substraction operator.
	 * 
	 * The components of left are respectively substracted by the ones from right.
	 * 
	 * \return The result as a new Vector.
	 */
	Vector operator-(const Vector& left, const Vector& right);

	/**
	 * \brief Overload of the unary minus operator.
	 * 
	 * Applies the unary minus operator to each component of the vector.
	 * 
	 * \return The result as a new Vector.
	 */
	Vector operator-(const Vector& right);

	/**
	 * \brief Overload of the multiplication operator.
	 * 
	 * Amplifies (or "scales") base by a scalar. Each component will be
	 * multiplied by the given scalar.
	 * 
	 * \param scalar Scalar (real number) by which the current vector will be amplified.
	 * \return The result as a new vector.
	 */
	Vector operator*(const Vector& base, const float scalar);

	/**
	 * \brief Overload of the multiplication operator.
	 * 
	 * Amplifies (or "scales") base by a scalar. Each component will be
	 * multiplied by the given scalar.
	 * 
	 * \param scalar Scalar (real number) by which the current vector will be amplified.
	 * \return The result as a new vector.
	 */
	Vector operator*(const float scalar, const Vector& base);

	/**
	 * \brief Overload of the multiplication operator.
	 * 
	 * Amplifies (or "scales") base by a scalar. Each component will be
	 * multiplied by the given scalar.
	 * 
	 * \param scalar Scalar (real number) by which the current vector will be amplified.
	 * \return The result as a new vector.
	 */
	Vector operator/(const Vector& base, const float divisor);

	/**
	 * \brief Overload of the equality operator.
	 * \return True if the 2 vectors are equal, false otherwise.
	 */
	bool operator==(const Vector& left, const Vector& right);

	/**
	 * \brief Overload of the inequality operator.
	 * \return true if the 2 vectors are different, false otherwise.
	 */
	bool operator!=(const Vector& left, const Vector& right);
}

#ifdef USE_SFML_VECTORS
#include <SFML/System/Vector2.hpp>
namespace CB {
	using vec_t = sf::Vector2f;
}
#else
namespace CB {
	using vec_t = CB::Vector;
}
#endif USE_SFML_VECTORS

namespace CB {
	/**
	 * \brief Computes the magnitude squared of the given vector.
	 *
	 * The "magnitude squared" is useful because it allows to *compare*
	 * the magnitude of 2 vectors without having to square-root the values.
	 *
	 * \return The magnitude squared of the given vector.
	 */
	float vec_magnitude_squared(vec_t v);

	/**
	 * \brief Computes the magnitude of a vector.
	 *
	 * The magnitude is the "length" of a vector.
	 *
	 * \return The magnitude of the given vector.
	 */
	float vec_magnitude(vec_t v);

	/**
	 * \brief Computes the dot product of 2 vectors.
	 * \return The result of the dot product, a scalar.
	 */
	float vec_dot_product(vec_t a, vec_t b);

	/**
	 * \brief Makes the components of the vector positive.
	 * \return A vector whose components are positive numbers.
	 */
	vec_t vec_abs(vec_t v);

	/**
	 * \brief Normalizes the given vector.
	 *
	 * Computes the normalized version of the current vector. A normalized vector
     * is a vector with an intensity (magnitude) of 1. Normalized vectors can be
	 * used to represent directions.
	 *
	 * \return A normalized vector.
	 */
	vec_t vec_normalize(vec_t v);

	/**
	 * \brief Rotates a vector.
	 * \return A vector "rotated" by the given angle.
	 */
	vec_t vec_rotate(vec_t v, float angle);

	/**
	 * \brief Builds a vector from polar coordinates (a length and an angle).
	 * \return The polar coordinates converted to a cartesian vector.
	 */
	vec_t vec_from_polar_coordinates(float degrees, float length);
}

namespace CB {

	/**
	 * \brief Represents an AABB's corner.
	 */
	enum class Corner {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	/**
	 * \brief Represents an Axis-Aligned-Bounding-Box
	 * 
	 * An AABB is a rectangle whose sides are aligned with the axis of the world in
	 * which it is defined.
	 * It's a rectangle that cannot rotate.
	 * 
	 * AABBs are commonly used to represent hitboxes. This class contains member
	 * functions that allow simple collision detection between AABBs.
	 */
	class AABB {

	public:

		vec_t pos; /**< Position of the top-left corner of the AABB. */

		vec_t size; /**< Size of the AABB. X for the width and Y for the height. */

	public:

		/**
		 * \brief Constructs a new AABB with default values.
		 * 
		 * By default, the AABB is positioned at 0,0 and has a size of 0,0.
		 */
		AABB();

		/**
		 * \brief Constructs a new AABB from 2 vectors.
		 * 
		 * \param position Position of the AABB.
		 * \param size_ Size of the AABB.
		 */
		AABB(const vec_t& position, const vec_t& size_);

		/**
		 * \brief Constructs a new AABB from 4 values.
		 * 
		 * \param left Distance from the AABB to the vertical axis.
		 * \param top Distance from the AABB to the horizontal axis.
		 * \param width Width of the AABB.
		 * \param height Height of the AABB.
		 */
		AABB(float left, float top, float width, float height);

		/**
		 * \brief Moves the AABB by the given movement.
		 *
		 * \param movement Vector representing the displacement.
		 */
		void move(const vec_t& movement);

		/**
		 * \brief Returns the center of the AABB.
		 * 
		 * \return The position of the AABB's center.
		 */
		vec_t center() const;

		/**
		 * \brief Computes the position of a single corner of the AABB.
		 * 
		 * Returns the position of one of the AABB's corner depending on the given enum
		 * value (see Corner).
		 * 
		 * \param corner Desired corner position.
		 * 
		 * \return The position of the specified corner.
		 */
		vec_t corner(const Corner corner) const;

		/**
		 * \brief Scales the AABB's size.
		 * 
		 * Scales the AABB's size by the given factor while keeping the same center
		 * for the AABB. 
		 * This method will also modify the position of the AABB (pos).
		 */
		void scaleRelativeToCenter(float factor);

		/**
		 * \brief Computes the perimeter of the AABB.
		 * \return The perimeter of the AABB.
		 */
		float perimeter() const;

		/**
		 * \brief Computes the area of the AABB.
		 * \return The area of the AABB.
		 */
		float area() const;

		/**
		 * \brief Computes the length of any of the AABB's diagonals.
		 * \return Length of the diagonal.
		 */
		float diagonalLength() const;

		/**
		 * \brief Checks if the given point is inside the AABB.
		 * \param point The position of the point as a Vector.
		 * \return True if the point is contained in the AABB, false otherwise.
		 */
		bool contains(const vec_t& point) const;

		/**
		 * \brief Checks if the given AABB intersects the current AABB.
		 * \param other AABB which is potentially overlapping with the current AABB.
		 * \return True if other intersects the current AABB, false otherwise.
		 */
		bool intersects(const AABB& other) const;

		/**
		 * \brief Checks if the given AABB is entirely contained in the current AABB.
		 * \param other AABB which is potentially contained inside the current AABB.
		 * \return True if other is contained inside the current AABB, false otherwise.
		 */
		bool strictlyContains(const AABB& other) const;
	};

	/**
	 * \brief Overload of the equality operator.
	 * \return True if left and right are equal, false otherwise.
	 */
	bool operator==(const AABB& left, const AABB& right);

	/**
	 * \brief Overload of the inequality operator.
	 * \return True if left and right are different, false otherwise.
	 */
	bool operator!=(const AABB& left, const AABB& right);
}

namespace CB {

	/**
	 * \brief Represents a circle.
	 * 
	 * This class contains methods that perform common operations that can be done with
	 * circles such as computing the diameter, the area, the circumference and also
	 * collision detection.
	 * Circles are defined by the position of their center (a vector) and their radius (a real number).
	 */
	class Circle {

	public:

		vec_t pos; /**< The circle's center position. */

		float radius; /**< The circle's radius. */

	public:

		/**
		 * \brief Constructs a new Circle with default values.
		 * 
		 * The new circle will be positioned at 0,0 and have a radius of 0.
		 */
		Circle();

		/**
		 * \brief Constructs a new Circle from a vector and a radius.
		 * \param position Position of the center of the circle.
		 * \param radius_ Radius of the circle.
		 */
		Circle(const vec_t& position, float radius_);

		/**
		 * \brief Computes the diameter of the circle.
		 * \return The diameter (radius * 2).
		 */
		float diameter() const;

		/**
		 * \brief Computes the circumference of the circle.
		 * \note The value for PI that will be used is the one contained in Constants.h
		 * \return The circumference.
		 */
		float circumference() const;

		/**
		 * \brief Computes the area of the circle. 
		 * \note The value for PI that will be used is the one contained in Constants.h
		 * \return The area of the circle.
		 */
		float area() const;

		/**
		 * \brief Computes the smallest AABB that contains the current circle.
		 * 
		 * The computed AABB will be as small as possible and the Circle will be
		 * centered inside it.
		 * 
		 * \return A new AABB containing the current circle.
		 */
		AABB enclosingAABB() const;

		/**
		 * \brief Checks if the given point is contained inside the current circle.
		 * \param point The position of the point.
		 * \return True if the point is inside the circle, false otherwise.
		 */
		bool contains(const vec_t& point) const;

		/**
		 * \brief Checks if the given circle intersects the current circle.
		 * \param other Another circle.
		 * \return True if the circles are overlapping, false otherwise.
		 */
		bool intersects(const Circle& other) const;

		/**
		 * \brief Checks if the given circle is entirely contained inside the current
		 * circle.
		 * \param other The potentially contained circle.
		 * \return True if the given circle is contained in the current circle.
		 */
		bool strictlyContains(const Circle& other) const;

		/**
		 * \brief Overload of the assignment operator.
		 * \param toCopy Circle whose values will be copied into the current circle. 
		 */
		void operator=(const Circle& toCopy);
	};

	/**
	 * \brief Overload of the equality operator between 2 circles.
	 * \return True if left is equal to right.
	 */
	bool operator==(const Circle& left, const Circle& right);

	/**
	 * \brief Overload of the inequality operator between 2 circles.
	 * \return True if left and right are different.
	 */
	bool operator!=(const Circle& left, const Circle& right);
}

#include <string>

namespace CB {

	/**
	 * Represents the type of intersection between 2 LineSegment.
	 */
	enum class IntersectionType {
		None, /**< The 2 segments are not intersecting. */
		Crossing, /**< The 2 segments are crossing at a single point. */
		Overlapping /**< The 2 segments are overlapping. */
	};

	/**
	 * \brief Represents an intersection between 2 segments.
	 * 
	 * How to use this class :
	 * Depending on the type of the intersection, different informations will
	 * be available about it. 
	 * Here are the 3 possible cases :
	 * - type equals IntersectionType::None -> There is no intersection.
	 * - type equals IntersectionType::Crossing -> There is a simple intersection
	 * 	 and member SegmentsIntersection::point contains the point of intersection.
	 * - type equals IntersectionType::Overlapping -> The segments are overlapping
	 *   and member SegmentsIntersection::resultingSegment contains 2 points
	 *   representing the extremities of a sub-segment that defines the overlapping
	 *   range.
	 * 
	 * \note Trying to retrieve an information that is not related to the
	 * 		 intersection type will result in undefined behaviour as the intersection
	 * 		 informations are part of a union.
	 */
	struct SegmentsIntersection {

		SegmentsIntersection(IntersectionType type_);
		SegmentsIntersection(IntersectionType type_, const vec_t& point_);
		SegmentsIntersection(IntersectionType type_, const std::pair<vec_t, vec_t>& segment);

		IntersectionType type; /**< Type of the intersection. */

		union {
			vec_t point; /**< Intersection point. */
			std::pair<vec_t, vec_t> resultingSegment; /**< Overlapping range of 2 segments. */
		};
	};
}

namespace CB {

	/**
	 * \brief Represents a line segment.
	 * 
	 * A line segment is a line that is not infinite. A LineSegment is delimited by two
	 * points.
	 * This class contains utility methods that perform operations such as computing
	 * the slope of a segment, it's length and detecting collisions.
	 */
	class LineSegment {

	public:

		vec_t start; /**< First point of the segment */
		vec_t end; /**< Second point of the segment */

	public:

		/**
		 * \brief Default constructs a new LineSegment.
		 */
		LineSegment();

		/**
		 * \brief Constructs a new LineSegment from 2 points.
		 * \param start_ First point of the segment.
		 * \param end_ Second point of the segment.
		 */
		LineSegment(const vec_t& start_, const vec_t& end_);

		/**
		 * \brief Computes the slope of the segment.
		 * 
		 * The slope is the rate at which the segment climbs. Obviously, the slope
		 * can be negative if the segment is not going up (from left to right).
		 * 
		 * \return The slope of the segment. If the slope is infinite, the float
		 * value for infinity defined in std::numeric_limits is returned. 
		 */
		float slope() const;

		/**
		 * \brief Computes the length of the segment.
		 * \return Length of the segment as a scalar.
		 */
		float length() const;

		/**
		 * \brief Computes the squared length of the segment.
		 * 
		 * Computes the length without square-rooting it. Similar
		 * to CB::Vector::magnitudeSquared().
		 * 
		 * \return The length squared.
		 */
		float lengthSquared() const;

		/**
		 * \brief Computes a vector representing the size of the segment.
		 * \return The absolute value of the size vector.
		 */
		vec_t absoluteSize() const;

		/**
		 * \brief Computes a unit vector of the direction from start to end.
		 * \return The direction from start to end.
		 */
		vec_t dirFromStart() const;

		/**
		 * \brief Computes the min value of X on the segment.
		 */
		float minX() const;

		/**
		 * \brief Computes the min value of Y on the segment.
		 */
		float minY() const;
		
		/**
		 * \brief Computes the max value of X on the segment.
		 */
		float maxX() const;
	
		/**
		 * \brief Computes the max value of Y on the segment.
		 */
		float maxY() const;

		/**
		 * \brief Computes the enclosing AABB.
		 * 
		 * Finds the smallest possible AABB that contains both points of the segment.
		 * 
		 * \return The enclosing AABB.
		 */
		AABB enclosingAABB() const;

		/**
		 * \brief Checks if the current segment and other are intersecting.
		 * 
		 * This methods generates a SegmentsIntersection instance representing the
		 * state of intersection between the 2 segments. 
		 * 
		 * \note See the SegmentsIntersection class to learn how to interpret the
		 *  	 result of this method.
		 * \param other The segment to check for intersection with.
		 * \return A SegmentsIntersection giving information about the intersection.
		 */
		SegmentsIntersection checkForIntersection(const LineSegment& other) const;

		/**
		 * \brief Computes the y-intercept value of a right (infinite line).
		 * 
		 * The Y-intercept is the Y component of the point at which the given right
		 * (defined by a point located on it and it's slope) will intercept the Y-axis.
		 * 
		 * \param anyPoint A point that is located on the right.
		 * \param slope The slope of the right.
		 * \return The y-intercept value.
		 */
		static float YIntercept(const vec_t& anyPoint, float slope);

		/**
		 * \brief Overload of the assignment operator.
		 * \param model Segment to copy from.
		 */
		void operator=(const LineSegment& model);
	};

	/**
	 * \brief Overload of the equality operator.
	 * 
	 * \note 2 segments are equal if they have the same extremities. If their
	 * 		 extremities are simply reversed, they will still be equal.
	 * 
	 * \return True if the segments have the same points equal, false otherwise.
	 */
	bool operator==(const LineSegment& left, const LineSegment& right);

	/**
	 * \brief Overload of the inequality operator.
	 * \return The opposite of operator==().
	 */
	bool operator!=(const LineSegment& left, const LineSegment& right);
}

#include <chrono>

namespace CB {

	/**
	 * \brief Represents a stopwatch.
	 *
	 * A utility class that encapsulates time measurement in a very simple interface.
	 */
	class Stopwatch {
	public:
		using time_point = std::chrono::time_point<std::chrono::system_clock>;

		/**
		 * \brief Constructs a new Stopwatch and starts it
		 */
		Stopwatch();

		/**
		 * \brief Starts measuring time.
		 */
		void start();

		/**
		 * \brief reset() is a convenient alias for the start() method.
		 */
		void reset();

		/**
		 * \brief Stops measuring time.
		 * \note Stopping the watch is not necessary to get the elapsed time. 
		 */
		void stop();

		/**
		 * \brief Returns the elapsed time in seconds.
		 * \note Stopping the watch is not necessary to get the elapsed time.
		 */
		long elapsedSeconds();

		/**
		 * \brief Returns the elapsed time in milliseconds.
		 * \note Stopping the watch is not necessary to get the elapsed time.
		 */
		long elapsedMilliseconds();

		/**
		 * \brief Returns the elapsed time in microseconds.
		 * \note Stopping the watch is not necessary to get the elapsed time.
		 */
		long elapsedMicroseconds();

		/**
		 * \brief Returns the elapsed time in nanoseconds.
		 * \note Stopping the watch is not necessary to get the elapsed time.
		 */
		long elapsedNanoseconds();

	private:

		/**
		 * \brief Returns a time_point representing the current moment.
		 */
		time_point now() const;

		time_point start_; /**< Time at which the stopwatch started measuring */
		time_point end_; /**< Time at which the stopwatch stopped measuring */
	};
}

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

namespace CB {

	Circle::Circle() : pos(), radius(0) {}

	Circle::Circle(const vec_t& position, float radius_) : pos(position), radius(radius_) {}

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