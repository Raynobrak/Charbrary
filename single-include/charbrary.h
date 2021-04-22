// BEGIN CHARBRARY.H

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

#include <string>

namespace ch {

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
namespace ch {
	using vec_t = sf::Vector2f;
}
#else
namespace ch {
	using vec_t = ch::Vector;
}
#endif USE_SFML_VECTORS

namespace ch {
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

//! Contains everything related to the Charbrary
namespace ch {
	constexpr float FLT_PI = 3.14159265359f;

	// The charbrary use a top-left-origin coordinate system. Below are constants for the direction of each axis.

	static const ch::vec_t LEFT_VEC = { -1.f, 0.f };
	static const ch::vec_t RIGHT_VEC = { 1.f, 0.f };
	static const ch::vec_t UP_VEC = { 0.f, -1.f };
	static const ch::vec_t DOWN_VEC = { 0.f, 1.f };

	static const ch::vec_t NULL_VEC = { 0.f,0.f };
}

namespace ch {
	/**
	 * \brief Represents an AABB's corner.
	 */
	enum class Corner {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		MAX_VALUE
	};

	/**
	 * \brief Utility function to find the diagonal opposite of a corner.
	 *
	 * The diagonally opposed corner is the "opposite" of a given corner.
	 * Example : TopLeft is diagonally opposed to BottomRight and vice-versa.
	 *
	 * \returns The opposite of the given corner.
	 */
	constexpr Corner diagonally_opposed_corner(Corner corner);

	/**
	 * \brief Utility function to find the vertical opposite of a corner.
	 *
	 * Example : TopLeft is vertically opposed to BottomLeft and vice-versa.
	 *
	 * \returns The vertical opposite of the given corner.
	 */
	constexpr Corner vertically_opposed_corner(Corner corner);

	/**
	 * \brief Utility function to find the horizontal opposite of a corner.
	 *
	 * Example : TopLeft is horizontally opposed to TopRight and vice-versa.
	 *
	 * \returns The horizontal opposite of the given corner.
	 */
	constexpr Corner horizontally_opposed_corner(Corner corner);
}

namespace ch {

	/**
	 * \brief Contains information about a collision between 2 AABBs.
	 */
	struct AABBCollision {
		vec_t normal; /**< The collision normal, a vector representing the direction of the collision. */
		vec_t delta; /**< The overlap of the colliding AABB on the other AABB. */

		/**
		 * \returns The penetration depth of the collision (= the length of the delta vector along the collision normal)
		 */
		float absolutePenetrationDepthAlongNormal() const;
	};
}

namespace ch {

	/**
	 * \brief Represents a circle.
	 *
	 * This class contains member functions that perform common mathematical operations
	 * done with circles (computing the area, perimeter, circumference) and also to help
	 * dealing with collision detection.
	 * Circles are defined by a position (the center) and a radius.
	 */
	class Circle {

	public:

		vec_t pos; /**< The circle's center position. */

		float radius; /**< The circle's radius. */

	public:

		/**
		 * \brief Constructs a new circle with default values.
		 * 
		 * The new circle will be positioned at 0,0 and have a radius of 0.
		 */
		Circle();

		/**
		 * \brief Constructs a new Circle from a vector and a radius.
		 * \param position Position of the center of the circle.
		 * \param radius_ Radius of the circle.
		 */
		Circle(const vec_t& position_, float radius_);

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

#include <array>

namespace ch {

	/**
	 * \brief Represents an Axis-Aligned-Bounding-Box
	 * 
	 * An AABB is a rectangle that cannot rotate.
	 * 
	 * Since AABBs are commonly used to represent hitboxes, this class 
	 * contains a few functions to help dealing with collision detection.
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
		 * \param pos_ Position of the AABB.
		 * \param size_ Size of the AABB.
		 */
		AABB(const vec_t& pos_, const vec_t& size_);

		/**
		 * \brief Constructs a new AABB from 4 values.
		 * 
		 * \param x Top left corner position on the X axis.
		 * \param y Top left corner position on the Y axis.
		 * \param w Width of the AABB.
		 * \param h Height of the AABB.
		 *
		 * Good alternative if you want to build an AABB without creating temporary vectors.
		 */
		AABB(float x, float y, float w, float h);

