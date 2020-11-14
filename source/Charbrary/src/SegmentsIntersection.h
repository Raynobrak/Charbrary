#pragma once

#include "vector_type_definition.h"
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