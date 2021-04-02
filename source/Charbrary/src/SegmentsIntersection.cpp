#include "SegmentsIntersection.h"

namespace ch {
	SegmentsIntersection::SegmentsIntersection(IntersectionType type_) : type(type_) {}
	SegmentsIntersection::SegmentsIntersection(IntersectionType type_, const vec_t& point_) : type(type_), point(point_) {}
	SegmentsIntersection::SegmentsIntersection(IntersectionType type_, const std::pair<vec_t, vec_t>& segment) : type(type_), resultingSegment(segment) {}
}