		/**
		 * \brief Moves the AABB by the given movement vector.
		 * \param movement Vector representing the displacement.
		 */
		void move(const vec_t& movement);

		/**
		 * \brief Returns the center of the AABB.
		 * \return The Position of the AABB's center.
		 */
		vec_t center() const;

		/**
		 * \brief Computes the position of a corner of the AABB.
		 * 
		 * Returns the position of the specified corner (see enum Corner).
		 * 
		 * \return The position of the specified corner.
		 */
		vec_t corner(Corner corner) const;

		/**
		 * \brief Computes the position of every corner of the AABB.
		 * 
		 * The returned std::array is ordered in the order as the Corner enum.
		 * 
		 * \return An array containing all 4 corners of the AABB.
		 */
		std::array<vec_t, static_cast<size_t>(Corner::MAX_VALUE)> corners() const;

		/**
		 * \brief Scales the AABB's size while keeping it centered.
		 * 
		 * Scales the AABB's size by the given factor without moving it's center.
		 *
		 * \param factor Factor by which the size will be multiplied. Ex. A factor of 2 will double the width and height.
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
		 * \brief Computes the AABB's diagonal length.
		 * \return Length of the diagonal.
		 */
		float diagonalLength() const;
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

#include <string>

namespace ch {

	/**
	 * \brief Represents the type of intersection between 2 LineSegment.
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

namespace ch {

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
		 * Computes the length without square-rooting it.
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

namespace ch {

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

#include <vector>

namespace ch { 

	//! Contains random number generation (RNG) utils
	namespace rand {

		/**
		 * \brief Generates a random integer within the given boundaries. The lower and upper limits are inclusive, meaning they are included in the range of possible values.
		 */
		int rand_int(int lowerInc, int upperInc);

		/**
		 * \brief Generates a random float within the given boundaries. The lower and upper limits are inclusive, meaning they are included in the range of possible values.
		 */
		float rand_float(float min, float max);

		/**
		* \brief Returns a random boolean.
		*/
		bool rand_bit();
		 
		/**
		* \brief Returns a boolean with the given probability of being true.
		*/
		bool rand_bit(float probability);

		/**
		* \brief Generates a random normalized float (between -1 and 1).
		*/
		float rnd_normal_float();

		/**
		 * \brief Generates a random angle in degrees (between 0 and 360).
		 */
		float rnd_angle_deg();

		/**
		 * \brief Generates a random angle in radians (between 0 and 2*pi).
		 */
		float rnd_angle_rad();

		/**
		 * \brief Generates a vector with random XY values within the given boundaries.
		 */
		vec_t rand_vector(float minX, float maxX, float minY, float maxY);

		/**
		 * \brief Generates a random unit vector.
		 */
		vec_t rand_unit_vector();

		/**
		 * \brief Generates a random point located on the given rectangle.
		 */
		vec_t rand_point_on_rect(vec_t topLeftCorner, vec_t size);

		/**
		 * \brief Generates a random point located on the given rectangle.
		 */
		vec_t rand_point_on_rect(vec_t center, float width, float height);

		/**
		 * \brief Generates a random point located on the given circle.
		 */
		vec_t rand_point_on_circle(float circleRadius, vec_t circleCenter = { 0.f,0.f });

		/**
		 * \brief Generates a random point located on the given taurus (taurus = donut).
		 */
		vec_t rand_point_on_torus(float innerRadius, float outerRadius, vec_t torusCenter = { 0.f,0.f });
	}
}

namespace ch {

	/**
	 * \brief Contains information about a collision between 2 circles.
	 */
	struct CirclesCollision {
		vec_t normal; /**< The collision normal, a vector representing the direction of the collision. */
		float absoluteDepth; /**< The depth of the collision (always positive). Can be used with the normal to determine the collision correction. */
	};
}

namespace ch {

	/**
	 * \brief Contains information about a collision between an AABB and a circle.
	 */
	struct CircleAABBCollision {
		vec_t normal; /**< The collision normal, a vector representing the direction of the collision. */
		float absoluteDepth; /**< The depth of the collision (always positive). Can be used with the normal to determine the collision correction. */
	};
}

namespace ch {

