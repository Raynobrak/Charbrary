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

	LineSegment::LineSegment(const Vector& start_, const Vector& end_) : start(start_), end(end_) {}

	float LineSegment::length() const {
		return (end - start).magnitude();
	}

	float LineSegment::lengthSquared() const {
		return (end - start).magnitudeSquared();
	}

	Vector LineSegment::absoluteSize() const {
		return (end - start).abs();
	}

	Vector LineSegment::dirFromStart() const {
		return (end - start).normalize();
	}

	float LineSegment::slope() const {
		Vector size = start - end;
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
		
					const Vector* p1 = nullptr;
					const Vector* p2 = nullptr;

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

					return SegmentsIntersection(IntersectionType::Overlapping, std::pair<Vector,Vector>{ *p1,*p2 });
				}
				else {
					return SegmentsIntersection(IntersectionType::None);
				}
			}
			else {
				if (YInterceptCurrent == YInterceptOther) {

					return SegmentsIntersection(IntersectionType::Crossing, Vector(0, YInterceptCurrent));
				}
				else {
					float commonX = (YInterceptOther - YInterceptCurrent) / (slopeCurrent - slopeOther);

					if (commonX > minX() && commonX < maxX() && commonX > other.minX() && commonX < other.maxX()) {
						float commonY = slopeCurrent * commonX + YInterceptCurrent;

						return SegmentsIntersection(IntersectionType::Crossing, Vector(commonX, commonY));
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

	float LineSegment::YIntercept(const Vector& anyPoint, float slope) {
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

