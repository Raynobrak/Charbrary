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

#include "LineSegment.h"

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