	//! Contains collision detection utils for 2D shapes (AABBs, circles, lines)
	namespace collision {

		/** \return A circle that contains the given AABB. */
		Circle enclosingCircle(const AABB& aabb);

		/** \return A circle contained in the given AABB. */
		Circle inscribedCircle(const AABB& aabb);

		/** \return An AABB that contains the given circle. */
		AABB enclosingAABB(const Circle& circle);

		/** \return The smallest enclosing AABB that contains both points of the segment. */
		AABB enclosingAABB(const LineSegment& lineSegment);

		/** \return An AABB contained in the given circle. */
		AABB inscribedAABB(const Circle& circle);
			
		/** \returns True if the given point is inside the AABB, false otherwise. */
		bool aabb_contains(const AABB& aabb, const vec_t& point);

		/** \returns True if the first AABB contains the other AABB, false otherwise. */
		bool aabb_contains(const AABB& first, const AABB& other);

		/** \returns True if the AABB contains the circle, false otherwise. */
		bool aabb_contains(const AABB& aabb, const Circle& circle);

		/** \returns True if the circle contains the point, false otherwise. */
		bool circle_contains(const Circle& circle, const vec_t& point);

		/** \returns True if the first circle contains the other, false otherwise. */
		bool circle_contains(const Circle& first, const Circle& other);

		/** \returns True if the circle contains the AABB, false otherwise. */
		bool circle_contains(const Circle& circle, const AABB& aabb);

		/** \returns True if the given AABBs intersect, false otherwise. */
		bool aabb_intersects(const AABB& a, const AABB& b);

		/** \returns True if the AABB and the circle intersect, false otherwise. */
		bool aabb_intersects(const AABB& aabb, const Circle& circle);

		/** \returns True if the circles intersect, false otherwise. */
		bool circle_intersects(const Circle& circle, const Circle& other);

		/** \returns True if the Circle and the AABB intersect, false otherwise. */
		bool circle_intersects(const Circle& circle, const AABB& aabb);

		/** \returns The distance separating two circles (negative if overlapping) */
		float circles_distance(const Circle& a, const Circle& b);

		/**
		 * \brief Checks if the first AABB collides with the other one.
		 *
		 * In case of a collision, this function returns an instance of AABBCollision containing the collision normal and the delta (overlap).
		 * The collision normal is the direction (a unit vector) towards which the other AABB needs to be pushed in order to resolve the collision.
		 * The collision normal will be set to a null vector (0,0) if there is no collision.
		 *
		 * \returns An AABBCollision containing information about the collision.
		 */
		AABBCollision aabb_collision_info(const AABB& first, const AABB& other);

		/**
		 * \brief Checks if the first circle collides with the other one.
		 *
		 * In case of a collision, this function returns an instance of CirclesCollision containing the collision normal and the penetration depth.
		 * The collision normal is the direction (a unit vector) towards which the other circle needs to be pushed in order to resolve the collision.
		 * The collision normal will be set to a null vector (0,0) if there is no collision.
		 *
		 * \returns A CirclesCollision object containing information about the collision.
		 */
		CirclesCollision circles_collision_info(const Circle& first, const Circle& other);

		/**
		 * \brief Checks if an AABB and a circle collide with each other.
		 *
		 * In case of a collision, this function returns an instance of CircleAABBCollision containing the collision normal and the penetration depth.
		 * The collision normal is the direction (a unit vector) towards which the *circle* needs to be pushed in order to resolve the collision.
		 * The collision normal will be set to a null vector (0,0) if there is no collision.
		 *
		 * \returns A CircleAABBCollision object containing information about the collision.
		 */
		CircleAABBCollision circle_aabb_collision_info(const AABB& aabb, const Circle& circle);

		/**
		 * \brief Checks if the given line segments are intersecting.
		 *
		 * This methods generates a SegmentsIntersection instance representing the
		 * state of intersection between the 2 segments.
		 *
		 * \note See the SegmentsIntersection class to learn how to interpret the
		 *  	 result of this method.
		 * 
		 * \return A SegmentsIntersection giving information about the intersection.
		 */
		SegmentsIntersection line_segments_intersection_info(const LineSegment& first, const LineSegment& other);
	}
}

// END CHARBRARY.H
