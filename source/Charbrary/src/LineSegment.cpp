#include "LineSegment.h"

#include "collision_functions.h"

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

