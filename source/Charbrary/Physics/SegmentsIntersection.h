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

#include "Vector.h"

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
		SegmentsIntersection(IntersectionType type_, const Vector& point_);
		SegmentsIntersection(IntersectionType type_, const std::pair<Vector, Vector>& segment);

		IntersectionType type; /**< Type of the intersection. */

		union {
			Vector point; /**< Intersection point. */
			std::pair<Vector, Vector> resultingSegment; /**< Overlapping range of 2 segments. */
		};
	};
}