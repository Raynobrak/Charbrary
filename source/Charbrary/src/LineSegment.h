#pragma once

#include "vector_type_definition.h"
#include "AABB.h"
#include "SegmentsIntersection.h"

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
		 * Computes the length without square-rooting it. Similar
		 * to ch::Vector::magnitudeSquared().
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